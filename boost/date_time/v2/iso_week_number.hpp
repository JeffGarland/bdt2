#ifndef BDT2_ISO_WEEK_NUMBER_HPP
#define BDT2_ISO_WEEK_NUMBER_HPP

#include <ctime>
#include <cstdlib> //for int32_t
#include <string>
#include <tuple>
#include <array>
#include <boost/date_time.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/finder.hpp>
#include "basic_defs.hpp"
#include "day_of_year.hpp"

namespace algo = boost::algorithm;

namespace boost { 
  namespace date_time2 {


    /**Construct from an iso week number spec - 2014 Week 7 Sunday
     * Note that iso week numbers are a bit complex in that days in the
     * last week of a year may be in the following year and days in the
     * first week of a year may be in the prior year.  So, for example
     * 2004-W53-6 is 2005-01-01 and 2008-W1-01 is 2007-12-31.
     *
     * Some notes about iso week numbers.  The weeks start on Monday. 
     * The first week of the year contains the first thursday of the 
     * year which guarantees that Jan 4 is in the first iso week of 
     * the year.
     */
    struct iso_week_number 
    {
      /** Construct to invalid state
       */
      iso_week_number() noexcept = default;

      /** Numeric constructor 
       * @param y The year for the week number
       * @param wn The week number 1..53
       * @param dow The day in the week 1..7 where 1==Monday, 2==Tuesday, ...7==Sunday
       */
      iso_week_number(uint16_t y, uint8_t wn, uint8_t dow) noexcept :
	year(y),
 	week_no(wn),
	day_in_week(dow)
      {}
     
      template<typename T>
      T to() const
      {
	std::cout << "WARNING....undefined ymd conversion called " << std::endl;
	//static_assert(false, "This signature is here for speciazialition only");
      }

      /** ISO defined year can have 52 or 53 weeks -- returns true
       * if year is 53 weeks long
       */
      bool is_long_year() const
      {
	return true; //todo fix me!!!
      }
      /** Pass the parts of the week number as chars with all numbers
       * @param y The year for the week number
       * @param wn The week number 1..53 prepended by W (ex: W01, W21, W53)
       * @param dow The day in the week 1..7 where 1==Monday, 2==Tuesday, ...7==Sunday
       */
      iso_week_number(const char* const y, const char* const wn, const char* const dow) :
       	iso_week_number(std::atoi(y), std::atoi(wn+1), std::atoi(dow))
      {}

      /** Construct from a string like 2014-W02-1
       *  Note that all week numbers must be 2 numeric characters so all
       *  weeks less than 10 need to be prepended by zero
       */
      iso_week_number(const std::string spec) 
      {
	if (spec.size() < 10) return; //default values
	*this = iso_week_number(spec.substr(0,4).c_str(),
				spec.substr(6,3).c_str(),
				spec.substr(9,1).c_str());
	// year = std::atoi(spec.substr(0,4).c_str());
	// week_no = std::atoi(spec.substr(6,2).c_str());
	// day_in_week = std::atoi(spec.substr(9,1).c_str());
      }

      uint16_t year = 10001;
      uint8_t  week_no=54; ///<use iso week numbering
      uint8_t  day_in_week=8; ///<1==monday...7==sunday

    };

    ///Specialization to convert to day_of_year form
    template<>
    inline
    day_of_year
    iso_week_number::to() const
    {
      typedef boost::gregorian::first_day_of_the_week_in_month firstkday;
      // firstkday fkd_thu(Thu, 1); //find first thu of jan
      // boost::gregorian::date first_thu(fkd_thu.get_date(year));
      firstkday fkd_mon(Mon, 1); //find first mon of jan -- first day of week in year
      boost::gregorian::date first_mon(fkd_mon.get_date(year));
      boost::gregorian::date jan_first(year, 1, 1);
      boost::gregorian::date jan_four(year, 1, 4);
      //      uint8_t offset = 0;
      boost::gregorian::days diff = first_mon - jan_first;
      uint8_t offset = static_cast<uint8_t>(diff.get_rep().as_number());
      uint8_t days_in_prior_year = 2;
      //todo -- for goodness sake fix this crap!
      //      if (offset < 4)
      

      std::cout << "DEBUG: offset: " << static_cast<int>(offset) << std::endl;
      //if this is week 1 it might be from prior year if Mon - Wed
      if ((this->week_no == 1) && (day_in_week < 4)) { 
	if (offset < 4) { //
	  //todo won't work in leap year
	  return day_of_year(year-1, 365-days_in_prior_year);
	}
      }  
      //todo similar logic for week 52/53
    
    return day_of_year(year, ((week_no-1)*7+day_in_week-days_in_prior_year));
	
    }    


    ///Specialization to convert week number to year_month_day
    template<>
    inline
    year_month_day
    iso_week_number::to() const
    {
      uint16_t year = this->year;
      //if it's week 1 or 52/53 check and see if we 
      //have to adjust the year
      if (this->week_no == 1) {
	
      }
      uint16_t month = (this->week_no-1)*7; 
      uint8_t day_of_month = 0;
      return year_month_day(year, month, day_of_month);
    }    

    //todo - fix me
    // std::ostream& operator<<(std::ostream& os, const iso_week_number& wn)
    // {
    //   os << wn.year << "-" 
    // 	 << static_cast<unsigned short>(wn.week_no) << "-" 
    // 	 << static_cast<unsigned short>(wn.day_of_week);
    //   return os;
    // }


  } //namespace date_time2
} //namespace boost
#endif

