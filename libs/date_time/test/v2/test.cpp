
//g++-4.8 -I../../../ -I ~/devtools/boost_1_55_0 -std=c++11 test.cpp

//#include "ext_tm.hpp"
//#include "utc_time_label.hpp"
//#include "date.hpp"
#include <iostream>
#include "testfrmwk.hpp"

#include "test_date.hpp"
#include "test_year_month_day.hpp"
#include "test_iso_year_month_day.hpp"
#include "test_closest_day.hpp"
#include "test_day_of_week.hpp"
#include "test_day_of_year.hpp"
#include "test_iso_week_number.hpp"
#include "test_nanotime.hpp"

using namespace boost::date_time2;
using std::cout;
using std::endl;

// class null_check 
// {
//   static void validate_ymd(uint16_t, uint8_t, uint8_t) {}
  
// };

// template<>
// date::date<std::tm, null_check>(const std::tm& tm)
// {
//   validator::validate_ymd(tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday);
      
//   //construct....
// }



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

  for (auto i=0; i<12; ++i) 
  {
    std::cout << &short_month_names.names[i][0] << std::endl;
  }
  for (auto i=0; i<12; ++i) 
  {
    std::cout << &long_month_names.names[i][0] << std::endl;
  }
  
 
  TestStats::instance().print();
  return TestStats::instance().failcount();

}
