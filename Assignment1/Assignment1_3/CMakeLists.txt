enable_language(CUDA)
enable_language(CXX)
enable_language(C)

include_directories(${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES})

#add_compile_definitions(GENERATE=-D GENERATE)
add_compile_definitions(GENERATE=)
add_compile_definitions(TIMING=-D TIMING)

set(CMAKE_CXX_FLAGS "-O3 -Wall")

add_executable(
	assignment1_3_matmul
	matmul.cu
	mmio.cu
)
add_executable(
	assignment1_3_transpose
	transpose.cu
)
