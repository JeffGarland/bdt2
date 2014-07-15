#ifndef BDT2_TEST_TIME
#define BDT2_TEST_TIME

//#include "ext_tm.hpp"
#include "utc_time_label.hpp"
#include <iostream>
#include "testfrmwk.hpp"

void test_time_t()
{

  
  // std::time_t tt(500000000); 
  // t18 = from_time_t(tt); //1985-11-5 0:53:20
  // check("time_t conversion of 500000000", 
  //       t18 == ptime(date(1985,11,5), time_duration(0,53,20)));
  
  // std::time_t tt1(1060483634); 
  // t18 = from_time_t(tt1); //2003-08-10 2:47:14
  // check("time_t conversion of 1060483634", 
  //       t18 == ptime(date(2003,8,10), time_duration(2,47,14)));
  
  // std::time_t tt2(1760483634); 
  // t18 = from_time_t(tt2); //2025-10-14 23:13:54
  // check("time_t conversion of 1760483634", 
  //       t18 == ptime(date(2025,10,14), time_duration(23,13,54)));
  
  // std::time_t tt3(1960483634); 
  // t18 = from_time_t(tt3); //2032-2-15 18:47:14
  // check("time_t conversion of 1960483634", 
  //       t18 == ptime(date(2032,2,15), time_duration(18,47,14)));

}

void test_utc_time_label() 
{
  using namespace boost::date_time2;
  using std::cout;
  using std::endl;
  //  test_time_t();


  //time_t conversions:
  {
    utc_time_label utc; //1970-1-1 0:0:0
    //    check("time_t conversion of 0", t.t_ == boost::posix_time::ptime(boost::gregorian::date(1970,1,1)));
  }

}





#endif
