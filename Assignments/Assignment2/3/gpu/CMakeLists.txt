enable_language(CUDA)

include_directories(${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES})

add_executable(
	Assignment2-3-gpu
	src/histogram.cu
	src/timer.cc
)
add_executable(
	Assignment2-3-gpu-events
	src/histogram-events.cu
	src/timer.cc
)
