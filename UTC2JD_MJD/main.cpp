#include "date/tz.h"
#include <chrono>
#include <cstdio>
#include <iostream>

constexpr auto jdiff()
{
  
   using namespace date;
   using namespace std::chrono_literals;
   return sys_days{jan/1/1970} - (sys_days{nov/24/-4713} + 12h);
}

template<typename Duration>
double UTC2MJD(date::utc_time<Duration>& ut)
{
  using dh = std::chrono::duration<double, std::ratio<84600>>;
  using namespace std::chrono;
  using namespace date;
  utc_time<seconds> ut_now{round<seconds>(utc_clock::now().time_since_epoch())};
  auto ut_lp = get_leap_second_info(ut);
  return dh{ut.time_since_epoch()}.count() + dh{jdiff()}.count() - dh{ut_lp.elapsed}.count() - 2400000.5;
}


date::utc_time<std::chrono::seconds> MJD2UTC(double MJD)
{
  using dh = std::chrono::duration<double, std::ratio<84600>>;
  using namespace std::chrono;
  using namespace date;
  utc_time<seconds> no_leap{round<seconds>(dh{ MJD + 2400000.5 - dh{jdiff()}.count()})};
  auto ut_lp = get_leap_second_info(no_leap);
  return utc_time<seconds>{round<seconds>(dh{  dh{ut_lp.elapsed}.count() + MJD + 2400000.5 - dh{jdiff()}.count()})};
}

int main(){
  using namespace date;
  using namespace std::chrono;
  printf("UTC -> MJD\n");
  using dh = std::chrono::duration<double, std::ratio<84600>>;
  utc_time<dh> ut(utc_clock::now().time_since_epoch());
  printf("%lf\n", UTC2MJD(ut) );
  printf("MJD -> UTC\n");
  std::cout << MJD2UTC(UTC2MJD(ut)) << std::endl;
  
  return 0;
}
