#include "date/tz.h"
#include <chrono>
#include <cstdio>
#include <iostream>
using namespace std::chrono_literals;
using namespace std::chrono;
using namespace date;
using dh = std::chrono::duration<double, std::ratio<86400>>;

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

int main() {
  printf("UTC -> MJD\n");
  utc_time<dh> ut(utc_clock::now().time_since_epoch());
  printf("%lf\n", UTC2MJD(ut));
  printf("MJD -> UTC\n");
  std::cout << MJD2UTC(UTC2MJD(ut)) << std::endl;

  return 0;
}
