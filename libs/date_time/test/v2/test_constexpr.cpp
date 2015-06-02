
//#include "boost/date_time/v2/date_algo.hpp"
#include "boost/date_time/v2/year_month_day.hpp"
#include "test_constexpr.hpp"
#include <iostream>


//g++-5 -I../../../../ -std=c++14 test_constexpr.cpp
//objdump -d a.out 
/* results for is_leap_year

without constexpr this is main assembly
0000000000400846 <main>:
  ...
  40084e:	bf 7c 05 00 00       	mov    $0x57c,%edi
  400853:	e8 7a 00 00 00       	callq  4008d2 <_ZN5boost10date_time212is_leap_yearIiEEbT_>
  400858:	88 45 ff             	mov    %al,-0x1(%rbp)
  40085b:	0f b6 45 ff          	movzbl -0x1(%rbp),%eax
  40085f:	89 c6                	mov    %eax,%esi
  400861:	bf 80 10 60 00       	mov    $0x601080,%edi
  ...

with constexpr this is main assembly - note, no callq
0000000000400846 <main>:
  ...
  40084e:	c6 45 ff 01          	movb   $0x1,-0x1(%rbp)
  400852:	be 01 00 00 00       	mov    $0x1,%esi
  400857:	bf 80 10 60 00       	mov    $0x601080,%edi
  ...


 */
int 
main() {

  using namespace boost::date_time2;
  using std::cout;
  using std::endl;
  
  //constexpr bool b = is_leap_year(1404);
  // bool b = is_leap_year(1404);
  // cout << b << endl;
  // constexpr int i = month_from_year_and_day(2014, 1);
  // cout << i << endl;
  constexpr year_month_day ymd(2015, 5, 10);

  test_const_expr();

  return 0;
}
