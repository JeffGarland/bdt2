#ifndef BDT2_TEST_DATE
#define BDT2_TEST_DATE

//#include "ext_tm.hpp"
#include "boost/date_time/v2/date.hpp"
#include <iostream>
#include "testfrmwk.hpp"
#include <boost/date_time/gregorian/gregorian_types.hpp>

// this is an example of a user extension
class yesterday {
public:
  yesterday() 
  {
    using  boost::gregorian::day_clock;
    using  boost::gregorian::date;
    //call the clock to set fields
    d_ = day_clock::universal_day() - boost::gregorian::days(1);
    
  }
  operator boost::date_time2::date()  const
  {
    return boost::date_time2::date(d_);
  }
  boost::gregorian::date d_;
};


namespace boost { namespace date_time2 {

    //Specialization to allow conversions from yesterday 
    template<>
    date::date<yesterday>(const yesterday& yd, checking check)
    {
      //never check this as it's always good
      d_ = yd.d_; //-- hack impl that will break...
    }
}}//namespace boost::date_time2



void test_min_max_epoch()
{

 using namespace boost::date_time2;
  using std::cout;
  using std::endl;

  {
    check("max date" , date::max_date() == date(9999,12,31));    
    check("min date" , date::min_date() == date(1400,1,1)); //todo temporary
    check("epoch date" , date::epoch() == date(1400,1,1)); //todo temporary
    
  }

}

void test_basic_construct_except()
{
  using namespace boost::date_time2;
  using std::cout;
  using std::endl;

 try {
    tm t;
    t.tm_year = 10012;
    date d(t, date::CHECKED);
    check("ymd checker for bad year" , false);
  }
  catch(std::exception& e) {
    check(std::string("ymd checker for bad year except text is: ") + e.what(), true);
  }
  
  try {
    year_month_day ymd1(2010, 14, 1); //bad month
    date d(ymd1, date::CHECKED);
    check("ymd checker for bad month-failure" , false);
  }
  catch(std::exception& e) {
    check(std::string("ymd checker for bad month except text is: ") + e.what(), true);
  }

  try {
    year_month_day ymd1(2010, 12, 32); //bad day
    date d(ymd1, date::CHECKED);
    check("ymd checker for bad day--fail", false);
  }
  catch(std::exception& e) {
    check(std::string("ymd checker for bad day except text is: ") + e.what(), true);
  }
  {
    tm t;
    t.tm_year = 113;//2013
    t.tm_mon = 11; //Dec
    t.tm_mday = 30; 
    date d(t);
    date d2(2013, 12, 30);
    check("check good construction from tm", d==d2);
    tm t2 = d.to<std::tm>();
    check("convert to tm", t2.tm_year == 113 && t2.tm_mon == 11 && t2.tm_mday == 30);
    
  }

}

void test_date() 
{
  test_min_max_epoch();
  test_basic_construct_except();
  //todo hoist more parts to sub functions

  using namespace boost::date_time2;
  using std::cout;
  using std::endl;


  {
    date d(2020, 12, 31);
    std::string s(d.to_string());
    check("check to_string " + d.to_string(), d.to_string() == "2020 12 31");

    check("check to<std::string> ", d.to<std::string>() == "2020 12 31");


    date d2(d);
    check("date copy constructor ", d2.to_string() == "2020 12 31");
  }

  {
    date d(1970, 1, 1);
    year_month_day ymd = d.to_year_month_day();
    std::cout << "to ymd: " << d.to_string() << std::endl;
    check("check to_year_month_day " + d.to_string(), ymd.year == 1970);

    year_month_day ymd2 = d.to<year_month_day>();
    check("check to<year_month_day> ", ymd == ymd2);
    
  }
  {
    std::tuple<int, int, int> t_ymd(1900, 1, 1);
    year_month_day ymd(t_ymd);
    //    std::cout << "tuple" << ymd
    date d(ymd);
    std::cout << "tuple" << d << std::endl;
    check("check tuple date construction via ymd", date(1900,1,1) == d);
  }
  {
    std::tuple<int, int, int> t_ymd(1900, 1, 1);
    date d(t_ymd);
    check("check tuple date construction ", date(1900,1,1) == d);
    check("check tuple conversion ", std::tuple<int, int, int>(1900,1,1) == d.to<std::tuple<int,int,int>>());
    std::tuple<int,int,int> ymd2 = d.to<std::tuple<int,int,int>>();
    check("check tuple conversion2 ", std::get<0>(ymd2) == 1900 && std::get<1>(ymd2) == 1);
  }
  {
    std::chrono::system_clock::time_point tp = std::chrono::system_clock::now();
    date d(tp);
    boost::gregorian::date bd(boost::gregorian::day_clock::universal_day());
    std::cout << "day clock: " << bd << std::endl;
    std::cout << "chrono based date is: " << d << std::endl;
    check("check construction from chrono timepoint ", d == date(bd));
  }

  {
    boost::gregorian::date bd(1900, 1, 1);
    date d(bd);
    check("check boost date construction ", date(1900,1,1) == d);

    boost::gregorian::date bd1 = d.to<boost::gregorian::date>();
    check("check boost date conversion ", bd1 == bd);

    boost::posix_time::ptime pt(bd);
    date d2(bd);
    check("check boost ptime construction ", date(1900,1,1) == d2);

    boost::posix_time::ptime pt1 = d.to<boost::posix_time::ptime>();
    check("check boost ptime conversion ", pt1 == pt);
  }
  //Test Days until, next
  {
    date d(2013, Jan, 1);
    
    check("days_until with date ", days(1) == d.days_until(date(2013, Jan, 2)));
    check("days_until with year_month_day ", days(1) == d.days_until(year_month_day(2013, Jan, 2)));
    check("days_until with gregorian::date ", days(1) == d.days_until(boost::gregorian::date(2013, Jan, 2)));
    //    cout << "FAIL: days_until " << date(day_of_week(2013, Jan, First, Tue)) << endl;
    check("days_until day_of_week ", days(1) == d.days_until(day_of_week(First, Wed, Jan, 2013))); 
    check("days_until weekday  ", days(1) == d.days_until(Wed)); 
    check("days_until weekday  ", days(2) == d.days_until(Thu)); 
    check("days_until weekday  ", days(4) == d.days_until(Sat)); 

    check("next weekday  ", d+days(4) == d.next(Sat)); 

  }
  
  {
    date d(2014, Apr, 1); //Tue
    days db = d.days_before(Mon); 
    check("days before 1 ", db == days(1)); 

  }
  
  {
    date d(2014, Apr, 1); //Tues
    date d2 = d.previous(Mon); 
    check("previous ", d2 == date(2014, Mar, 31)); 
    
  }
  //Test addition and subtraction of dates, days
  {
    date d1(2013, Jan, 1);
    date d2(2013, Jan, 2);
    check("test subtraction positive ", days(1) == d2-d1); 
    check("test subtraction negative", days(-1) == d1-d2); 
    check("test addition of days", d1 + days(1) == d2); 
    check("test subtraction of days", d2 - days(1) == d1); 
   
  }
  //Test addition and subtraction of weeks
  {
    date d1(2013, Jan, 1);
    date d2(2013, Jan, 8);
    check("test addition of weeks", d1 + weeks(3) == d1 + days(21)); 
    check("test addition of weeks", d1 + weeks(1) == d2); 
    check("test subtraction of weeks", d2 - weeks(1) == d1); 
   
  }
  //check operator-- and operator++
  {
    date d1(2013, Jan, 1);
    date d2(2013, Jan, 1);
    --d2;
    d1--;
    check("prefix and postfix--", d1 == d2); 
    d2++;
    ++d1;
    check("prefix and postfix++", d1 == d2); 
    //    std::cout << "postfix " << d2 << std::endl;

    date di(2014, Apr, 1);
    date end = di+days(7);
    for (; di < end; di++) {
      std::cout << "iterate: " << di << std::endl;
    }
    check("iteration", di == date(2014, Apr, 8));

  }
  //do a map emplace -- move construct
  {
    std::map<date, int> dmap;
    dmap.emplace(date(2014,Apr,8), 1);
    check("map emplace - move construct", dmap.find(date(2014, Apr, 8)) != dmap.end());
    
  }
  //test a user extension -- yesterday
  { 
    std::chrono::system_clock::time_point tp = std::chrono::system_clock::now();
    date today(tp);
    --today;
    date yd = yesterday();
    // std::cout << "FAIL: today" << today << std::endl;
    // std::cout << "FAIL: yester" << yd << std::endl;
    check("test of user extension", today == yd); 
    
    
  }
  //test iso string conversions
  {
    date d(2014, Apr, 1);
    std::string s = d.to<std::string>(iso_year_month_day::ISO_NORMAL);
    cout << "ISO NORMAL: " << s << endl;
    check("iso normal string conversion", s == "20140401"); 
    std::string s2 = d.to<std::string>(iso_year_month_day::ISO_EXTENDED);
    check("iso extended string conversion", s2 == "2014-04-01"); 
    
  }

  //end of month
  {
    date d1(2014, Jan, 1);
    check("end of month", d1.end_of_month() == date(2014, Jan, 31)); 

    date d2(2000, Feb, 20);
    check("end of month", d2.end_of_month() == date(2000, Feb, 29)); 

    date d3(2000, Dec, 20);
    check("end of month", d3.end_of_month() == date(2000, Dec, 31)); 

    date d4(2004, Feb, 20);
    check("end of month", d4.end_of_month() == date(2004, Feb, 29)); 

    date d5(2014, Dec, 20);
    check("end of month", d5.end_of_month() == date(2014, Dec, 31)); 
   
  }
}


#endif
