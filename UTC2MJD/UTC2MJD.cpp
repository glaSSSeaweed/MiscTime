#include<iostream>
#include "UTC.h"

int main(){
  UTC utc;
  utc.AutoSetUTC();
  std::cout << utc;
  std::cout << utc.utc2jd()<<std::endl;
  std::cout <<  utc.utc2mjd()<<std::endl;
  std::cout <<"======"<<std::endl;
  utc = UTC::mjd2utc(utc.utc2mjd());
  std::cout << utc;
  return 0;
}
