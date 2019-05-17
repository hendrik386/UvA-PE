enable_testing()

add_test(
	NAME Project-VerifyOutput
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	COMMAND Source/VerifyOutput.sh "$<TARGET_FILE:Project>" "./Resources/images"
)

set_tests_properties(Project-VerifyOutput PROPERTIES DEPENDS Project)
