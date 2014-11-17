/* Implementation of an Aladdin accelerator with a datapath that is connected
 * to main memory via DMA.
 */

#include "base/types.hh"
#include "base/trace.hh"
#include "base/flags.hh"
#include "mem/request.hh"
#include "mem/packet.hh"
#include "mem/mem_object.hh"
#include "sim/system.hh"
#include "sim/sim_exit.hh"
#include "sim/clocked_object.hh"

#include "aladdin/common/ScratchpadDatapath.h"
#include "debug/DmaScratchpadDatapath.hh"
#include "DmaScratchpadDatapath.h"

DmaScratchpadDatapath::DmaScratchpadDatapath(
    const DmaScratchpadDatapathParams* params) :
    ScratchpadDatapath(params->benchName,
                       params->traceFileName,
                       params->configFileName,
                       params->cycleTime),
    MemObject(params),
    inFlightNodes(0),
    _dataMasterId(params->system->getMasterId(name() + ".dmadata")),
    spadPort(this, params->system, params->maxDmaRequests),
    tickEvent(this),
    dmaSetupLatency(params->dmaSetupLatency),
    system(params->system)
{
  scratchpad = new Scratchpad(params->spadPorts, cycleTime);
  setGlobalGraph();
  initActualAddress();
  ScratchpadDatapath::globalOptimizationPass();
  setGraphForStepping();
  num_cycles = 0;
  system->registerAcceleratorStart();
  schedule(tickEvent, clockEdge(Cycles(1)));
}

DmaScratchpadDatapath::~DmaScratchpadDatapath()
{
  delete scratchpad;
}

// TODO: Copied from CacheDatapath.cpp. Some refactoring is in order.
void DmaScratchpadDatapath::initActualAddress()
{
  ostringstream file_name;
  file_name << benchName << "_memaddr.gz";
  gzFile gzip_file;
  gzip_file = gzopen(file_name.str().c_str(), "r");
  while (!gzeof(gzip_file))
  {
    char buffer[256];
    if (gzgets(gzip_file, buffer, 256) == NULL)
      break;
    unsigned node_id;
    long long int address;
    unsigned size;
    sscanf(buffer, "%d,%lld,%u\n", &node_id, &address, &size);
    actualAddress[node_id] = make_pair(address & MASK, size/8);
  }
  gzclose(gzip_file);
}

void DmaScratchpadDatapath::event_step()
{
  step();
  scratchpad->step();
}

void
DmaScratchpadDatapath::stepExecutingQueue()
{
  auto it = executingQueue.begin();
  int index = 0;
  while (it != executingQueue.end())
  {
    unsigned node_id = *it;
    if (is_memory_op(microop.at(node_id)))
    {
      std::string node_part = baseAddress[node_id].first;
      if(scratchpad->canServicePartition(node_part))
      {
        assert(scratchpad->addressRequest(node_part));
        if (is_load_op(microop.at(node_id)))
          scratchpad->increment_loads(node_part);
        else
          scratchpad->increment_stores(node_part);
        markNodeCompleted(it, index);
      }
      else
      {
        ++it;
        ++index;
      }
    }
    else if (is_dma_op(microop.at(node_id)))
    {
      DmaRequestStatus status = Ready;
      Addr addr = actualAddress[node_id].first;
      unsigned size = actualAddress[node_id].second;
      if (dma_requests.find(addr) == dma_requests.end())
        dma_requests[addr] = status;
      else
        status = dma_requests[addr];
      if (status == Ready && inFlightNodes < MAX_INFLIGHT_NODES)
      {
        //first time see, do access
        bool isLoad = is_dma_load(microop.at(node_id));
        issueDmaRequest(addr, size, isLoad, node_id);
        dma_requests[addr] = Waiting;
        DPRINTF(DmaScratchpadDatapath, "node:%d is a dma request\n", node_id);
        ++it;
        ++index;
      }
      else if (status == Returned)
      {
        markNodeCompleted(it, index);
        dma_requests[addr] = status;
        inFlightNodes--;
      }
      else
      {
        // Still waiting from the cache. Move on to the next node.
        ++it;
        ++index;
      }
    }
    else
    {
      // Not a memory operation node, so it can be completed in one cycle.
      markNodeCompleted(it, index);
    }
  }
}

bool
DmaScratchpadDatapath::step() {
  stepExecutingQueue();
  copyToExecutingQueue();
  DPRINTF(DmaScratchpadDatapath, "Cycles:%d, executedNodes:%d, totalConnectedNodes:%d\n",
     num_cycles, executedNodes, totalConnectedNodes);
  num_cycles++;
  if (executedNodes < totalConnectedNodes)
  {
    schedule(tickEvent, clockEdge(Cycles(1)));
    return true;
  }
  else
  {
    dumpStats();
    system->registerAcceleratorExit();
    if (system->totalNumInsts == 0 &&  // no cpu
        system->numRunningAccelerators() == 0)
    {
      exitSimLoop("Aladdin called exit()");
    }
  }
  return false;
}

BaseMasterPort &
DmaScratchpadDatapath::getMasterPort(const string &if_name, PortID idx)
{
  // Get the right port based on name. This applies to all the
  // subclasses of the base CPU and relies on their implementation
  // of getDataPort and getInstPort. In all cases there methods
  // return a MasterPort pointer.
  if (if_name == "spad_port")
    return getDataPort();
  else
    return MemObject::getMasterPort(if_name);
}

/* Mark the DMA request node as having completed. */
void
DmaScratchpadDatapath::completeDmaAccess(Addr addr)
{
  DPRINTF(DmaScratchpadDatapath,
          "completeDmaAccess for addr:%#x \n", addr);
  dma_requests[addr] = Returned;
}

/* Issue a DMA request for memory. */
void DmaScratchpadDatapath::issueDmaRequest(
    Addr addr, unsigned size, bool isLoad, int node_id)
{
  DPRINTF(DmaScratchpadDatapath, "issueDmaRequest for addr:%#x, size:%u\n", addr, size);
  MemCmd::Command cmd = isLoad ? MemCmd::ReadReq : MemCmd::WriteReq;
  Request::Flags flag = 0;
  uint8_t *data = new uint8_t[size];
  dmaQueue.push_back(addr);
  DmaEvent *dma_event = new DmaEvent(this);
  spadPort.dmaAction(cmd, addr, size, dma_event, data,
                     clockEdge(Cycles(dmaSetupLatency)), flag);
}

bool DmaScratchpadDatapath::SpadPort::recvTimingResp(PacketPtr pkt)
{
  return DmaPort::recvTimingResp(pkt);
}

DmaScratchpadDatapath::DmaEvent::DmaEvent(DmaScratchpadDatapath *_dpath)
  : Event(Default_Pri, AutoDelete), datapath(_dpath) {}

void DmaScratchpadDatapath::DmaEvent::process()
{
  assert(!datapath->dmaQueue.empty());
  datapath->completeDmaAccess(datapath->dmaQueue.front());
  datapath->dmaQueue.pop_front();
}
const char * DmaScratchpadDatapath::DmaEvent::description() const
{
  return "DmaScratchpad DMA receving request event";
}

////////////////////////////////////////////////////////////////////////////
//
//  The SimObjects we use to get the Datapath information into the simulator
//
////////////////////////////////////////////////////////////////////////////

DmaScratchpadDatapath* DmaScratchpadDatapathParams::create()
{
  return new DmaScratchpadDatapath(this);
}
