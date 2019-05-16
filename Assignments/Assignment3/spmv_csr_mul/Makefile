# See LICENSE.txt for license details.
CXX_FLAGS += -std=c++17 -O3 -march=native -Wall
PAR_FLAG = -fopenmp
#GENERATE = -D GENERATE
GENERATE = 
TIMING = -D TIMING

ifneq (,$(findstring icpc,$(CXX)))
	PAR_FLAG = -openmp
endif

ifneq ($(SERIAL), 1)
	CXX_FLAGS += $(PAR_FLAG)
endif

APPS = spmv

.PHONY: all

all: $(APPS)

spmv: spmv.c mmio.c spmv_kernel.c
	$(CXX) $(CXX_FLAGS) $(GENERATE) $(TIMING) -o $@ $^ $(LFLAGS)

.PHONY: clean
clean:
	rm -f $(APPS)
