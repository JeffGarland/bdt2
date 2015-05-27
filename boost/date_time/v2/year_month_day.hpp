#ifndef BDT2_YEAR_MONTH_DAY_HPP
#define BDT2_YEAR_MONTH_DAY_HPP

#include <ctime>
#include <cstdlib> //for int32_t
#include <string>
#include <tuple>
#include <array>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/finder.hpp>
#include "basic_defs.hpp"
#include <iomanip>

namespace algo = boost::algorithm;

namespace boost { 
  namespace date_time2 {

    /** Helper to provide construction and output of date types from various
     *  year-month-day representations.
     */
    struct year_month_day 
    {
      ///Constructs and invalid ymd
      constexpr
      year_month_day() noexcept :
	year(0),
	month(0),
	day_of_month(0) 
      {}

      ///Construct a year month day -- unchecked
      constexpr
      year_month_day(int16_t y, uint8_t m, uint8_t d) noexcept :
	year(y),
	month(m),
	day_of_month(d) 
      {}

      // ///This constructor allows expression of dates like 1st Sunday after 1/1/2010
      // ///or Nearest Sunday to 1/1/2010.
      // year_month_day(uint16_t y, uint8_t m, uint8_t d, weekdays wd, direction_type p) 
      // {
      // 	//todo write the code here
      // 	//todo -- is this really the best way?  shouldn't there be a struct
      // 	//        like the day_of_week form so that we can do i/o?
      // }

      //todo -- handy, but dangerous...what if month is actually a string...
      year_month_day(const char* const y,
		     const char* const m,
		     const char* const d) :
	year(std::atoi(y)),
	month(std::atoi(m)),
	day_of_month(std::atoi(d))
      {}

      template<typename T>
      explicit
      constexpr
      year_month_day(const T& y, const T& m, const T& d) :
	year(static_cast<int16_t>(y)),
	month(static_cast<uint8_t>(m)),
	day_of_month(static_cast<uint8_t>(d)) 
      {} //todo should cause error

      enum class date_order { ymd, mdy, dmy };


      template<date_order=date_order::ymd>
      static
      year_month_day
      parse_date(const char* const ymd_string, date_order)
      {
	std::string ymd(ymd_string);
	algo::replace_all(ymd, "/", " ");
	algo::replace_all(ymd, "-", " ");
	return year_month_day(std::atoi(ymd.c_str()),
			      std::atoi(ymd.c_str()+5),
			      std::atoi(ymd.c_str()+8));
      }

      // template<>
      // static
      // year_month_day
      // parse_date<date_order::mdy>(const char* const ymd_string, date_order) :
      // {
      // 	std::string ymd(ymd_string);
      // 	algo::replace_all(ymd, "/", " ");
      // 	algo::replace_all(ymd, "-", " ");
      // 	return year_month_day(std::atoi(ymd.c_str()),
      // 			      std::atoi(ymd.c_str()+5),
      // 			      std::atoi(ymd.c_str()+8));

      // }

      // todo -- shouldn't we have an ordering and delimiter version
      /// Construct from a string of the form YYYY-MM-DD or YYYY/MM/DD
      template<date_order = date_order::ymd>
      year_month_day(const char* const ymd_string, 
		     date_order order=date_order::ymd) 
      {
	*this = parse_date(ymd_string, order);
      }

      template<typename T>
      explicit 
      year_month_day(const T& ymd)
      {
      } //todo should cause error

      template<typename T>
      T to() const
      {
	std::cout << "WARNING....undefined ymd conversion called " << std::endl;
	//    static_assert(false, "This signature is here for speciazialition only");
      }

      bool operator==(const year_month_day& rhs) const
      {
	return (year == rhs.year &&
		month == rhs.month &&
		day_of_month == rhs.day_of_month);
      }
      int16_t year;//   = 10001; //todo - what the zero year -- what the negative?
      uint8_t month;//  = 13;
      uint8_t day_of_month; // = 32;
    };


    ///Stream out the year/month/day
    std::ostream& operator<<(std::ostream& os, const year_month_day& ymd)
    {
      os << ymd.year << "-" 
	 << std::setw(2) << std::setfill('0') 
	 << static_cast<unsigned short>(ymd.month) << "-" 
	 << std::setw(2) << std::setfill('0') 
	 << static_cast<unsigned short>(ymd.day_of_month);
      return os;
    }

    ///Specialization to convert from 3 strings in y, m, d order
    template<>
    year_month_day::year_month_day(const std::string& y,
				   const std::string& m,
				   const std::string& d) :
      year(std::atoi(y.c_str())),
      month(std::atoi(m.c_str())),
      day_of_month(std::atoi(d.c_str()))
    {}

    ///Specialization to parse a string - forwards to char* specialization
    template<>
    year_month_day::year_month_day(const std::string& ymd_string) :
      year_month_day(ymd_string.c_str())
    {}

    ///Specialization to convert from std::tm
    template<>
    year_month_day::year_month_day(const std::tm& tm)
    {
      year = tm.tm_year+1900;
      month = tm.tm_mon+1;
      day_of_month = tm.tm_mday;
    } 

    ///Specialization to convert from a std::tuple<int,int,int> in y/m/d order
    template<>
    year_month_day::year_month_day(const std::tuple<int, int, int>& ymd)
    {
      year = std::get<0>(ymd);
      month = std::get<1>(ymd);
      day_of_month = std::get<2>(ymd);
    } 

    ///Specialization to convert from a boost::gregorian::date
    template<>
    year_month_day::year_month_day(const boost::gregorian::date& d)
    {
      boost::gregorian::date::ymd_type ymd = d.year_month_day();
      year = ymd.year;
      month = ymd.month;
      day_of_month = ymd.day;
    } 

    template<>
    boost::gregorian::date
    year_month_day::to() const
    {
      return boost::gregorian::date(year, month, day_of_month);
    }


    //  http://akrzemi1.wordpress.com/2012/10/29/user-defined-literals-part-iii/
    //N2750 recommendation to prevent clash
    //N2750 recommends calling namespace operators -- I prefer literals

    namespace literals 
    {
      year_month_day operator"" _ymd(const char* s, size_t)
      {
	std::string str(s);
	return year_month_day(str);
      }
    }

  } //namespace date_time2
} //namespace boost
#endif
