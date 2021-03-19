#pragma once
#include<iostream>
#include<ctime>
using namespace std;
//static const char mon_name[][4] = {
//    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
//    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
//  };
struct UTC{
  explicit UTC(
	       unsigned int year,
	       unsigned int mon,
	       unsigned int day,
	       unsigned int hor =0,
	       unsigned int min =0,
	       unsigned int sec =0) :
    m_year(year),m_mon(mon),m_day(day),
    m_hour(hor),m_min(min),m_sec(sec)  
    {};
  friend ostream& operator << (ostream& os, UTC& u);  
  unsigned int m_year =0;
  unsigned int m_mon  =0;
  //  unsigned int m_week =0;
  unsigned int m_day  =0;
  unsigned int m_hour =0;
  unsigned int m_min  =0;
  unsigned int m_sec  =0;
};

ostream& operator << (ostream& os, UTC& u){
  cout <<u.m_year<<" "
       <<u.m_mon<<" "
       <<u.m_week<<" "
       <<u. m_day<<" "
       <<u.m_hour<<" "
       <<u.m_min<<" "
       <<u. m_sec<<endl;
  return os;
}
//utc->jd/mjd
float utc2jd(UTC& u){
  return 367*(u.m_year) - 7.0*(u.m_year+(u.m_mon+9.0)/12)/4+275*u.m_mon/9.0+u.m_day+1721014;
}
float utc2mjd(UTC& u){
  return utc2jd(u) - 2400000.5;
}

//mjd->utc
void mjd2utc(float mjd)
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
  cout << year<<" "<<mon<<" "<<day<<endl;
}

int main(){
	time_t now =time(0);
	char* data = ctime(&now);
	tm* gm =gmtime(&now);
	//UTC
	UTC utc(gm->tm_year+1900,
		gm->tm_mon+1,
		gm->tm_mday,
		gm->tm_hour,
		gm->tm_min,
		gm->tm_sec);
	cout << utc;
	//	cout <<utc2jd(utc)<<endl;
	cout <<utc2mjd(utc)<<endl;
	cout <<"======"<<endl;
	mjd2utc(utc2mjd(utc));
	return 0;
}
