#include "date/tz.h"
#include <chrono>
#include <cstdio>
#include <iostream>
using namespace date;
using namespace std::chrono;
constexpr auto jdiff()
{
   return sys_days{jan/1/1970} - (sys_days{nov/24/-4713} + 12h);
}
utc_time<std::chrono::seconds> MJD2UTC(double MJD)
{
  using dh = std::chrono::duration<double, std::ratio<84600>>;
  utc_time<seconds> no_leap{round<seconds>(dh{ MJD + 2400000.5 - dh{jdiff()}.count()})};
  auto ut_lp = get_leap_second_info(no_leap);
  return utc_time<seconds>{round<seconds>(dh{  dh{ut_lp.elapsed}.count() + MJD + 2400000.5 - dh{jdiff()}.count()})};
}

int main(){
  //set utc_time 
  utc_time<seconds> utc_s{ round<seconds>(utc_clock::now().time_since_epoch()) };
  std::cout << "UTC - > SEC" << std::endl;
  std::cout << utc_s.time_since_epoch().count() <<"s"<< std::endl;
  std::cout << "MJD - > SEC" << std::endl;
  utc_s = MJD2UTC(10000.0);
  std::cout << utc_s.time_since_epoch().count() <<"s"<< std::endl;
  
  return 0;
}
