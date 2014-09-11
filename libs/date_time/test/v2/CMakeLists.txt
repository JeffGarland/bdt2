cmake_minimum_required (VERSION 2.6)
project (bdt2)

#tuned for linux just now...
set (CMAKE_CXX_COMPILER "/usr/bin/g++-4.9" CACHE FILEPATH "CXX Compiler" FORCE)
set (CMAKE_CXX_FLAGS "-std=c++14 -Wall")

include_directories("../../../../")

add_executable(testv2 test.cpp)

#provides a make test target that will build and run test
enable_testing()
add_test(testall testv2)


