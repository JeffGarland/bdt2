
#ifndef BDT2_TEST_YMD__
#define BDT2_TEST_YMD__


#include "boost/date_time/v2/year_month_day.hpp"
#include "boost/date_time/v2/bdt_v1_convert.hpp"
#include <iostream>
#include "testfrmwk.hpp"



void test_iso_year_month_day_2() 
{
  using namespace boost::date_time2;
  using std::cout;
  using std::endl;

  {
    
    year_month_day id("20140401", date_order::ymd, date_format::iso);
    cout << "ISO string " << id << endl;;
    check("ymd: iso year_month_day constructor", 
	  id.year == 2014 && id.month == 4 && id.day_of_month == 1);
    
  }
  {
    
    year_month_day id("2014-04-01");
    cout << "YMD: ISO string 2 " << id << endl;;
    check("ymd: iso year_month_day constructor", 
	   id.year == 2014 && id.month == 4 && id.day_of_month == 1);
    
  }

  {
    
    year_month_day id("2014-04-01T00:00:00Z");
    cout << "YMD: ISO string 3 " << id << endl;;
    check("ymd: iso year_month_day constructor", 
	   id.year == 2014 && id.month == 4 && id.day_of_month == 1);
    
  }

  {
    
    year_month_day id("2014-04-01T00:00:00Z");
    check("ymd: iso year_month_day constructor - conversion", 
  	  date(id) == date(2014,4,1));
    
  }
  {
    
    check("ymd: iso year_month_day constructor - conversion", 
  	  date(year_month_day("20140401T000000", date_order::ymd, date_format::iso)) == date(2014,4,1));
    
  }

  {
    std::string iso_string("2014-04-01T00:00:00Z");
    year_month_day id(iso_string);
    check("ymd: iso year_month_day constructor - conversion", 
  	  date(id) == date(2014,4,1));
    
  }

}

void test_year_month_day_basic()
{

  using namespace boost::date_time2;
  using std::cout;
  using std::endl;

  {
    constexpr year_month_day ymd{};
    check("ymd:constexpr default constructor", 
	  ymd.year == 0 && ymd.month == 0 && ymd.day_of_month == 0);

  }

  {
    constexpr year_month_day ymd{2014, 1, 15};
    check("ymd:constexpr integer constructor", 
	  ymd.year == 2014 && ymd.month == 1 && ymd.day_of_month == 15);

  }

  {
    std::string y("2014");
    std::string m("10");
    std::string d("2");
    year_month_day ymd(y, m, d);
    check("ymd:split string constructor", 
	  ymd.year == 2014 && ymd.month == 10 && ymd.day_of_month == 2);
    cout << "ymd split string " << ymd << endl;;
    
  }
  {

    year_month_day ymd("2004-10-01");
    check("ymd:string constructor", 
	  ymd.year == 2004 && ymd.month == 10 && ymd.day_of_month == 1);
    cout << "ymd string " << ymd << endl;;
  }
  {
    year_month_day ymd("2004/10/01");
    check("ymd:string constructor 2", 
	  ymd.year == 2004 && ymd.month == 10 && ymd.day_of_month == 1);

  }
  {
    std::string s("2004/10/01");
    year_month_day ymd(s);
    check("ymd:string constructor 3", 
	  ymd.year == 2004 && ymd.month == 10 && ymd.day_of_month == 1);

  }

  {
    std::string s("2004 10 01");
    year_month_day ymd(s);
    check("ymd:string constructor 4", 
	  ymd.year == 2004 && ymd.month == 10 && ymd.day_of_month == 1);

  }

  {
    std::string s("01-13-2004");
    year_month_day ymd(s, date_order::mdy);
    check("ymd:string constructor 5 - mdy order", 
	  ymd.year == 2004 && ymd.month == 1 && ymd.day_of_month == 13);

  }

  {
    std::string s("13-01-2004");
    year_month_day ymd(s, date_order::dmy);
    check("ymd:string constructor 6 - dmy order", 
	  ymd.year == 2004 && ymd.month == 1 && ymd.day_of_month == 13);

  }

  // year_month_day d1;
  // cout << d1.year << endl;
  {
    year_month_day ymd(2010, 10, 1);
    check("ymd:int constructor", 
	  ymd.year == 2010 && ymd.month == 10 && ymd.day_of_month == 1);
    cout << "ymd int " << ymd << endl;;
  }
  // cout << "d2: " << d2 << endl;;
  // year_month_day d3("2013", "10", "1");
  // cout << "d3: " << d3 << endl;;


}

void test_year_month_day_conversions()
{
  using namespace boost::date_time2;
  using std::cout;
  using std::endl;

  {
    year_month_day ymd(2010, 10, 1);
    boost::gregorian::date d(ymd.to<boost::gregorian::date>());
    check("boost date conversion from ymd", 
	  boost::gregorian::date(2010, 10, 1) == d);

  }


}
void test_year_month_day() 
{
  test_year_month_day_basic();
  test_iso_year_month_day_2();
  test_year_month_day_conversions();
}



#endif
