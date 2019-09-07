SRCS=sail.c

ACCEL_NAME = br
TEST_BIN = $(ACCEL_NAME)
export TRACE_OUTPUT_DIR=$(ACCEL_NAME)
ifndef WORKLOAD
  export WORKLOAD=br
endif
include ../common/Makefile.common
include ../common/Makefile.tracer
