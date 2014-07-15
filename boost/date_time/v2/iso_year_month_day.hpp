#ifndef ISO_YEAR_MONTH_DAY_HPP__
#define ISO_YEAR_MONTH_DAY_HPP__

#include "year_month_day.hpp"


namespace boost { 
  namespace date_time2 {

    //todo -- bad design what about iso week specificatins or day of year

    ///Specification of a date in iso form convertable to date
    struct iso_year_month_day : public year_month_day
    {

      enum ISO_FORMAT {ISO_NORMAL, ISO_EXTENDED};

      iso_year_month_day(const char* const iso_string) 
      {
	std::string ymd(iso_string);
	
	//todo -- this is lousy impl for now, but works
	//todo -- needs to be templatitized to support other char types
	//todo -- if this has timezone it might need adjustment...
	if (ymd.length() >= 7) {
	  if (ymd[4] != '-') { //iso compressed 20140401 -- apr 1, 2014
	    //todo use c++11 stoi
	    year = std::atoi(ymd.substr(0,4).c_str());
	    month = std::atoi(ymd.substr(4,2).c_str());
	    day_of_month = std::atoi(ymd.substr(6,2).c_str());
	  }
	  else { //iso extended
	    year = std::atoi(ymd.substr(0,4).c_str());
	    month = std::atoi(ymd.substr(5,2).c_str()); //skip - in pos 4
	    day_of_month = std::atoi(ymd.substr(8,2).c_str()); //skip - in pos 7
	  }
	}
	  
      }
      template<typename string_type>
      iso_year_month_day(const string_type& iso_string) 
      {
      }

      template<typename T>
      T to() const
      {
	std::cout << "WARNING....undefined ymd conversion called " << std::endl;
	//static_assert(false, "This signature is here for speciazialition only");
      }
    };

    template<>
    iso_year_month_day::iso_year_month_day<std::string>(const std::string& iso_string) :
      iso_year_month_day(iso_string.c_str()) //forwarding constructor
    {}

    // template<>
    // year_month_day
    // day_of_week::to() const
    // {

    //   //DEBUG std::cout << " TRACE: " << static_cast<short>(month) << " " << weekday << std::endl;
    //   if (week_of_month == month_weeks::Last) {
    // 	typedef boost::gregorian::last_day_of_the_week_in_month lastkday;
    // 	lastkday lkd(weekday, month);
    // 	boost::gregorian::date d(lkd.get_date(year));
    // 	//DEBUG std::cout << " TRACE dow2: " << d << std::endl;
    // 	return year_month_day(d); //note inefficient...
    //   }
    //   if (week_of_month == month_weeks::First) {
    // 	typedef boost::gregorian::first_day_of_the_week_in_month firstkday;
    // 	firstkday fkd(weekday, month);
    // 	boost::gregorian::date d(fkd.get_date(year));
    // 	//DEBUG std::cout << " TRACE dow3: " << d << std::endl;
    // 	return year_month_day(d); //note todo inefficient...
    //   }
    //   //else week is 1 to 5 - so use nth kday
    //   typedef boost::gregorian::nth_day_of_the_week_in_month nthkdayofmonth;
    //   nthkdayofmonth nkd(static_cast<nthkdayofmonth::week_num>(week_of_month), weekday, month);
    //   boost::gregorian::date d(nkd.get_date(year));
    //   //DEBUG std::cout << " TRACE dow4: " << d << std::endl;
    //   return year_month_day(d); 
    // }

    

    } //namespace date_time2
} //namespace boost
#endif
