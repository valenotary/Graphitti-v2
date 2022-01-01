add_subdirectory(./core)

add_library(test_directory INTERFACE)
target_link_libraries(test_directory INTERFACE
	test_directory_core
)