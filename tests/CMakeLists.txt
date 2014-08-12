#TODO: Do the same with whatever testing framework you choose
#if(DEFINED ENV{GTEST_DIR})
#	message("Using gtest found in $ENV{GTEST_DIR}.")
#else()
#	message("GTEST_DIR is not defined. You must tell CMake where to find the# gtest source.")
#	return()
#endif()
#add_subdirectory($ENV{GTEST_DIR} ${CMAKE_CURRENT_BINARY_DIR}/gtest)



add_executable(PGNAnalyzerTest src/tests.cpp)
