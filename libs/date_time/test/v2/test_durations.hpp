
#ifndef BDT2_TEST_DURATIONS__
#define BDT2_TEST_DURATIONS__


#include "boost/date_time/v2/durations.hpp"
#include <iostream>
#include "testfrmwk.hpp"

void test_days() 
{
  using namespace boost::date_time2;

  {
    days d{5};
    check("duration: days constructor", d.count() == 5);
  }
  {
    days d = days(2) + days(3);
    check("duration: days adding ", d.count() == 5);
  }
  {
    days d = days(8) - days(3);
    check("duration: subtraction", d.count() == 5);
  }
  {
    days d = days(3) - days(3) + days(5);
    check("duration: mixed adding subtract", d.count() == 5);
  }

  {
    if (days(3) <= days(5)) {
      check("duration: days compare", true);
    } else {
      check("duration: days compare", false);
    }
  }


} //test_days

void test_weeks() 
{
  using namespace boost::date_time2;

  {
    weeks w{5};
    check("duration: weeks constructor", w.count() == 5);
  }
  {
    weeks w = weeks(2) + weeks(3);
    check("duration: weeks adding ", w.count() == 5);
  }
  {
    weeks w = weeks(8) - weeks(3);
    check("duration: subtraction", w.count() == 5);
  }
  {
    weeks w = weeks(3) - weeks(3) + weeks(5);
    check("duration: mixed adding subtract", w.count() == 5);
  }

  {
    if (weeks(3) <= weeks(5)) {
      check("duration: weeks compare", true);
    } else {
      check("duration: weeks compare", false);
    }
  }


} //test_weeks

void test_durations()
{
  test_days();
  test_weeks();

  using namespace boost::date_time2;

  {
    days d{1};
    weeks w{1};
    days d2 = d + w;
    check("duration: days + weeks", d2.count() == 8);
  }
  {
    //    weeks w2 = d + w; //yes - compile error!
   // conversion from ‘std::__success_type<std::chrono::duration<int, std::ratio<86400l, 1l> > >::type {aka std::chrono::duration<int, std::ratio<86400l, 1l> >}’ to non-scalar type ‘boost::date_time2::weeks {aka std::chrono::duration<int, std::ratio<604800l, 1l> >}’ requested
   //   weeks w2 = d + w;
   //                ^

  }

}



#endif
