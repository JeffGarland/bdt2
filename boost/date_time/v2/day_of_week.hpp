#ifndef BDT2_DAY_WEEK_HPP
#define BDT2_DAY_WEEK_HPP

#include "year_month_day.hpp"


namespace boost { 
  namespace date_time2 {


    /** Specification of a day in a week like - 1st Monday in Jan 2005
     *
     * Construct your date from a logical week day specification
     *
     * day_of_week(Second, Tue, Jan, 2013)
     */
    struct day_of_week
    {
      day_of_week(month_weeks mw, weekdays wd, 
		  uint8_t m, uint16_t y) noexcept :
	year(y),
	month(m),
	week_of_month(mw),
	weekday(wd)
      {}

      /** Default constructor -- constructs to invalid state
       */
      day_of_week() noexcept = default;

      uint16_t    year = 10001;
      uint8_t     month=13;
      month_weeks week_of_month=month_weeks::First;
      weekdays    weekday=weekdays::Sun;

      /** Templated conversion function -- specialize an implementation
       *  for a new type to facilitate conversions
       */
      template<typename T>
      T to() const
      {
	std::cout << "WARNING....undefined ymd conversion called " << std::endl;
	//static_assert(false, "This signature is here for speciazialition only");
      }

      operator year_month_day() const;
    };

    /** Convert the day_of_week to a year_month_day
     */
    template<>
    year_month_day
    day_of_week::to() const
    {

      //DEBUG std::cout << " TRACE: " << static_cast<short>(month) << " " << weekday << std::endl;
      if (week_of_month == month_weeks::Last) {
	typedef boost::gregorian::last_day_of_the_week_in_month lastkday;
	lastkday lkd(weekday, month);
	boost::gregorian::date d(lkd.get_date(year));
	//DEBUG std::cout << " TRACE dow2: " << d << std::endl;
	return year_month_day(d); //note inefficient...
      }
      if (week_of_month == month_weeks::First) {
	typedef boost::gregorian::first_day_of_the_week_in_month firstkday;
	firstkday fkd(weekday, month);
	boost::gregorian::date d(fkd.get_date(year));
	//DEBUG std::cout << " TRACE dow3: " << d << std::endl;
	return year_month_day(d); //note todo inefficient...
      }
      //else week is 1 to 5 - so use nth kday
      typedef boost::gregorian::nth_day_of_the_week_in_month nthkdayofmonth;
      nthkdayofmonth nkd(static_cast<nthkdayofmonth::week_num>(week_of_month), weekday, month);
      boost::gregorian::date d(nkd.get_date(year));
      //DEBUG std::cout << " TRACE dow4: " << d << std::endl;
      return year_month_day(d); 
    }

    //todo -- was trying to just make an operator for year_month_day here
    //so that standard template constructor in date could work...would compile,
    //but would NOT be called -- what was it calling? default constructor?
    ///convenience operator so specialization of date constructor is not required
    // operator day_of_week::year_month_day() const
    // {
    //   std::cout << "DUDE - this was called!!!!" << std::endl;
    //   return this->to<year_month_day>();
    // }


  } //namespace date_time2
} //namespace boost
#endif
