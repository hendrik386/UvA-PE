enable_language(CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Ofast -march=native -g -fopenmp")

add_executable(
	Project
	src/BarnzNhutt.cpp
#	src/Octant.cpp
#	src/Body.cpp
#	src/Vector3.cpp
#	src/Graphics.cpp
#	src/Utility.cpp
)