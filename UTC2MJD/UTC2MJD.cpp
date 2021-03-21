#include<iostream>
#include "UTC.h"

int main(){
  UTC utc;
  std::cout << "UTC" << std::endl;
  std::cout << utc;
  std::cout << "UTC -> JD" << std::endl;
  std::cout << utc.utc2jd()<<std::endl;
  std::cout << "UTC -> MJD" << std::endl;
  std::cout <<  utc.utc2mjd()<<std::endl;
  std::cout << "MJD -> UTC" << std::endl;
  utc = UTC::mjd2utc(utc.utc2mjd());
  std::cout << utc;
  return 0;
}
