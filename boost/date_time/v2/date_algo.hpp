#ifndef BDT2_DATE_ALGO_HPP__
#define BDT2_DATE_ALGO_HPP__

#include <boost/date_time.hpp> //todo replace/scope

namespace boost { 
  namespace date_time2 {

    
    /** Determine if the give year is a leap year.
     * This function will be compile time only if used with constexpr
     *@param num_type A number type with % and && operations
     */
    template<typename num_type>
    inline
    constexpr
    bool
    is_leap_year(num_type year)
    {
      //divisible by 4, not if divisible by 100, but true if divisible by 400
      return (!(year % 4))  && ((year % 100) || (!(year % 400)));
    }

    namespace {
      constexpr
      int eomd [] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

      // last day of month in leap year

    }
    /** Determine the last day of the month
     * This function will be compile time only if used with constexpr
     *@param num_type A number type with % and && operations
     *@param year - The year to get the end of month
     *@param month - The month to get the end of month
     */
    template<typename num_type>
    constexpr
    num_type
    end_of_month_day(num_type year, num_type month)
    {
      //if feb & leap year then 29 else lookup in static table
      return ((month==2) && is_leap_year(year)) ? 29 : eomd[month-1];
    }
  

    /** calculate the month from the year and day in the year taking
     *  into account leap years.  So 2014,1 -> 1; 2004,60 -> 2 (feb 29)
     */
    template<typename num_type>
    inline
    constexpr  //requires g++-5 and above
    num_type
    month_from_year_and_day(num_type year, num_type day_of_year)
    {
      
      //calculate month and day from day number
      //todo -- this algorithm is a bit of a hack...done to satisfy constexpr
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


    /** Calculate the month and day_of_month using the year and
     *  day of year taking into account leap years.
     *  So 2014,1 -> 1,1; 2004,60 -> 2,29 (feb 29)
     */
    template<typename num_type>
    inline
    constexpr  //requires g++-5 and above
    std::pair<num_type, num_type>
    month_and_day_from_year_doy(num_type year, num_type day_of_year)
    {
      typedef std::pair<num_type, num_type> npair;

      //quick return on error
      if (day_of_year > 366) return std::pair<num_type, num_type>(0,0);

      //simple case of january -- immediately return
      if (day_of_year <= 31) return npair(1, day_of_year);

      constexpr int
	ldom_leap [] = { 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 };
      //last day of month in normal year
      constexpr int
	ldom      [] = { 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };

      bool is_leap =  is_leap_year(year);

      //calculate the approximate location in the month array
      //it will either be right on or one below -- subtract
      //one for zero indexed array.  Also works because
      //avoiding all less than 31...so this will always be
      //greater than 1
      short idx = (day_of_year/29) - 1;
      // std::cout << "algo: idx " << idx
      // 		<< " day_of_year " << day_of_year ;

      if (is_leap) {
	if (ldom_leap[idx] >= day_of_year) { //traverse back
	  idx--;
	}
	// std::cout << " idx2 " << idx
	// 	  << " ldom_leap[idx]  " << ldom_leap[idx]
	// 	  << std::endl;
	if (idx == 11) {
	  return npair(idx+1, day_of_year-ldom_leap[idx]);
	}
	return npair(idx+2, day_of_year-ldom_leap[idx]);
      }

      //regular year
      if (ldom[idx] >= day_of_year) { //traverse back
	idx--;
      }
      // std::cout << " idx2 " << idx
      // 		<< " ldom[idx]  " << ldom[idx]
      // 		<< std::endl;
      if (idx == 11) {
	return npair(idx+1, day_of_year-ldom[idx]);
      }
      return npair(idx+2, day_of_year-ldom[idx]);
    }
  } //namespace date_time2
} //namespace boost
#endif
