#ifndef BDT2_TEST_CONST_EXPR_HPP__
#define BDT2_TEST_CONST_EXPR_HPP__

#include "boost/date_time/v2/day_of_year.hpp"
#include "testfrmwk.hpp"


void test_date_algo_const_expr() {
  using namespace boost::date_time2;
  using std::cout;
  using std::endl;

  {
    constexpr int i = month_from_year_and_day(2002, 321);
    check("constexpr:month_from_year_and_day - constexpr - 2002-321 == 11", 
	  i == 11);
  }
  {
    constexpr bool b = is_leap_year(1404);
    check("constexpr:is_leap_year - constexpr -1404 is a leap year", 
	  b == true);
  }
  {
    constexpr bool b = is_leap_year(2014);
    check("constexpr:is_leap_year - constexpr -2014 is NOT a leap year", 
	  b == false);
  }

  {
    constexpr int i = end_of_month_day(1999, 2);
    check("constexpr:end_of_month_day - constexpr - 28 days in month Feb 1999", 
	  i == 28);

  }
  {
    constexpr int i = end_of_month_day(2000, 2);
    check("constexpr:end_of_month_day - constexpr - 29 days in month Feb 2000", 
	  i == 29);
  }

  {
    constexpr auto mnt_day = month_and_day_from_year_doy(2014, 59);
    check("constexpr:month_and_day_from_year_doy - 2014/59 - 2/28 ", 
	  mnt_day == std::pair<int,int>(2,28));
  }

}

void test_misc_const_expr()
{
  using namespace boost::date_time2;
  
  {
    //assembly for the next 2 lines...nice!
    // 00000000004024eb <test_misc_const_expr()>:
    //   4024eb:       55                      push   %rbp
    //   4024ec:       48 89 e5                mov    %rsp,%rbp
    //   4024ef:       66 c7 45 e0 de 07       movw   $0x7de,-0x20(%rbp)
    //   4024f5:       66 c7 45 e2 3b 00       movw   $0x3b,-0x1e(%rbp)
    //   4024fb:       66 c7 45 f0 de 07       movw   $0x7de,-0x10(%rbp)
    //   402501:       c6 45 f2 02             movb   $0x2,-0xe(%rbp)
    //   402505:       c6 45 f3 1c             movb   $0x1c,-0xd(%rbp)
    //   402509:       90                      nop
    constexpr day_of_year    doy(2014,59); //2014-feb-28
    constexpr year_month_day ymd(doy.to<year_month_day>()); 
    check("constexpr:doy to ymd - 2014/59 - 2/28 ", 
     	  ymd.month==2 && ymd.day_of_month == 28);
  }

}

void test_const_expr()
{
  test_date_algo_const_expr();
  test_misc_const_expr();
}






#endif
