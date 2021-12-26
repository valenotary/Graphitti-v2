# CMakeList.txt : CMake project for graphitti-cmake-vs22, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.21)

project (graphitti-v2 LANGUAGES C CXX)

find_package(unofficial-sqlite3 CONFIG REQUIRED)

# Add source to this project's executable.
add_executable (graphitti-cmake-vs22 "graphitti-cmake-vs22.cpp" "graphitti-cmake-vs22.h")
target_compile_options(graphitti-cmake-vs22 PUBLIC -fsycl -fsycl-targets=nvptx64-nvidia-cuda)
# includes 
target_include_directories(graphitti-cmake-vs22 PRIVATE $ENV{SYCL_LLVM_DIR}/include/sycl)

# library directories
target_link_directories(graphitti-cmake-vs22 PRIVATE $ENV{SYCL_LLVM_DIR}/lib)
# libraries
target_link_libraries(graphitti-cmake-vs22 PRIVATE unofficial::sqlite3::sqlite3)
target_link_libraries(graphitti-cmake-vs22 PRIVATE sycl)
target_link_options(graphitti-cmake-vs22 PUBLIC -fsycl -fsycl-targets=nvptx64-nvidia-cuda)

# TODO: Add tests and install targets if needed.
