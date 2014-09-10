
//Primary test file -- includes all other tests and calls 
//As of 2014-Sep-10 116 tests
//use the following command to compile for now and run resulting executable...
//g++-4.8 -I../../../ -I ~/devtools/boost_1_55_0 -std=c++11 test.cpp
//g++-4.9 -I../../../../ -I -std=c++14 test.cpp

#include "test_date.hpp"
#include "test_year_month_day.hpp"
#include "test_iso_year_month_day.hpp"
#include "test_closest_day.hpp"
#include "test_day_of_week.hpp"
#include "test_day_of_year.hpp"
#include "test_iso_week_number.hpp"
#include "test_nanotime.hpp"

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

  TestStats::instance().print();
  return TestStats::instance().failcount();

}
