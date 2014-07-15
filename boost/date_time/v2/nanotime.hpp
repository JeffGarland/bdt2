#ifndef BDT2_TIME_HPP
#define BDT2_TIME_HPP

#include <ctime>
#include <cstdlib> //for int32_t
#include <stdexcept>
#include <string>
#include <sstream>
#include "year_month_day.hpp"
#include "day_of_year.hpp"
#include "closest_day_of_week.hpp"
#include "day_of_week.hpp"
#include "iso_year_month_day.hpp"
#include "iso_week_number.hpp"
#include <chrono>
#include <boost/date_time.hpp>

namespace boost { 
  namespace date_time2 {

    // template <typename T>
    // void range_check(std::string unit, T min, T max, T value)
    // {
    //   if (value > max || value < min) {
    // 	throw std::out_of_range(unit + " is out of range " 
    // 				+ std::to_string(min) + "..." + std::to_string(max)
    // 				+ ": " + std::to_string(value));
      
    //   }
    // }

    // struct gregorian_calendar
    // {
    //   static constexpr uint16_t year_min() { return 1400; } //todo temporary
    //   static constexpr uint16_t year_max() { return 10000; }
    //   static constexpr uint8_t  month_min() { return 1; }
    //   static constexpr uint8_t  month_max() { return 12; }
    //   static constexpr uint8_t  day_of_month_min() { return 1; }
    //   static constexpr uint8_t  day_of_month_max() { return 31; }

    //   static void validate_ymd(uint16_t year, uint8_t month, uint8_t day) 
    //   { 
    // 	range_check("year", year_min(), year_max(), year);
    // 	range_check("month", month_min(), month_max(), month);
    // 	range_check("day",  day_of_month_min(), day_of_month_max(), day);
    //   }


    // };
    


    /** Type used by the date::to function to allow for single
     *  parameter conversions by default
     */
    //    struct no_formatter {};

    class time_facet 
    {

    };

    class nanotime 
    {
    public:
      //      typedef gregorian_calendar calendar;
      enum checking { NOT_CHECKED, CHECKED };

      // ///Maximum time representable by the time type
      // static time max_time()
      // {
      // 	return time(year_max()-1, month_max(), day_of_month_max());
      // }
      // ///Minimum time representable by the time type
      // static time min_time()
      // {
      // 	return time(year_min(), month_min(), day_of_month_min());
      // }
      // ///Zero time for the represented calendar
      // static time epoch() {
      // 	return min_time();
      // }
      void from_ymd(const year_month_day& ymd, checking check)
      {
	// if (check==CHECKED) {
	//   calendar::valitime_ymd(ymd.year, ymd.month, ymd.day_of_month);
	//   d_ = boost::gregorian::date(ymd.year, ymd.month, ymd.day_of_month);
	//   return;
	// }
	// //nocheck / noexcept route...sets to epoch
	// try {
	//   d_ = boost::gregorian::date(ymd.year, ymd.month, ymd.day_of_month);
	// }
	// catch(...) {
	//   *this = min_date();
	// }
	// //    std::cout << d_ << std::endl;
	// //    std::cout << "int constructor: " << ymd << std::endl;
      }

      nanotime(boost::posix_time::ptime pt) //conversion from boost date time v1
      {
	t_ = pt;
      }

      //todo - this is probably an issue since time_t is probably just a typedef...
      nanotime(std::time_t tt) 
      {
	t_ =  boost::posix_time::from_time_t(tt);
      }

      ///no except, non checking variant of contstructor from date time
      ///constructs time at 00:00:00 of the date
      nanotime(const date& d) noexcept
      {
	boost::gregorian::date bd1 = d.to<boost::gregorian::date>();
	t_ = boost::posix_time::ptime(bd1);

      }

      // ///throws an exception if time doesn’t validate
      // time(uint16_t year, uint8_t month, uint8_t day, checking check=CHECKED)
      // {
      // 	from_ymd(year_month_day(year,month,day), check);
      // }
  

      // time(const year_month_day& ymd) noexcept
      // {
      // 	from_ymd(ymd, NOT_CHECKED);
      // 	//    std::cout << "ymd constructor: " << ymd << std::endl;
      // }

      // // todo: it would be nice to have one of these as noexcept
      // // the problem being that this makes it almost impossible
      // // to have checking be the default 
      // time(const year_month_day& ymd, checking check)
      // {
      // 	from_ymd(ymd, check);
      // 	//    std::cout << "ymd constructor: " << ymd << std::endl;
      // }
  
      // // a flexible string conversion method
      // template<typename charT=char, typename facet=time_facet>
      // std::basic_string<charT>
      // to_string(const facet& f) const
      // {
      // 	std::ostringstream ss;
      // 	ss.imbue(std::locale(ss.getloc(), new boost::gregorian::time_facet("%Y %m %d")));
      // 	ss << d_;
      // 	return ss.str();
      // }

      // /// Flexible string conversion method
      // template<typename charT=char>
      // std::basic_string<charT>
      // to_string() const
      // {
      // 	std::ostringstream ss;
      // 	ss.imbue(std::locale(ss.getloc(), new boost::gregorian::time_facet("%Y %m %d")));
      // 	ss << d_;
      // 	return ss.str();
      // }
      
      // /** Convert to the year-month-day type
      //  */
      // year_month_day to_year_month_day() const
      // {
      // 	boost::gregorian::greg_year_month_day ymd = d_.year_month_day();
      // 	return year_month_day(ymd.year, ymd.month , ymd.day); 
      // }

      // /** Templated conversion function -- specilize an implementation
      //  *  for a new type to facilitate conversions. This variation
      //  *  supports the passing of a formatting object to provide for
      //  *  things like string conversions which have flexible formats
      //  */
      // template<typename T, typename Format>
      // T to(const Format& format) const
      // {
      // 	std::cout << "WARNING....undefined time conversion called " << std::endl;
      // 	//static_assert(false, "This signature is here for speciazialition only");
      // }

      // /** Templated conversion function -- specilize an implementation
      //  *  for a new type to facilitate conversions
      //  */
      // template<typename T>
      // T to() const
      // {
      // 	std::cout << "WARNING....undefined time conversion called " << std::endl;
      // 	//static_assert(false, "This signature is here for speciazialition only");
      // }

      // /** Templated constructor which can be overridden to provide new and unique
      //  *  ways to construct a time custom to a program or project.  Most standard
      //  *  ways to construct a time specialize this constructor, often using from_ymd
      //  *  method to initialize.  
      //  */
      // template<typename T>
      // explicit time(const T& t, checking check=CHECKED) //todo deal with noexcept
      // {
      // 	from_ymd(year_month_day(t), check); 
      // }


      /// Trivial move constructor
      nanotime(nanotime&&) noexcept = default;

      /// Trivial copy constructor
      nanotime(const nanotime&) noexcept = default;

      /// Trivial assignment
      nanotime& operator=(const nanotime&) noexcept = default;

      bool operator==(const nanotime& rhs) const { return t_ == rhs.t_; }
      bool operator!=(const nanotime& rhs) const { return t_ != rhs.t_; }
      bool operator>(const nanotime& rhs) const  { return t_ > rhs.t_; }
      bool operator>=(const nanotime& rhs) const { return t_ >= rhs.t_; }
      bool operator<(const nanotime& rhs) const  { return t_ < rhs.t_; }
      bool operator<=(const nanotime& rhs) const { return t_ <= rhs.t_; }

      ///todo -- needs to a template on duration type...
      // time operator-(const days& rhs) const;
      // time operator+(const days& rhs) const;
      // time operator-(const weeks& rhs) const;
      // time operator+(const weeks& rhs) const;
      //      days operator-(const time& rhs) const { return d_ - rhs.d_; }

      /// increment / decrement operators
      // time& operator--() { d_ = d_ - boost::gregorian::days(1); return *this; }
      // time operator--(int) { time tmp(*this); operator--(); return tmp; }
      // time& operator++() { d_ = d_ + boost::gregorian::days(1); return *this; }
      // time operator++(int) { time tmp(*this); operator++(); return tmp; }

      // /** Calculate the days until another date or weekday -- result is negative 
      //  * if parameter represents a date before this date.
      //  * To use template form T must have a to<date> conversion, otherwise
      //  * a specialization should be written.
      //  */
      // template<typename T>
      // days days_until(const T& d) const
      // {
      // 	date target(d);
      // 	//DEBUG std::cout << "date: " << d_ << " target: " << target.qd_ << " days: " << (target.d_ - d_) << std::endl;
      // 	return target.d_ - d_;
      // }
      

      // /// Return the number of days to the date or weekday before -- inverse of days_until
      // template<typename T>
      // days days_before(const T& d) const
      // {
      // 	date target(d);
      // 	//DEBUG std::cout << "date: " << d_ << " target: " << target.qd_ << " days: " << (target.d_ - d_) << std::endl;
      // 	return d_ - target.d_;
      // }
      // //todo interface
      // //      days days_before(weekdays weekday) const;
      // // do this with operator- ?
      // //      days days_before(date d) const;
      // // this or a template?
      // //      days days_until(year_month_day ymd) const;
      // //      days days_before(year_month_day ymd) const;

      // /// Calculate the date of next given weekday
      // date next(weekdays wd) const;
      // date previous(weekdays wd) const;

      // date end_of_month() const;

      boost::posix_time::ptime t_; //temp implementation
    };

    // std::ostream& operator<<(std::ostream& os, const date& d)
    // {
    //   os << d.to_year_month_day();
    //   return os;
    // }


    // template<>
    // std::basic_string<char>
    // date::to_string<char,date_facet>(const date_facet& f) const
    // {
    //   std::ostringstream ss;
    //   ss.imbue(std::locale(ss.getloc(), new boost::gregorian::date_facet("%Y %m %d")));
    //   ss << d_;
    //   return ss.str();
    // }


    // template<>
    // std::string
    // date::to<std::string>() const
    // {
    //   return this->to_string();
    // }


    // /** Templated conversion function -- specilize an implementation
    //  *  for a new type and format to facilitate conversions. This variation
    //  *  supports the passing of a formatting object to provide for
    //  *  things like string conversions which have flexible formats
    //  *
    //  * todo -- still unsure if this belongs here or the i/o goes in 
    //  *         the auxilary types
    //  */
    // template<>
    // std::string
    // date::to<std::string, iso_year_month_day::ISO_FORMAT>(const iso_year_month_day::ISO_FORMAT& format) const
    // {
    //   year_month_day ymd(this->to_year_month_day());
    //   std::string year(std::to_string(ymd.year));
    //   std::string month, day;
    //   if (ymd.month < 10) { month = '0'; }
    //   month += std::to_string(ymd.month);
    //   if (ymd.day_of_month < 10) { day = '0'; }
    //   day += std::to_string(ymd.day_of_month);
    //   if (format == iso_year_month_day::ISO_NORMAL) {
    // 	return year+month+day;
    //   }
    //   //extended form
    //   return year+"-"+month+"-"+day;
    // }

    // template<>
    // year_month_day
    // date::to<year_month_day>() const
    // {
    //   return this->to_year_month_day();
    // }


    // //not needed because generic version works
    // // template<>
    // // date::date<std::tm>(const std::tm& theTM, checking check)
    // // {
    // //   from_ymd(year_month_day(theTM), check); //implicit year_month_day construction
    // // }

    // template<>
    // std::tm
    // date::to<std::tm>() const
    // {
    //   std::tm t;
    //   year_month_day ymd = this->to_year_month_day();
    //   t.tm_year = ymd.year - 1900;
    //   t.tm_mon = ymd.month - 1;
    //   t.tm_mday= ymd.day_of_month; 
    //   return t;
    // }

    // template<>
    // date::date<std::tuple<int,int,int>>(const std::tuple<int,int,int>& ymd, checking check)
    // {
    //   from_ymd(year_month_day(ymd), check); 
    // }

    // /// Template specialization to convert date to tuple of ints with year, month, day_of_month
    // template<>
    // std::tuple<int,int,int>
    // date::to<std::tuple<int,int,int>>() const
    // {
    //   year_month_day ymd = this->to_year_month_day();
    //   std::tuple<int,int,int> t(ymd.year, ymd.month, ymd.day_of_month);
    //   return t;
    // }

    // /// Template specialization to construct a date from a chrono::system_clock::time_point
    // template<>
    // date::date<std::chrono::system_clock::time_point>(const std::chrono::system_clock::time_point& tp, checking check)
    // {
    //   using namespace std::chrono;
    //   std::time_t tt = system_clock::to_time_t(tp);
    //   from_time_t(tt);
    // }

    // /// Specialization to allow construction from a iso_week_number representation Sunday of 51st week 2014 
    // template<>
    // date::date<iso_week_number>(const iso_week_number& wn, checking check)
    // {
    //   //todo fix me..
    // }

    // ///Specialization to allow conversions from boost date time v1 gregorian::date
    // template<>
    // date::date<boost::gregorian::date>(const boost::gregorian::date& bd, checking check)
    // {
    //   d_ = bd;
    // }


    // ///Specialization to allow conversions to boost date time v1 gregorian::date
    // template<>
    // boost::gregorian::date
    // date::to<boost::gregorian::date>() const
    // {
    //   return d_;
    // }


    // ///Specialization to allow conversions from boost date_time  v1 posix_time::ptime
    // template<>
    // date::date<boost::posix_time::ptime>(const boost::posix_time::ptime& t, checking check)
    // {
    //   d_ = t.date(); //todo fix the check -- what to do with nadt values from v1?
    // }


    // ///Specialization to allow conversions to boost date_time v1 posix_time::ptime
    // template<>
    // boost::posix_time::ptime
    // date::to<boost::posix_time::ptime>() const
    // {
    //   return boost::posix_time::ptime(d_);
    // }

    // /// Specialization to construct from a day of week spec eg: First Tue in Jan 2014
    // template<>
    // date::date<day_of_week>(const day_of_week& dow, checking check)
    // {
    //   year_month_day ymd(dow.to<year_month_day>());
    //   from_ymd(ymd, check); 
    // }

    // /// Specialization to construct from closest day of week spec eg: First Tue in Jan 2014
    // template<>
    // date::date<closest_day_of_week>(const closest_day_of_week& cdw, checking check)
    // {

    //   year_month_day ymd(cdw.to<year_month_day>());
    //   from_ymd(ymd, check); 
    // }
    
    // /// Specialization to support day of year construction 
    // template<>
    // date::date<day_of_year>(const day_of_year& doy, checking check)
    // {
    //   from_ymd(year_month_day(doy.to<year_month_day>()), check); 
    // }

    // /// Specialization of days_until for date -- slight efficiency since no Conversion required
    // template<>
    // days 
    // date::days_until<date>(const date& target) const
    // {
    //   return target.d_ - d_;
    // }

    // ///Specialization of days_until for weekdays so you can write d.day_until(Sun);
    // template<>
    // days
    // date::days_until<weekdays>(const weekdays& wd) const
    // {
    //   year_month_day ymd = this->to_year_month_day();
    //   closest_day_of_week cdw(wd, After, ymd);
    //   date target(cdw);
    //   return days_until<date>(target);
    // }

    // /// Specialization of days_before for date -- slight efficiency since no Conversion required
    // template<>
    // days 
    // date::days_before<date>(const date& target) const
    // {
    //   return d_ - target.d_;
    // }
    // /// Specialization of days_before for weekdays so you can write d.day_before(Sun);
    // template<>
    // days
    // date::days_before<weekdays>(const weekdays& wd) const
    // {
    //   year_month_day ymd = this->to_year_month_day();
    //   closest_day_of_week cdw(wd, Before, ymd);
    //   date target(cdw);
    //   return -days_until<date>(target); 
    // }

    // /// Arithmetic subtraction operation with weeks duration type
    // inline
    // date 
    // date::operator-(const weeks& rhs) const
    // {
    //   return date(d_ - rhs); 
    // }

    // /// Arithmetic addition operation with weeks duration type
    // inline
    // date 
    // date::operator+(const weeks& rhs) const
    // {
    //   return date(d_ + rhs); 
    // }

    // /// Arithmetic subtraction operation with days duration type
    // inline
    // date 
    // date::operator-(const days& rhs) const 
    // { 
    //   return date(d_ - rhs); 
    // }
    
    // /// Arithmetic addition operation with days duration type
    // inline
    // date 
    // date::operator+(const days& rhs) const 
    // { 
    //   return date(d_ + rhs); 
    // }

    // /// Calculate the date of next given weekday eg: next Thu
    // inline
    // date 
    // date::next(weekdays wd) const
    // {
    //   days dist = this->days_until(wd);
    //   return *this + dist;
    // }

    // /// Calculate the previous weekday eg: previous Thu
    // inline
    // date
    // date::previous(weekdays wd) const
    // {
    //   days dist = this->days_before(wd);
    //   return *this - dist;
    // }

    // ///Calculate the end of month
    // inline
    // date 
    // date::end_of_month() const
    // {
    //   return date(d_.end_of_month());
    // }


  } //namespace date_time2
} //namespace boost
#endif
