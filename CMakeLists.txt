#TODO: Test if export LD_LIBRARY_PATH=/usr/local/lib/
#if(DEFINED ENV{GTEST_DIR})
#	message("Using gtest found in $ENV{GTEST_DIR}.")
#else()
#	message("GTEST_DIR is not defined. You must tell CMake where to find the# gtest source.")
#	return()
#endif()

cmake_minimum_required (VERSION 2.6)

project (PGNAnalyzer)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wpedantic")

include_directories ("${PROJECT_SOURCE_DIR}/include")

add_executable(PGNAnalyzer src/main.cpp src/Game.cpp)

### tests/ 
option(build_tests "Build unit tests?" OFF)
if(build_tests)
	add_subdirectory(tests)
endif()
