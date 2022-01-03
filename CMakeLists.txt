cmake_minimum_required (VERSION 3.21)

project (graphitti-v2 LANGUAGES C CXX)

# vcpkg dependencies
find_package(cxxopts CONFIG REQUIRED) # CLI argument parsing 
find_package(flatbuffers CONFIG REQUIRED) # serialization 
find_package(hdf5 CONFIG REQUIRED) # runtime data output format 
find_package(spdlog CONFIG REQUIRED) # logging 
find_package(GTest CONFIG REQUIRED) # testing 

# Add source to this project's executable.
add_executable (graphitti simulator/main/src/main.cpp)
target_compile_options(graphitti PUBLIC -fsycl -fsycl-targets=nvptx64-nvidia-cuda)
target_link_options(graphitti PUBLIC -fsycl -fsycl-targets=nvptx64-nvidia-cuda)

# subdirectories 
add_subdirectory(./simulator/test_directory)
add_subdirectory(./3p)

# includes 
target_include_directories(graphitti PRIVATE
	$ENV{SYCL_LLVM_DIR}/include/sycl
)

# library directories
target_link_directories(graphitti PRIVATE 
	$ENV{SYCL_LLVM_DIR}/lib # for heterogeneous programming 
)

# project sublibraries

#  libraries
target_link_libraries(graphitti PRIVATE 
	# dependencies first 
	sycl # for heterogeneous programming 
	cxxopts::cxxopts # CLI argument parsing 
	flatbuffers::flatbuffers # serialization 
	hdf5::hdf5-shared hdf5::hdf5_hl-shared hdf5::hdf5_cpp-shared hdf5::hdf5_tools-shared # runtime data output format 
	spdlog::spdlog spdlog::spdlog_header_only # logging 
	# GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main # testing (put this in test exec, not in the main one)
	3p


	# simulator modules second 
	test_directory
)


# TODO: Add tests and install targets if needed.