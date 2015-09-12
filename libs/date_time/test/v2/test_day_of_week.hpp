

#ifndef BDT2_TEST_DOW__
#define BDT2_TEST_DOW__


#include "boost/date_time/v2/day_of_week.hpp"
#include <iostream>
#include "testfrmwk.hpp"


void test_day_of_week() {

  using namespace boost::date_time2;
  using std::cout;
  using std::endl;

  {
    day_of_week dow{Last, Thu, Nov, 2013};
    cout << "dow1: " << dow.to<year_month_day>() << endl;
    year_month_day ymd(dow.to<year_month_day>());
    check("day of week: thx giving 2013 Last Thu in Nov",  year_month_day(2013,Nov,28) == ymd);
  }

  {
    day_of_week dow{First, Sun, Feb, 2002};
    year_month_day ymd(dow.to<year_month_day>());
    check("day of week: First Sunday in Feb 2002",  year_month_day(2002,Feb,3) == ymd);
  }


  {
    day_of_week dow{First, Sun, Feb, 2002};
    year_month_day ymd(dow);
    check("day of week: First Sunday in Feb 2002",  year_month_day(2002,Feb,3) == ymd);
  }

  {
    date memorial(day_of_week(Last, Mon, May, 2013)); 
    check("day of week: memorial day 2013 Last Mon in May",  date(2013,May,27) == memorial);
  }
  {
    date d(day_of_week(First, Tue, Jan, 2013)); 
    check("day of week: first tue in Jan 2013",  date(2013,Jan,1) == d);
  }
  {
    date d(day_of_week(Second, Tue, Jan, 2013)); 
    check("day of week: second tue in Jan 2013",  date(2013,Jan,8) == d);
  }
  {
    date d(day_of_week(Third, Tue, Jan, 2013)); 
    check("day of week: third tue in Jan 2013",  date(2013,Jan,15) == d);
  }
  {
    date d(day_of_week(Fourth, Tue, Jan, 2013)); 
    check("day of week: forth tue in Jan 2013",  date(2013,Jan,22) == d);
  }
  {
    date d(day_of_week(Fifth, Tue, Jan, 2013)); 
    check("day of week: fifth tue in Jan 2013",  date(2013,Jan,29) == d);
  }

}

#endif
