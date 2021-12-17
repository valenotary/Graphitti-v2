# CMakeList.txt : CMake project for graphitti-cmake-vs22, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.21)

project ("graphitti-cmake-vs22")

find_package(unofficial-sqlite3 CONFIG REQUIRED)

# Add source to this project's executable.
add_executable (graphitti-cmake-vs22 "graphitti-cmake-vs22.cpp" "graphitti-cmake-vs22.h")

target_link_libraries(graphitti-cmake-vs22 PRIVATE unofficial::sqlite3::sqlite3)
# TODO: Add tests and install targets if needed.
