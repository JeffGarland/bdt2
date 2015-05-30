#ifndef BDT2_BDT_V1_CONVERT_HPP_
#define BDT2_BDT_V1_CONVERT_HPP_

//
//#include <boost/date_time/gregorian/gregorian.hpp>
//todo refine this
#include "year_month_day.hpp"
#include "date.hpp"
#include <boost/date_time.hpp>

namespace boost { 
  namespace date_time2 {



    ///Specialization to allow conversions from boost date time v1 gregorian::date
    template<>
    date::date<boost::gregorian::date>(const boost::gregorian::date& bd, checking check)
    {
      d_ = bd;
    }


    ///Specialization to allow conversions to boost date time v1 gregorian::date
    template<>
    boost::gregorian::date
    date::to<boost::gregorian::date>() const
    {
      return d_;
    }


    ///Specialization to allow conversions from boost date_time  v1 posix_time::ptime
    template<>
    date::date<boost::posix_time::ptime>(const boost::posix_time::ptime& t) noexcept
    {
      d_ = t.date(); //todo fix the check -- what to do with nadt values from v1?
    }


    ///Specialization to allow conversions to boost date_time v1 posix_time::ptime
    template<>
    boost::posix_time::ptime
    date::to<boost::posix_time::ptime>() const
    {
      return boost::posix_time::ptime(d_);
    }



  } //namespace date_time2
} //namespace boost
#endif


