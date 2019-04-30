add_executable(
	Assignment2-3-cpu-with_mutual_exclusion-software_transactional
	src/histo.c
)

target_link_libraries(Assignment2-3-cpu-with_mutual_exclusion-software_transactional pthread)

target_compile_options(Assignment2-3-cpu-with_mutual_exclusion-software_transactional PUBLIC -fgnu-tm)