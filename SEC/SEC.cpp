#include "date/tz.h"
#include <iostream>
#include <string>
using namespace date;
using namespace std::chrono;


int main()
{
  utc_time<seconds> utc;
  auto sutc = duration<double>{utc_clock::now().time_since_epoch()};
  std::cout << "utc -> sec" << std::endl;
  std::cout << sutc << std::endl;
  return 0;
}
