# See LICENSE.txt for license details.

CXX_FLAGS += -std=c++11 -O3
PAR_FLAG = -g -arch compute_52 -code sm_52
#GENERATE = -D GENERATE
GENERATE = 
TIMING = -D TIMING
NVCC = nvcc

ifneq (,$(findstring icpc,$(CXX)))
	PAR_FLAG = -openmp
endif

ifneq ($(SERIAL), 1)
	CXX_FLAGS += $(PAR_FLAG)
endif

APPS = matmul transpose

.PHONY: all

all: $(APPS)

matmul: matmul.cu mmio.cu
	$(NVCC) $(CXX_FLAGS) $(GENERATE) $(TIMING) -o $@ $^ $(LFLAGS)

transpose: transpose.cu mmio.cu
	$(NVCC) $(CXX_FLAGS) $(GENERATE) -o $@ $^ $(LFLAGS)

.PHONY: clean
clean:
	rm -f $(APPS)
