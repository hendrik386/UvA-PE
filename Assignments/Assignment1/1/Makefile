# See LICENSE.txt for license details.

CXX_FLAGS += -std=c++17 -Ofast -march=native
PAR_FLAG = -fopenmp
#GENERATE = -D GENERATE
GENERATE = 
TIMING = -D TIMING

ifneq (,$(findstring icpc,$(CXX)))
	PAR_FLAG = -openmp
endif

ifneq ($(SERIAL), 1)
	#CXX_FLAGS += $(PAR_FLAG)
endif

APPS = matmul transpose

.PHONY: all

all: $(APPS)

matmul: matmul.cpp mmio.c
	$(CXX) $(CXX_FLAGS) $(GENERATE) $(TIMING) -o $@ $^ $(LFLAGS)

transpose: transpose.cpp mmio.c
	$(CXX) $(CXX_FLAGS) $(GENERATE) $(TIMING) -o $@ $^ $(LFLAGS)

.PHONY: clean
clean:
	rm -f $(APPS)
