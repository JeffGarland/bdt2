#ifndef BDT2_TEST_DATE_ALGO_HPP__
#define BDT2_TEST_DATE_ALGO_HPP__

#include "boost/date_time/v2/date_algo.hpp"
#include "testfrmwk.hpp"


void test_month_from_year_and_day() {
  using namespace boost::date_time2;
  using std::cout;
  using std::endl;
  
  check("month_from_year_and_day - 2014-Jan-1 == 1", 
	month_from_year_and_day(2014, 1) == 1);
  check("month_from_year_and_day - 2014-Jan-31 == 1", 
	month_from_year_and_day(2014, 31) == 1);
  check("month_from_year_and_day - 2014-Dec-1 == 12", 
	month_from_year_and_day(2014, 365-30) == 12);
  check("month_from_year_and_day - 2000-Feb-29 == 29", 
	month_from_year_and_day(2000, 31+29) == 2);
  
  check("month_from_year_and_day - 2000-Feb-31 == 29", 
	month_from_year_and_day(2000, 31+29) == 2);
  
  check("month_from_year_and_day - 2000-366 == 12", 
	month_from_year_and_day(2000, 366) == 12);
  
  check("month_from_year_and_day - 2001-365 == 12", 
	month_from_year_and_day(2001, 365) == 12);
  
  check("month_from_year_and_day - 2002-321 == 11 (nov 17)", 
	month_from_year_and_day(2002, 321) == 11);
  
  check("month_from_year_and_day - 1400-31 == 1", 
	month_from_year_and_day(2002, 321) == 11);
  
  
}



void test_date_algo()
{
  test_month_from_year_and_day();
}






#endif
