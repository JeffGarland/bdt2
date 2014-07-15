#ifndef BDT2_CDOW_HPP__
#define BDT2_CDOW_HPP__

#include "year_month_day.hpp"

namespace algo = boost::algorithm;

namespace boost { 
  namespace date_time2 {

    /// Provides a calculated day of a week -- some examples:
    ///   Sunday Before 2005-Jan-1
    ///   Monday After 2013-May-17
    ///   Monday Nearest 2013-May-17
    struct closest_day_of_week 
    {
      closest_day_of_week() {}

      closest_day_of_week(weekdays wd, direction_type dir,
			  uint16_t y, uint8_t m, uint8_t d) :
	ymd(y, m, d),
	weekday(wd),
	direction(dir)
      {}

      closest_day_of_week(weekdays wd, direction_type dir, year_month_day base) :
	ymd(base),
	weekday(wd),
	direction(dir)
      {}

      year_month_day ymd;
      direction_type direction=Before;
      weekdays       weekday=weekdays::Sun;

      template<typename T>
      T to() const
      {
	std::cout << "WARNING....undefined ymd conversion called " << std::endl;
	//    static_assert(false, "This signature is here for speciazialition only");
      }

    };

    template<>
    year_month_day
    closest_day_of_week::to() const
    {
	boost::gregorian::date d(ymd.to<boost::gregorian::date>());
	boost::gregorian::greg_year_month_day new_date(2000,1,1);//no default constructor

	if (direction == Before) {
	  boost::gregorian::first_day_of_the_week_before fdbf(weekday);
	  new_date = fdbf.get_date(d).year_month_day();
	  //DEBUG	  std::cout << "here1..." << day << std::endl;
	}
	if (direction == After) {
	  boost::gregorian::first_day_of_the_week_after fdaf(weekday);
	  new_date = fdaf.get_date(d).year_month_day();
	}
	if (direction == Nearest) {
	  if (d.day_of_week() == weekday) {//today is that day
	    return ymd;
	  }
	  boost::gregorian::first_day_of_the_week_after fdaf(weekday);
	  boost::gregorian::first_day_of_the_week_before fdbf(weekday);
	  boost::gregorian::date after = fdaf.get_date(d);
	  boost::gregorian::date before = fdbf.get_date(d);
	  if ((after-d) <= (d-before)) { //after is closer or same
	    new_date = after.year_month_day();
	  }
	  else {
	    new_date = before.year_month_day();
	  }
	}

	return year_month_day(new_date.year, new_date.month, new_date.day);
    }
    

  } //namespace date_time2
} //namespace boost
#endif
