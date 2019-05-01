enable_language(CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Ofast -march=native -g")

add_executable(
	Project
	src/BarnzNhutt.cpp
	src/Bhtree.cpp
	src/Octant.cpp
)