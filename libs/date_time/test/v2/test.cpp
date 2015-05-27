
//Primary test file -- includes all other tests and calls 
//As of 2015-May-26 163 tests
//use the following command to compile for now and run resulting executable...
//or use the CMakeLists.txt file. Note that g++5 is now required to compile
//the library due to constexpr enhancements
//g++-5 -I../../../../ -I -std=c++14 test.cpp

#include "test_date.hpp"
#include "test_year_month_day.hpp"
#include "test_iso_year_month_day.hpp"
#include "test_closest_day.hpp"
#include "test_day_of_week.hpp"
#include "test_day_of_year.hpp"
#include "test_iso_week_number.hpp"
#include "test_nanotime.hpp"
#include "test_date_algo.hpp"

#include <iostream>
#include "testfrmwk.hpp"


int main()
{
  test_year_month_day();
  test_date();
  test_closest_day_of_week();
  test_day_of_week();
  test_day_of_year();
  test_iso_week_number();
  test_iso_year_month_day();
  test_nanotime();
  test_date_algo();

  TestStats::instance().print();
  return TestStats::instance().failcount();

}
