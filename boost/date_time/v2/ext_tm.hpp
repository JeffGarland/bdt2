#ifndef BDT2_EXT_TM_HPP
#define BDT2_EXT_TM_HPP

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


    // template<typename CharT>
    // struct date_info
    // {
    //   typedef CharT char_type;
    //   const   CharT* separators;
    //   const   CharT* postfix;
    // };
    
    

    
    //And for time I need one of the date_tm types and then

    struct  time_tm  
    {
      time_tm() {
	tm_sec  = 61; //60 is valid second in leap seconds
	tm_min  = 60; 
	tm_hour = 24; //0...23
	tm_isdst = -1; //or maybe a bool false
	//    tmx_frac_sec_resolution;  hmm...might be part of the type...
	tm_frac_sec = 0; //count of fractional seconds
	tm_leap_sec = false;   // tell me this is a leap second   
      }
      uint8_t tm_sec; //60 is valid second in leap seconds
      uint8_t tm_min ; 
      uint8_t tm_hour; //0...23
      bool    tm_isdst = false; //or maybe a bool false
      int8_t tm_frac_sec_resolution;
      int32_t tm_frac_sec;
      bool    tm_leap_sec;
    };

  } //namespace date_time2
} //namespace boost
#endif
