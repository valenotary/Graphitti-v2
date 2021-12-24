# CMakeList.txt : CMake project for graphitti-cmake-vs22, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.21)

project (graphitti-v2 LANGUAGES C CXX)

include(CheckLanguage)

if (CMAKE_CUDA_STANDARD)
	message(STATUS "CUDA Standard defined in Preset - checking for CUDA supported compiler...")
	check_language(CUDA)
	if (CMAKE_CUDA_HOST_COMPILER)
		message(STATUS "CUDA supported compiler found. Enabling...")
		enable_language(CUDA)
	else()
		message(STATUS "CUDA supported compiler not found. Not enabling...")
	endif()
endif()

find_package(unofficial-sqlite3 CONFIG REQUIRED)

# Add source to this project's executable.
add_executable (graphitti-cmake-vs22 "graphitti-cmake-vs22.cpp" "graphitti-cmake-vs22.h")

target_link_libraries(graphitti-cmake-vs22 PRIVATE unofficial::sqlite3::sqlite3)
# TODO: Add tests and install targets if needed.
