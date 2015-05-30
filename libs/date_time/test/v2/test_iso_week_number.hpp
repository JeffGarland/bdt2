

#ifndef BDT2_TEST_WEEK_NUM__
#define BDT2_TEST_WEEK_NUM__




#include "boost/date_time/v2/iso_week_number.hpp"
#include <iostream>
#include "testfrmwk.hpp"


void test_iso_week_number() {

  using namespace boost::date_time2;
  using std::cout;
  using std::endl;

  {
    boost::gregorian::date d(2014,1,1);
    cout << "Week Number for 1/1/2014 -> " << d.week_number() << endl;
    d += boost::gregorian::days(7);
    cout << "Week Number for 1/8/2014 -> " << d.week_number() << endl;
  }
  {
    iso_week_number wn;
    check("week number default construct - year",  wn.year == 10001);
    check("week number default construct - week number",  wn.week_no == 54);
    check("week number default construct - weekday ",  wn.day_in_week == 8);
  }
  {
    iso_week_number wn("2014-W01-2");
    check("week number string construct - year",  wn.year == 2014);
    check("week number string construct - week number",  wn.week_no == 1);
    check("week number string construct - weekday ",  wn.day_in_week == 2);
  }
  {
    iso_week_number wn("2014", "W1", "2");
    check("week number char construct - year",  wn.year == 2014);
    check("week number char construct - week number",  wn.week_no == 1);
    check("week number char construct - weekday ",  wn.day_in_week == 2);
  }

  //todo this needs a freakin lot of test cases and it's broke now...
  {
    iso_week_number wn(2014, 1, 5); //2014-Jan-3
    day_of_year doy(wn.to<day_of_year>());
    //todo -- why does this compile?    date d2(day_of_year(wn));
    cout << "Week doy: " << doy.to<year_month_day>() << endl;
    date d(doy);
    //date d(2014, 1, 1);
    cout << "Week: " << d << endl;
    //    check("week number default construct",  wn.year == 10001);
  }

  // {
  //   day_of_week dow{2002, Feb, First, Sun};
  //   year_month_day ymd(dow.to<year_month_day>());
  //   check("day of week: First Sunday in Feb 2002",  year_month_day(2002,Feb,3) == ymd);
  // }

}

#endif
