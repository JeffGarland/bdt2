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



void test_leap_year() {
  using namespace boost::date_time2;
  
  check("algo:is_leap_year -1404 is a leap year", is_leap_year(1404));
  check("algo:is_leap_year -2000 is a leap year", is_leap_year(2000));
  check("algo:is_leap_year -2004 is a leap year", is_leap_year(2004));
  check("algo:is_leap_year -2400 is a leap year", is_leap_year(2400));
  check("algo:is_leap_year -4000 is a leap year", is_leap_year(4000));
  check("algo:is_leap_year -1400 is NOT a leap year", !is_leap_year(1400));
  check("algo:is_leap_year -1900 is NOT a leap year", !is_leap_year(1900));
  check("algo:is_leap_year -2100 is NOT a leap year", !is_leap_year(2100));
  check("algo:is_leap_year -1999 is NOT a leap year", !is_leap_year(1999));
  check("algo:is_leap_year -5000 is NOT a leap year", !is_leap_year(5000));
  check("algo:is_leap_year -2014 is NOT a leap year", !is_leap_year(2014));

}


void test_end_of_month_day() {
  using boost::date_time2::end_of_month_day;

  check("algo:end_of_month_day - 31 days in month Jan 2000", 
	end_of_month_day(2000,1) == 31);
  check("algo:end_of_month_day - 29 days in month Feb 2000", 
	end_of_month_day(2000,2) == 29);
  check("algo:end_of_month_day - 28 days in month Feb 1999", 
	end_of_month_day(1999,2) == 28);
  check("algo:end_of_month_day - 28 days in month Feb 2001", 
	end_of_month_day(2001,2) == 28);
  check("algo:end_of_month_day - 31 days in month Mar 2000", 
	end_of_month_day(2000,3) == 31);
  check("algo:end_of_month_day - 30 days in month Apr 2000", 
	end_of_month_day(2000,4) == 30);
  check("algo:end_of_month_day - 31 days in month May 2000", 
	end_of_month_day(2000,5) == 31);
  check("algo:end_of_month_day - 30 days in month Jun 2000", 
	end_of_month_day(2000,6) == 30);
  check("algo:end_of_month_day - 31 days in month Jul 2000", 
	end_of_month_day(2000,7) == 31);
  check("algo:end_of_month_day - 31 days in month Aug 2000", 
	end_of_month_day(2000,8) == 31);
  check("algo:end_of_month_day - 30 days in month Sep 2000", 
	end_of_month_day(2000,9) == 30);
  check("algo:end_of_month_day - 31 days in month Oct 2000", 
	end_of_month_day(2000,10) == 31);
  check("algo:end_of_month_day - 30 days in month Nov 2000", 
	end_of_month_day(2000,11) == 30);
  check("algo:end_of_month_day - 31 days in month Dec 2000", 
	end_of_month_day(2000,12) == 31);
}



void test_from_ymd() {
  using namespace boost::date_time2;
  
  // check("month_from_year_and_day - 2014-Jan-1 == 1", 
  // 	month_from_year_and_day(2014, 1) == 1);
  
  
}


void test_date_algo()
{
  test_leap_year();
  test_end_of_month_day();
  test_month_from_year_and_day();
  test_from_ymd();
}






#endif
