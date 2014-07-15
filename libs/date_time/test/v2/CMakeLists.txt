# Before running this export CXX=/usr/bin/g++-4.7

cmake_minimum_required (VERSION 2.6)
project (bdt2)

include_directories("~/devtools/boost-trunk")
#link_directories("~/devtools/boost-trunk/bin.v2/libs/date_time/build/gcc-4.7/release/")
#target_link_libraries(boost_date_time.so.1.51.0)
add_definitions("-std=gnu++0x -DBOOST_DATE_TIME_NO_LIB")
add_executable(test test.cpp)
#add_executable(cookbook cookbook.cpp)
#add_executable(c2 cookbook2.cpp)


