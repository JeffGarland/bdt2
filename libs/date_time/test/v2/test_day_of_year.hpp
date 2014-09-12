
#ifndef BDT2_TEST_DOY__
#define BDT2_TEST_DOY__




#include "boost/date_time/v2/day_of_year.hpp"
#include "testfrmwk.hpp"

void test_day_of_year() 
{
  using namespace boost::date_time2;
  using std::cout;
  using std::endl;

  //Quick table of last day of year to month mapping non leap year
  //Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec
  // 31  59  90 120 151 181 212 243 273 304 334 365 

  { //january

    day_of_year doy1(2014, 1);
    date d1(doy1);
    check("day of year - Jan 1", date(2014, Jan, 1) == d1);

    day_of_year doy1a = d1.to<day_of_year>();
    check("day of year - Jan 1 - roundtrip",  
	  doy1a.year == 2014 && doy1a.day == 1);

    day_of_year doy2(2014, 31);
    date d2(doy2);
    check("day of year - Jan 31", date(2014, Jan, 31) == d2);

    day_of_year doy2a = d2.to<day_of_year>();
    check("day of year - Jan 31 - roundtrip",  
	  doy2a.year == 2014 && doy2a.day == 31);

    day_of_year doy3(2000, 31);
    date d3(doy3);
    check("day of year - Jan 31 - leap", date(2000, Jan, 31) == d3);

    day_of_year doy3a = d3.to<day_of_year>();
    check("day of year - Jan 31 - roundtrip - leap",  
	  doy3a.year == 2000 && doy3a.day == 31);

  }
  { //feb
    day_of_year doy1(2014, 31+1);
    date d1(doy1);
    check("day of year - Feb 1", date(2014, Feb, 1) == d1);

    day_of_year doy1a = d1.to<day_of_year>();
    check("day of year - Feb 1 - roundtrip",  
	  doy1a.year == 2014 && doy1a.day == 32);

    day_of_year doy2(2014,31+28);
    date d2(doy2);
    check("day of year - Feb 28 - no leap", date(2014, Feb, 28) == d2);

    day_of_year doy2a = d2.to<day_of_year>();
    check("day of year - Feb 28 - no leap - roundtrip",  
	  doy2a.year == 2014 && doy2a.day == 31+28);

    day_of_year doy3(2000, 31+29);
    date d3(doy3);
    check("day of year - Feb 29 - leap", date(2000, Feb, 29) == d3);

    day_of_year doy4(2000, 31+28);
    date d4(doy4);
    check("day of year - Feb 28 - leap", date(2000, Feb, 28) == d4);
  }

  {
    day_of_year doy1(2014, 31+28+1);
    date d1(doy1);
    check("day of year - Mar 1 - no leap", date(2014, Mar, 1) == d1);

    day_of_year doy2(2014, 31+28+31);
    date d2(doy2);
    check("day of year - Mar 31 - no leap", date(2014, Mar, 31) == d2);

    day_of_year doy3(2000, 31+29+31);
    date d3(doy3);
    check("day of year - Mar 31 - leap", date(2000, Mar, 31) == d3);

  }

  {
    day_of_year doy1(2014, 31+28+31+1);
    date d1(doy1);
    check("day of year - Apr 1 - no leap", date(2014, Apr, 1) == d1);

    day_of_year doy2(2014, 31+28+31+30);
    date d2(doy2);
    check("day of year - Apr 30 - no leap", date(2014, Apr, 30) == d2);
  }

  {
    day_of_year doy1(2014, 31+28+31+30+1);
    date d1(doy1);
    check("day of year - May 1 - no leap", date(2014, May, 1) == d1);

    day_of_year doy2(2014, 31+28+31+30+31);
    date d2(doy2);
    check("day of year - May 31 - no leap", date(2014, May, 31) == d2);

  }
  {
    day_of_year doy1(2014, 31+28+31+30+31+1);
    date d1(doy1);
    check("day of year - Jun 1 - no leap", date(2014, Jun, 1) == d1);

    day_of_year doy2(2014, 31+28+31+30+31+30);
    date d2(doy2);
    check("day of year - Jun 30 - no leap", date(2014, Jun, 30) == d2);

  }
  {
    day_of_year doy1(2014, 31+28+31+30+31+30+1);
    date d1(doy1);
    check("day of year - Jul 1 - no leap", date(2014, Jul, 1) == d1);

    day_of_year doy2(2014, 31+28+31+30+31+30+31);
    date d2(doy2);
    check("day of year - Jul 31 - no leap", date(2014, Jul, 31) == d2);

  }
  {
    day_of_year doy1(2014, 31+28+31+30+31+30+31+1);
    date d1(doy1);
    check("day of year - Aug 1 - no leap", date(2014, Aug, 1) == d1);

    day_of_year doy2(2014, 31+28+31+30+31+30+31+31);
    date d2(doy2);
    check("day of year - Aug 31 - no leap", date(2014, Aug, 31) == d2);

  }
  {
    day_of_year doy1(2014, 31+28+31+30+31+30+31+31+1);
    date d1(doy1);
    check("day of year - Sep 1 - no leap", date(2014, Sep, 1) == d1);

    day_of_year doy2(2014, 31+28+31+30+31+30+31+31+30);
    date d2(doy2);
    check("day of year - Sep 31 - no leap", date(2014, Sep, 30) == d2);

  }
  {
    day_of_year doy1(2014, 31+28+31+30+31+30+31+31+30+1);
    date d1(doy1);
    check("day of year - Oct 1 - no leap", date(2014, Oct, 1) == d1);

    day_of_year doy2(2014, 31+28+31+30+31+30+31+31+30+31);
    date d2(doy2);
    check("day of year - Oct 31 - no leap", date(2014, Oct, 31) == d2);

  }
  {
    day_of_year doy1(2014, 31+28+31+30+31+30+31+31+30+31+1);
    date d1(doy1);
    check("day of year - Nov 1 - no leap", date(2014, Nov, 1) == d1);

    day_of_year doy2(2014, 31+28+31+30+31+30+31+31+30+31+30);
    date d2(doy2);
    check("day of year - Nov 30 - no leap", date(2014, Nov, 30) == d2);

  }
  {
    day_of_year doy1(2014, 31+28+31+30+31+30+31+31+30+31+30+1);
    date d1(doy1);
    check("day of year - Dec 1 - no leap", date(2014, Dec, 1) == d1);

    day_of_year doy2(2014, 31+28+31+30+31+30+31+31+30+31+30+31);
    date d2(doy2);
    check("day of year - Dec 30 - no leap", date(2014, Dec, 31) == d2);

    day_of_year doy3(2000, 366);
    date d3(doy3);
    check("day of year - Dec 31 - leap", date(2000, Dec, 31) == d3);

  }

}



#endif
