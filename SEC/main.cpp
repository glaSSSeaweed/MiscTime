#include "date/tz.h"
#include <chrono>
#include <cstdio>
#include <iostream>
using namespace date;
using namespace std::chrono;
using dh = std::chrono::duration<double, std::ratio<84600>>;

constexpr auto jdiff() {
  return duration_cast<dh>(sys_days{jan / 1 / 1970} -
                           (sys_days{nov / 24 / -4713} + 12h));
}
template <typename Duration> double UTC2MJD(date::utc_time<Duration> &ut) {
  return duration_cast<dh>(ut.time_since_epoch()).count() + jdiff().count() -
         duration_cast<dh>(get_leap_second_info(ut).elapsed).count() -
         2400000.5;
}

date::utc_time<seconds> MJD2UTC(double MJD) {
  seconds utcWithoutLeap =
      duration_cast<seconds>(dh(MJD) + dh(2400000.5) - jdiff());
  utc_time<seconds> no_leap{utcWithoutLeap};
  return utc_time<seconds>{
      duration_cast<seconds>(dh{get_leap_second_info(no_leap).elapsed}) +
      utcWithoutLeap};
}
int main(){
  //set utc_time 
  utc_time<seconds> utc_s{ duration_cast<seconds>(utc_clock::now().time_since_epoch()) };
  std::cout << "UTC - > SEC" << std::endl;
  std::cout << utc_s.time_since_epoch().count() <<"s"<< std::endl;
  std::cout << "MJD - > SEC" << std::endl;
  utc_s = MJD2UTC(10000.0);
  std::cout << utc_s.time_since_epoch().count() <<"s"<< std::endl;
 
  return 0;
}
