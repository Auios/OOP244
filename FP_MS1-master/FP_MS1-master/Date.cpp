#include <iomanip>
#include <iostream>
#include <ctime>
using namespace std;
#include "Date.h"
#include "POS.h"
namespace sict{

  void Date::set(){
    time_t t = time(NULL);
    tm lt = *localtime(&t);
    _day = lt.tm_mday;
    _mon = lt.tm_mon + 1;
    _year = lt.tm_year + 1900;
    if (dateOnly()){
      _hour = _min = 0;
    }
    else{
      _hour = lt.tm_hour;
      _min = lt.tm_min;
    }
  }

  int Date::value()const{
    return _year * 535680 + _mon * 44640 + _day * 1440 + _hour * 60 + _min;
  }


  int Date::mdays()const{
    int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
    int mon = _mon >= 1 && _mon <= 12 ? _mon : 13;
    mon--;
    return days[mon] + int((mon == 1)*((_year % 4 == 0) && (_year % 100 != 0)) || (_year % 400 == 0));
  }


}
