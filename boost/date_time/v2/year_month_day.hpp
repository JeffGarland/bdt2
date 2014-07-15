#ifndef BDT2_YEAR_MONTH_DAY_HPP
#define BDT2_YEAR_MONTH_DAY_HPP

#include <ctime>
#include <cstdlib> //for int32_t
#include <string>
#include <tuple>
#include <array>
#include <boost/date_time.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/finder.hpp>
#include "basic_defs.hpp"

namespace algo = boost::algorithm;

namespace boost { 
  namespace date_time2 {

    /** Helper to provide construction and output of date types from various
     *  year-month-day representations.
     */
    struct year_month_day 
    {
      ///Constructs and invalid ymd
      year_month_day() noexcept :
	year(0),
	month(0),
	day_of_month(0) 
      {}

      ///Construct a year month day -- unchecked
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
      year_month_day(const char* const y, const char* const m, const char* const d) :
	year(std::atoi(y)),
	month(std::atoi(m)),
	day_of_month(std::atoi(d))
      {}

      template<typename T>
      year_month_day(const T& y, const T& m, const T& d) :
	year(static_cast<int16_t>(y)),
	month(static_cast<uint8_t>(m)),
	day_of_month(static_cast<uint8_t>(d)) 
      {} //todo should cause error

      // todo -- shouldn't we have an orderinging and delimiter version
      /// Construct from a string of the form YYYY-MM-DD or YYYY/MM/DD
      year_month_day(const char* const ymd_string) 
      {
	std::string ymd(ymd_string);
	algo::replace_all(ymd, "/", " ");
	algo::replace_all(ymd, "-", " ");
	year = std::atoi(ymd.c_str());
	month = std::atoi(ymd.c_str()+5);
	day_of_month = std::atoi(ymd.c_str()+8);
	//todo remove	std::cout << "ymd char*: " << ymd << std::endl;
      }

      template<typename T>
      explicit year_month_day(const T& ymd)
      {
      } //todo should cause error

      template<typename T>
      T to() const
      {
	std::cout << "WARNING....undefined ymd conversion called " << std::endl;
	//    static_assert(false, "This signature is here for speciazialition only");
      }


      // template<typename T>
      // year_month_day(T ymd)
      // {} //todo should cause error
      bool operator==(const year_month_day& rhs) const
      {
	return (year == rhs.year && month == rhs.month && day_of_month == rhs.day_of_month);
      }
      int16_t year;// = 10001; //todo - what the zero year -- what the negative?
      uint8_t  month;// = 13;
      uint8_t  day_of_month;//=32;
    };


    std::ostream& operator<<(std::ostream& os, const year_month_day& ymd)
    {
      os << ymd.year << "-" 
	 << std::setw(2) << std::setfill('0') << static_cast<unsigned short>(ymd.month) << "-" 
	 << std::setw(2) << std::setfill('0') << static_cast<unsigned short>(ymd.day_of_month);
      return os;
    }

    template<>
    year_month_day::year_month_day(const std::string& y, const std::string& m, const std::string& d) :
      year(std::atoi(y.c_str())),
      month(std::atoi(m.c_str())),
      day_of_month(std::atoi(d.c_str()))
    {}

    template<>
    year_month_day::year_month_day(const std::string& ymd_string) :
      year_month_day(ymd_string.c_str())
    {}

    template<>
    year_month_day::year_month_day(const std::tm& tm)
    {
      year = tm.tm_year+1900;
      month = tm.tm_mon+1;
      day_of_month = tm.tm_mday;
    } 

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
