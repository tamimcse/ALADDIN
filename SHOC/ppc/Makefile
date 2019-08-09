SRCS=ppc.c

ACCEL_NAME = ppc
TEST_BIN = $(ACCEL_NAME)
export TRACE_OUTPUT_DIR=$(ACCEL_NAME)
ifndef WORKLOAD
  export WORKLOAD=fib_lookup
endif
include ../common/Makefile.common
include ../common/Makefile.tracer
