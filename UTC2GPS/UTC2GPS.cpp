#include "date/tz.h"
#include <cstdint>
#include <iostream>
#include <string>
using namespace date;
using namespace std::chrono;

#define REGISTE_TIME_SYS(class_name) class class_name{	\
public: \
 static std::string name; \
 typedef class_name##_##clock clock;		  \
 typedef class_name##_##time<milliseconds> time; \
};						 \
std::string class_name::name = #class_name;

//using dms = duration<double, std::milli>;
//void GPS2UTC(){
//   gps_time<microseconds> gt{round<microseconds>(dms{gps_clock::now().time_since_epoch()})};
//   auto utc = clock_cast<utc_clock>(gt);
//   std::cout << gt << std::endl;
//   std::cout << utc <<std::endl;
//}
//
//void UTC2GPS(){
//  utc_time<milliseconds> ut{round<milliseconds>(dms{utc_clock::now().time_since_epoch()})};
//  auto gps = clock_cast<gps_clock>(ut);
//  std::cout << ut << "UTC" << std::endl;
//  std::cout << gps << "GPS" << std::endl;
//
//}

template<typename T1, typename T2>
void Convert(){
  using dms = duration<double, std::milli>;
  typename T1::time t1{round<milliseconds>(dms{T1::clock::now().time_since_epoch()})};
  auto t2 = clock_cast<typename T2::clock>(t1);
  std::cout << t1 << T1::name << std::endl;
  std::cout << t2 << T2::name << std::endl;
};
REGISTE_TIME_SYS(utc)
REGISTE_TIME_SYS(gps)


int main()
{
  
   Convert<gps, utc>();
   Convert<utc, gps>();
  //GPS2UTC();
  //UTC2GPS();
  return 0;
}
