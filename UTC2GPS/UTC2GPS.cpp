#include "date/tz.h"
#include <iostream>
#include <string>
using namespace date;
using namespace std::chrono;

namespace method {
namespace M01 {
#define REGISTE_TIME_SYS(class_name)                                           \
  class class_name {                                                           \
  public:                                                                      \
    static std::string name;                                                   \
    typedef class_name##_##clock clock;                                        \
    typedef class_name##_##time<milliseconds> time;                            \
  };                                                                           \
  std::string class_name::name = #class_name;

template <typename T1, typename T2> void Convert() {
  using dms = duration<double, std::milli>;
  typename T1::time t1{
      round<milliseconds>(dms{T1::clock::now().time_since_epoch()})};
  auto t2 = clock_cast<typename T2::clock>(t1);
  std::cout << t1 << T1::name << std::endl;
  std::cout << t2 << T2::name << std::endl;
};
REGISTE_TIME_SYS(utc)
REGISTE_TIME_SYS(gps)
}; // namespace M01
namespace M02 {
using dms = duration<double, std::milli>;
void GPS2UTC() {
  gps_time<milliseconds> gt{
      round<milliseconds>(dms{gps_clock::now().time_since_epoch()})};
  auto utc = clock_cast<utc_clock>(gt);
  std::cout << gt << std::endl;
  std::cout << utc << std::endl;
}
void UTC2GPS() {
  utc_time<milliseconds> ut{
      round<milliseconds>(dms{utc_clock::now().time_since_epoch()})};
  auto gps = clock_cast<gps_clock>(ut);
  std::cout << ut << "UTC" << std::endl;
  std::cout << gps << "GPS" << std::endl;
}

} // namespace M02

} // namespace method

// Convert T1 to T2 //clock
template <typename T1, typename T2> void Convert(typename T1::time_point &tp1) {
  // typename  T1::time_point tp1{T1::now().time_since_epoch()};
  auto tp2 = clock_cast<T2>(tp1);
  std::cout << tp1 << std::endl;
  std::cout << tp2 << std::endl;
}

int main() {
	// leap(utc) - leap(gsp) = 9s
  gps_clock::time_point gps(
      seconds{duration_cast<seconds>(gps_clock::now().time_since_epoch())});
  std::cout << "GPS -> UTC" << std::endl;
  Convert<gps_clock, utc_clock>(gps);

  utc_clock::time_point utc(
      seconds{duration_cast<seconds>(utc_clock::now().time_since_epoch())});
  std::cout << "UTC -> GPS" << std::endl;
  Convert<utc_clock, gps_clock>(utc);
  return 0;
}
