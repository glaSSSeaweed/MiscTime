#pragma once
#include <iostream>
#include <ctime>
class UTC{
 private:
  struct __S_UTC{
  explicit __S_UTC(
	       unsigned int year =0,
	       unsigned int mon =0,
	       unsigned int day =0,
	       unsigned int hor =0,
	       unsigned int min =0,
	       unsigned int sec =0) :
    m_year(year),m_mon(mon),m_day(day),
    m_hour(hor),m_min(min),m_sec(sec)  
    {};
  unsigned int m_year;
  unsigned int m_mon;
  unsigned int m_day;
  unsigned int m_hour;
  unsigned int m_min;
  unsigned int m_sec;
};
 public:
  friend std::ostream& operator << (std::ostream& os, UTC& utc);
  explicit UTC() : u(new __S_UTC){  };
  explicit UTC(unsigned int year,
	       unsigned int mon,
	       unsigned int day,
	       unsigned int hour=0,
	       unsigned int min =0,
	       unsigned int sec =0) : u(new __S_UTC{year,mon,day,hour,min,sec}){  };
  UTC(const UTC& other){
    initialize(other);
  }
  UTC(UTC&& other){
    u = other.u;
    other.u = nullptr;
  
  }
  UTC& operator=(const UTC& other){
    initialize(other);
    return *this;
  };
  UTC& operator=(UTC&& other){
    u = other.u;
    other.u = nullptr;
    return *this;
  };
  void initialize(const UTC& other){
    if(&other == this)
      return ;
    delete u;
    u = new __S_UTC(other.u->m_year,other.u->m_mon,other.u->m_day,other.u->m_hour,other.u->m_min,other.u->m_sec);
  }
  void AutoSetUTC(){
    time_t now =time(0);
    char* data = ctime(&now);
    tm* gm =gmtime(&now);
    setUTC(gm->tm_year+1900,gm->tm_mon+1,gm->tm_mday,gm->tm_hour,gm->tm_min,gm->tm_sec);
  };
  void setUTC( unsigned int year,
	       unsigned int mon,
	       unsigned int day,
	       unsigned int hor =0,
	       unsigned int min =0,
	       unsigned int sec =0){
    u->m_year = year;
    u->m_mon =mon;
    u->m_day =day;
  };
  float utc2jd();
  float utc2mjd();
  static UTC  mjd2utc(float mjd);
  

  
  virtual ~UTC(){
    delete u;
  };
 private:
  __S_UTC* u;
};
float UTC::utc2jd(){
  return 367*(u->m_year) - 7.0*(u->m_year+(u->m_mon+9.0)/12)/4+275*u->m_mon/9.0+u->m_day+1721014;
}
float UTC::utc2mjd(){
  return utc2jd() - 2400000.5;
}

std::ostream& operator << (std::ostream& os, UTC& utc){
  std::cout <<(utc.u)->m_year<<" "
     <<utc.u->m_mon<<" "
     <<utc.u->m_day<<" "
      <<utc.u->m_hour<<" "
     <<utc.u->m_min<<" "
     <<utc.u->m_sec<<std::endl;
  return os;
}

UTC UTC::mjd2utc(float mjd)
{
  int y1,m1,k;
  y1=(int)( (mjd-15078.2)/365.25 );
  m1=(int)((mjd-14956.1-(int)(y1*365.25))/30.6001); 
  int day =(mjd-14956-(int)(y1*365.25)-(int)(m1*30.6001)); 
  k=0;
  if(y1==14 || y1==15) k=1;
  int mon = (int)(m1-1-k*12);
  k=0;
  if(y1==14 || y1==15) k=1;
  int year = (int)(y1+k);
  //std::cout << year<<" "<<mon<<" "<<day<<std::endl;
  return UTC(year,mon,day);
  
}
