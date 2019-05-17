include_directories(../Libraries/fast-cpp-csv-parser)

add_executable(
	Project
	Source/Bhtree.hpp Source/Body.cpp Source/Body.hpp Source/Color.cpp Source/Color.hpp Source/Constants.hpp Source/Image.cpp Source/Image.hpp Source/NBody.cpp Source/Octant.hpp Source/Universe.cpp Source/Universe.hpp Source/Utility.cpp Source/Utility.cpp Source/Vector3.cpp Source/Vector3.hpp)

target_link_libraries(Project pthread stdc++fs)
