#include "date/tz.h"
#include <cstdint>
#include <iostream>
using namespace date;
using namespace std::chrono;

void GPS2UTC(){
   using dms = duration<double, std::milli>;
   gps_time<microseconds> gt{round<microseconds>(dms{gps_clock::now().time_since_epoch()})};
   auto utc = clock_cast<utc_clock>(gt);
   auto tai = clock_cast<tai_clock>(gt);
   std::cout << gt << " GPS\n";
   std::cout << utc << " UTC\n";
   std::cout << tai << " TAI\n";
   


}


int main()
{
  GPS2UTC();
  return 0;
}
