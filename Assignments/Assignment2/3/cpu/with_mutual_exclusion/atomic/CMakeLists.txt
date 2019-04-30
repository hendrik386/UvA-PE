add_executable(
	Assignment2-3-cpu-with_mutual_exclusion-atomic
	src/histo.c
)

target_link_libraries(Assignment2-3-cpu-with_mutual_exclusion-atomic pthread)
