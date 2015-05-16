#ifndef BDT2_DATE_ALGO_HPP__
#define BDT2_DATE_ALGO_HPP__

#include <boost/date_time.hpp> //todo replace/scope

namespace boost { 
  namespace date_time2 {

    
    /** Determine if the give year is a leap year.
     *@param num_type A number type with % and && operations
     */
    template<typename num_type>
    inline
    constexpr 
    bool is_leap_year(num_type year)
    {
      //divisible by 4, not if divisible by 100, but true if divisible by 400
      return (!(year % 4))  && ((year % 100) || (!(year % 400)));
    }


    /** Determine the last day of the month
     *@param num_type A number type with % and && operations
     *@param year - The year to get the end of month
     *@param month - The month to get the end of month
     */
    template<typename num_type>
    //    constexpr -- cannot get g++ to accept this as constexpr function
    num_type
    end_of_month_day(num_type year, num_type month)
    {
      
      switch (month) {
      case 2:
	if (is_leap_year(year)) {
	  return 29;
	} else {
	  return 28;
	};
      case 4:
      case 6:
      case 9:
      case 11:
	return 30;
      default:
	return 31;
      };
      
      //other alternate, but ultimately not compatible constexpr functions
      //num_type eomd [] = { 31, 28, 31, 30, 31, 30, 31, 30, 31, 31, 30, 31 };
      //return eomd[month-1];


      // num_type ret = 31;
      // if (month == 2 ) {
      //  	if (is_leap_year(year)) {
      //  	  return num_type(29);
      // 	} else {
      //  	  return num_type(28);
      //  	}
      // }
      // if (month == 4 || month == 6 || month == 9 || month == 11) {
      // 	ret = 30;
      // }
      // return ret;
    }
  


    /** calculate the month from the year and day in the year taking into account
     *  leap years.  So 2014,1 -> 1; 2004,60 -> 2 (feb 29)
     */
    template<typename num_type>
    inline
    //todo    constexpr  -- g++ won't allow...
    num_type month_from_year_and_day(num_type year, num_type day_of_year)
    {
      
      //calculate month and day from day number
      //todo -- this algorithm is a bit of a hack...
      if (day_of_year <= 31+28) { //up to end of feb don't need to check leap year
	if (day_of_year <= 31) return 1;
	return 2;
      }
      bool is_leap =  is_leap_year(year);
      //DEBUG      std::cout << "TRACE: year " << year << " doy " << day_of_year << std::endl;

      
      //Quick table of last day of year to month mapping leap year
      //Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec
      // 31  60  91 121 152 182 213 244 274 305 335 366 
      //following is a kind of binary search
      if (is_leap) {
	if (day_of_year <=182) {
	  if (day_of_year <= 60) return 2;
	  if (day_of_year <= 91) return 3;
	  if (day_of_year <= 121) return 4;
	  if (day_of_year <= 152) return 5;
	  //if (day_of_year <= 182) 
	  return 6;
	}
	else {
	  if (day_of_year <= 213) return 7;
	  if (day_of_year <= 244) return 8;
	  if (day_of_year <= 274) return 9;
 	  if (day_of_year <= 305) return 10;
 	  if (day_of_year <= 335) return 11;
	  return 12;
	}
      }
      //Quick table of last day of year to month mapping non leap year
      //Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec
      // 31  59  90 120 151 181 212 243 273 304 334 365 
      else { //not leap 
	if (day_of_year <= 212) {
	  if (day_of_year <= 90) return 3;
	  if (day_of_year <= 120) return 4;
	  if (day_of_year <= 151) return 5;
	  if (day_of_year <= 181) return 6;
	  //if (day_of_year <= 212) 
	  return 7;
	} 
	else { //> 212
	  if (day_of_year <= 243) return 8;
	  if (day_of_year <= 273) return 9;
	  if (day_of_year <= 304) return 10;
	  if (day_of_year <= 334) return 11;
	}
      //the only option left after dropping out of not leap path...
	return 12;

      }
    }



  } //namespace date_time2
} //namespace boost
#endif
