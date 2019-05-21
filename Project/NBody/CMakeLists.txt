enable_language(CXX)

set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_CXX_FLAGS "-march=native -g -fopenmp")
set(CMAKE_CXX_FLAGS "-Ofast -march=native -fopenmp")

add_subdirectory(Libraries)
add_subdirectory(Main)
add_subdirectory(Test)
