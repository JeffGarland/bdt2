#ifndef BDT2_DOY_HPP__
#define BDT2_DOY_HPP__

#include "year_month_day.hpp"
#include "date_algo.hpp"

namespace boost { 
  namespace date_time2 {

    ///Specify a year and a day eg: 2013 1 == Jan 1, 2013 365 == Dec 31
    ///An alternative for construction of a date instead of year_month_day
    struct day_of_year
    {
      ///Default constructor -- sets to invalid values
      constexpr
      day_of_year() noexcept
      {}

      ///Construct a day of year
      ///@param y - The year
      ///@param d - The day of the year from 1 to 366
      constexpr
      day_of_year(uint16_t y, uint16_t d) noexcept :
	year(y),
        day(d)
      {}

      uint16_t year = 10001;  //out of range
      uint16_t day  = 367;

      ///Declare signature for specialization
      template<typename T>
      T to() const;
    };


    ///Conversion to a year month day form
    template<>
    constexpr
    year_month_day
    day_of_year::to() const
    {
      auto mnt_day = month_and_day_from_year_doy(this->year, this->day);
      return year_month_day(this->year, mnt_day.first, mnt_day.second);
    }

  } //namespace date_time2
} //namespace boost
#endif
