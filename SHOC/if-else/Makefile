SRCS=if-else.c

ACCEL_NAME = if-else
TEST_BIN = $(ACCEL_NAME)
export TRACE_OUTPUT_DIR=$(ACCEL_NAME)
ifndef WORKLOAD
  export WORKLOAD=if-else
endif
include ../common/Makefile.common
include ../common/Makefile.tracer
