
#ifndef BDT2_TEST_CDOW__
#define BDT2_TEST_CDOW__




#include "boost/date_time/v2/closest_day_of_week.hpp"
#include <iostream>
#include "testfrmwk.hpp"


void test_closest_day_of_week() 
{
  using namespace boost::date_time2;
  using std::cout;
  using std::endl;

  {
    closest_day_of_week pdw(Sun, Before, 2013, May, 17); 
    date d(pdw);
    check("closest date of week - sunday before", 
	  date(2013, May, 12) == d);
  }
  {
    closest_day_of_week pdw(Sun, After, 2013, May, 17); 
    year_month_day ymd(pdw.to<year_month_day>());
    date d(ymd);
    check("closest date of week - sunday after", 
	  date(2013, May, 19) == d);
    cout << "cd2: " << ymd << endl;

  }

  {
    closest_day_of_week pdw(Mon, Before, 2014, Apr, 1); 
    date d(pdw);
    check("closest date of week - monday before - month boundary", date(2014, Mar, 31) == d);
  }

  {
    closest_day_of_week pdw(Mon, Nearest, 2014, Apr, 1); 
    date d(pdw);
    check("closest date of week - monday nearest 4/1", date(2014, Mar, 31) == d);
  }
  {
    closest_day_of_week pdw(Mon, Nearest, 2014, Apr, 2); 
    date d(pdw);
    check("closest date of week - monday nearest 4/2", date(2014, Mar, 31) == d);
  }
  {
    closest_day_of_week pdw(Mon, Nearest, 2014, Apr, 3); 
    date d(pdw);
    check("closest date of week - monday nearest 4/3", date(2014, Mar, 31) == d);
  }
  {
    closest_day_of_week pdw(Mon, Nearest, 2014, Apr, 4); 
    date d(pdw);
    check("closest date of week - monday nearest 4/4", date(2014, Apr, 7) == d);
  }
  {
    closest_day_of_week pdw(Mon, Nearest, 2014, Apr, 5); 
    date d(pdw);
    check("closest date of week - monday nearest 4/5", date(2014, Apr, 7) == d);
  }
  {
    closest_day_of_week pdw(Mon, Nearest, 2014, Apr, 7); 
    date d(pdw);
    check("closest date of week - monday nearest 4/7", date(2014, Apr, 7) == d);
  }

 {
    closest_day_of_week pdw(Mon, Before, 2014, Jan, 1); 
    date d(pdw);
    check("closest date of week - monday before - year boundary", date(2013, Dec, 30) == d);
  }

}



#endif
