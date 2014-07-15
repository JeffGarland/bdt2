#ifndef BDT2_DOY_HPP__
#define BDT2_DOY_HPP__

#include "year_month_day.hpp"


namespace boost { 
  namespace date_time2 {

    ///Specify a year and a day eg: 2013 1 == Jan 1, 2013 365 == Dec 31
    struct day_of_year
    {
      day_of_year(uint16_t y, uint16_t d) noexcept :
	year(y),
	day(d)
      {}
      day_of_year() noexcept {}
      uint16_t year = 10001;
      uint16_t day  = 367;

      template<typename T>
      T to() const
      {
	std::cout << "WARNING....undefined ymd conversion called " << std::endl;
	//static_assert(false, "This signature is here for speciazialition only");
      }
    };


    ///Conversion to a year month day form
    template<>
    year_month_day
    day_of_year::to() const
    {
      //calculate month and day from day number
      //todo -- this algorithm is a bit of a hack...
      if (this->day <= 31+28) { //up to end of feb don't need to check leap year
	if (this->day <= 31) return year_month_day(this->year, 1, this->day);
	return year_month_day(this->year, 2, this->day-31);
      }
      bool is_leap =  boost::gregorian::gregorian_calendar::is_leap_year(this->year);
      //DEBUG      std::cout << "TRACE: year " << this->year << " doy " << this->day << std::endl;

      //Quick table of last day of year to month mapping leap year
      //Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec
      // 31  60  91 121 152 182 213 244 274 305 335 366 
      //following is a kind of binary search
      if (is_leap) {
	if (this->day <=182) {
	  if (this->day <= 60) return year_month_day(this->year, 2, this->day-31);
	  if (this->day <= 91) return year_month_day(this->year, 3, this->day-60);
	  if (this->day <= 121) return year_month_day(this->year, 4, this->day-91);
	  if (this->day <= 152) return year_month_day(this->year, 5, this->day-121);
	  //if (this->day <= 182) 
	  return year_month_day(this->year, 6, this->day-152);
	}
	else {
	  if (this->day <= 213) return year_month_day(this->year, 7, this->day-182);
	  if (this->day <= 244) return year_month_day(this->year, 8, this->day-213);
	  if (this->day <= 274) return year_month_day(this->year, 9, this->day-244);
 	  if (this->day <= 305) return year_month_day(this->year, 10, this->day-274);
 	  if (this->day <= 335) return year_month_day(this->year, 11, this->day-305);
	  return year_month_day(this->year, 12, this->day-335);
	}
      }
      //Quick table of last day of year to month mapping non leap year
      //Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec
      // 31  59  90 120 151 181 212 243 273 304 334 365 
      else { //not leap 
	if (this->day <= 212) {
	  if (this->day <= 90) return year_month_day(this->year, 3, this->day-59);
	  if (this->day <= 120) return year_month_day(this->year, 4, this->day-90);
	  if (this->day <= 151) return year_month_day(this->year, 5, this->day-120);
	  if (this->day <= 181) return year_month_day(this->year, 6, this->day-151);
	  //if (this->day <= 212) 
	  return year_month_day(this->year, 7, this->day-181);
	} 
	else { //> 212
	  if (this->day <= 243) return year_month_day(this->year, 8, this->day-212);
	  if (this->day <= 273) return year_month_day(this->year, 9, this->day-243);
	  if (this->day <= 304) return year_month_day(this->year, 10, this->day-273);
	  if (this->day <= 334) return year_month_day(this->year, 11, this->day-304);
	}
      //the only option left after dropping out of not leap path...
      return year_month_day(this->year, 12, this->day-334);
      }
    }

  } //namespace date_time2
} //namespace boost
#endif
