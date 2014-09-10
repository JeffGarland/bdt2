
#ifndef BDT2_TEST_YMD__
#define BDT2_TEST_YMD__


#include <iostream>
#include "testfrmwk.hpp"


void test_year_month_day() 
{
  using namespace boost::date_time2;
  using std::cout;
  using std::endl;

  {
    std::string y("2014");
    std::string m("10");
    std::string d("2");
    year_month_day ymd(y, m, d);
    check("ymd split string constructor", 
	  ymd.year == 2014 && ymd.month == 10 && ymd.day_of_month == 2);
    cout << "ymd split string " << ymd << endl;;
    
  }
  {

    year_month_day ymd("2004-10-01");
    check("ymd string constructor", 
	  ymd.year == 2004 && ymd.month == 10 && ymd.day_of_month == 1);
    cout << "ymd string " << ymd << endl;;
  }
  {
    year_month_day ymd("2004/10/01");
    check("ymd string constructor 2", 
	  ymd.year == 2004 && ymd.month == 10 && ymd.day_of_month == 1);

  }
  {
    std::string s("2004/10/01");
    year_month_day ymd(s);
    check("ymd string constructor 3", 
	  ymd.year == 2004 && ymd.month == 10 && ymd.day_of_month == 1);

  }

  // year_month_day d1;
  // cout << d1.year << endl;
  {
    year_month_day ymd(2010, 10, 1);
    check("ymd int constructor", 
	  ymd.year == 2010 && ymd.month == 10 && ymd.day_of_month == 1);
    cout << "ymd int " << ymd << endl;;
  }
  // cout << "d2: " << d2 << endl;;
  // year_month_day d3("2013", "10", "1");
  // cout << "d3: " << d3 << endl;;

  {
    year_month_day ymd(2010, 10, 1);
    boost::gregorian::date d(ymd.to<boost::gregorian::date>());
    check("boost date conversion from ymd", 
	  boost::gregorian::date(2010, 10, 1) == d);


  }

}



#endif
