set(CMAKE_C_FLAGS "-fopenmp")

add_executable(Assignment3-SPMV-ELLPACK-Parallel
	Source/matrix.c Source/matrix.h Source/mmio.c Source/mmio.h Source/spmv.c Source/spmv_kernel.c Source/spmv_kernel.h)