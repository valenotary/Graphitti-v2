add_library(test_directory_core
	./inc/core_test.hpp 
	./src/core_test.cpp
)
target_include_directories(test_directory_core PUBLIC ./inc)