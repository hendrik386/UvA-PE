enable_language(CUDA)
enable_language(CXX)
enable_language(C)

include_directories(${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES})

#add_compile_definitions(GENERATE=-D GENERATE)
add_compile_definitions(GENERATE=)
add_compile_definitions(TIMING=-D TIMING)

set(CMAKE_CXX_FLAGS "-O3 -Wall")

add_executable(
	Assignment1-3-matmul
	src/matmul.cu
	src/mmio.cu
)
add_executable(
	Assignment1-3-transpose
	src/transpose.cu
)
