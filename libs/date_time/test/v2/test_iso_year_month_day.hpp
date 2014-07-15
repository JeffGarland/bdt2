
#ifndef BDT2_TEST_ISOYEAR_MONTH_DAY__
#define BDT2_TEST_ISOYEAR_MONTH_DAY__




#include "boost/date_time/v2/iso_year_month_day.hpp"
#include <iostream>
#include "testfrmwk.hpp"


void test_iso_year_month_day() 
{
  using namespace boost::date_time2;
  using std::cout;
  using std::endl;

  {
    
    iso_year_month_day id("20140401");
    cout << "ISO string " << id << endl;;
    check("iso year_month_day constructor", 
	   id.year == 2014 && id.month == 4 && id.day_of_month == 1);
    
  }
  {
    
    iso_year_month_day id("2014-04-01");
    cout << "ISO string 2 " << id << endl;;
    check("iso year_month_day constructor", 
	   id.year == 2014 && id.month == 4 && id.day_of_month == 1);
    
  }

  {
    
    iso_year_month_day id("2014-04-01T00:00:00Z");
    cout << "ISO string 3 " << id << endl;;
    check("iso year_month_day constructor", 
	   id.year == 2014 && id.month == 4 && id.day_of_month == 1);
    
  }

  {
    
    iso_year_month_day id("2014-04-01T00:00:00Z");
    check("iso year_month_day constructor - conversion", 
	  date(id) == date(2014,4,1));
    
  }
  {
    
    check("iso year_month_day constructor - conversion", 
	  date(iso_year_month_day("20140401T000000")) == date(2014,4,1));
    
  }

  {
    std::string iso_string("2014-04-01T00:00:00Z");
    iso_year_month_day id(iso_string);
    check("iso year_month_day constructor - conversion", 
	  date(id) == date(2014,4,1));
    
  }

}



#endif
