#ifndef BDT2_DAY_CLOCK
#define BDT2_DAY_CLOCK

#include <boost/date_time.hpp>

namespace boost { 
  namespace date_time2 {
    
    class day_clock 
    {
    public:
      static year_month_day local_day() 
      {
	boost::gregorian::date d = boost::gregorian::day_clock::local_day();
	boost::gregorian::date::ymd_type ymd = d.year_month_day();
	return year_month_day(ymd.year, ymd.month, ymd.day);
      }
      static year_month_day universal_day() 
      {
	boost::gregorian::date d = boost::gregorian::day_clock::universal_day();
	boost::gregorian::date::ymd_type ymd = d.year_month_day();
	return year_month_day(ymd.year, ymd.month, ymd.day);
      }

    };


  } //namespace date_time2
} //namespace boost
#endif
