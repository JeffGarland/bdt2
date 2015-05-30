#ifndef BDT2_DURATIONS_HPP_
#define BDT2_DURATIONS_HPP_

#include <cstdlib> //for int32_t
#include <chrono>  
#include <boost/date_time.hpp> //todo to be removed!

namespace boost { 
  namespace date_time2 {


    ///Chrono ratio for 1 day -- basically number seconds in a day
    typedef std::ratio<86400,1> day_ratio;

    /** Use chrono to define day length duration type
     *  This type provides for basic date based math
     *  and algorihms to write code like this:
     *@code
     *
     *  date d(...);
     *  d += days(5);
     *  d -= days(2);
     *
     *  days c1 = d.days_until(day_of_week(2013, Jan, First, Wed));
     *  days c2 = d.days_until(Wed);
     *  days c3 = d.days_until(year_month_day("2004/10/01"));
     *
     *@endcode
     */
    typedef std::chrono::duration<int32_t, day_ratio> days;


    ///Chrono ratio for 1 week -- seconds in a day * 7 days per week
    typedef std::ratio<86400*7,1> week_ratio;
    

    /** Use chrono to define week length duration type
     *  This type provides for basic date based math
     *  and algorihms to write code like this:
     *@code
     *
     *  date d(...);
     *  d += weeks(5);
     *  d -= weeks(2);
     *
     *@endcode
     */
    typedef std::chrono::duration<int32_t, week_ratio> weeks;


  } //namespace date_time2
} //namespace boost
#endif
