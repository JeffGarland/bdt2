#ifndef BDT2_UTC_TIME_LABEL
#define BDT2_UTC_TIME_LABEL

#include <ctime>
#include <cstdlib> //for uint_8, etc
#include <string>


namespace boost { 
  namespace date_time2 {

    /// Type used to provided extended tm functions as part of boost date_time2.
    /// Provides the basis for performing I/O functions.  Extends the classic tm
    /// to include facilities for variable resolution fractional seconds as well
    /// as leap seconds.

    class utc_time_label 
    {
    public:
      enum class weekdays : uint8_t { SUN, MON, TUE, WED, THU, FRI, SAT };
      enum class resolutions : uint8_t {tenth, centi, milli, micro, nano, pico, femto, atto};

      uint8_t   sec_in_day = 61;              //<replaces tm_sec   - range 0-60
      uint8_t   minutes_in_hour = 61;         //<replaces tm_min   - range 0-60
      uint8_t   hours_in_day = 25;            //<replaces tm_hour  - range 0-24
      uint8_t   month = 0;                    //<replaces tm_month - range 1-12
      uint8_t   month_day = 0;                //<replaces tm_mon   - range 1-31
      weekdays  day_in_week = weekdays:: SUN; //<replaces tm_wday
      uint8_t   day_in_year = 0;              //<replaces tm_yday  - range 1-366
      int16_t   year = 0;                     //<replaces tm_year  - 0 == 0 AD;
      bool      is_dst = false;               //<replaces tm_isdst

      //addtions from standard tm
      uint8_t   week_num = 54;                //<range 0 to 53 
      resolutions resolution = resolutions::nano; //<resolution of frac_sec
      uint32_t  frac_sec = 0;                 //<count of fractional seconds since start of day -- todo atto sec/day?
      int8_t    leap_sec = 0;                 //<count of leap seconds to include -- typically 15 now
      std::string tz_zone_string{};           //<arbitrary string representing timezone
  
      //possibly overkill
      int8_t    utc_offset_hours = 24;        //<range 0 to 23
      int8_t    utc_offset_min = 60;          //<range 0 to 59
  
    };
  


    //   ///Default constructor -- sets things to bogus values.
    //   ext_tm() 
    //   {
    //     tm_sec  = 61;
    //     tm_min  = 61;
    //     tm_hour = 24;
    //     tm_mon  = 13;
    //     tm_year = 9999+1900;
    //     tm_mday = 32;
    //     tm_wday = 8;
    //     tm_yday = 367;
    //     tm_year = -1;
    //     tm_isdst = -1;
    //     //    tmx_frac_sec_resolution;
    //     tmx_frac_sec = 0;
    //     tmx_leap_sec = 0;

    //   }
    //   ///Construct things from integer values
    //   ext_tm(int32_t year, int32_t month, int32_t day, int32_t hour, bool isdst,
    //          int32_t min, int32_t sec, int32_t frac_sec, int8_t leap_sec) 
    //   {
    //   //   tm_year = year-1900; //adjust to 1900 epoch of tm;
    //   //   tm_mon = month -1;   //adjust to 0 based tm months
    //   //   tm_mday = day;
    //   //   tm_hour = hour;
    //   //   tm_min = min;
    //   //   tm_sec = sec;
    //   //   tm_yday = 0; //todo - requires a calendar...
    //   //   tm_wday = 0; //todo - requires a calendar...
    //   //   tm_isdst = 0;
    //   //   tmx_frac_sec = frac_sec;
    //   //   tmx_leap_sec = leap_sec;
    //   //   if (isdst) {
    //   //     tm_isdst = 1;
    //   //   }
    //   }

    //   ///Construct things from string values
    //   ext_tm(std::string year, std::string month, std::string day, 
    //          std::string hour, std::string min, std::string sec, 
    //          std::string frac_seconds)
    //   {
    //     // Make sure the year field has 4 digits.
    //     //
    //     if (year.size() < 4)
    //     {
    //       throw "bad date specification - not 4 digits in year.";
    //     }
    //     tm_year = std::atoi(year.c_str()) - 1900; //adjust to 1900 epoch of tm;
    //     tm_mon  = std::atoi(month.c_str()) - 1;
    //     tm_mday = std::atoi(day.c_str());
    //     tm_yday = 0; //todo
    //     tm_wday = 0; //todo
    //     tm_hour = std::atoi(hour.c_str());
    //     tm_min  = std::atoi(min.c_str());
    //     tm_sec  = std::atoi(sec.c_str());

 
    //     // std::string fs_string = "0.";
    //     // fs_string.append(frac_seconds);

    //     // double fs = std::atof(fs_string.c_str());
    //     // double us = fs * 1000000.0;

    //     // int32_t  max_precision = ;
    //     // microseconds = static_cast<uint32_t>(us);

    //     // while (microseconds > max_precision)
    //     // {
    //     //   microseconds /= 10;
    //     // }
  
    //   }

    //   /// Almost like a copy constructor build from a tm adding other fields 
    //   /// or defaulting to reasonable values
    //   ext_tm(const tm* const aTime, 
    //          int32_t usecs = 0)
    //   {
    //     tm_year = aTime->tm_year;
    //     tm_mon  = aTime->tm_mon;
    //     tm_mday = aTime->tm_mday;
    //     tm_hour = aTime->tm_hour;
    //     tm_min  = aTime->tm_min;
    //     tm_sec  = aTime->tm_sec;
    //     tm_yday = aTime->tm_yday;
    //     tm_wday = aTime->tm_wday;
    //     tm_isdst = aTime->tm_isdst;
    //     //    microseconds = usecs;
    //   }

    // private:
  
    //   ///Construct things from integer values
    //   void set_fields_no_adjust(int32_t year, int32_t month, int32_t day, 
    // 			    int32_t day_of_year, int32_t day_of_week,
    // 			    int32_t hour, int32_t min, int32_t sec, bool isdst,
    // 			    int32_t frac_sec, frac_sec_resolution fsr, int8_t leap_sec) 
    //   {
    //     tm_year = year;
    //     tm_mon = month;   //adjust to 0 based tm months
    //     tm_mday = day;
    //     tm_hour = hour;
    //     tm_min = min;
    //     tm_sec = sec;
    //     tm_yday = day_of_year;
    //     tm_wday = day_of_week;
    //     tm_isdst = 0;
    //     tmx_frac_sec = frac_sec;
    //     tmx_leap_sec = leap_sec;
    //     if (isdst) {
    //       tm_isdst = 1;
    //     }
    //   }


    // };

  } //namespace date_time2
} //namespace boost

#endif
