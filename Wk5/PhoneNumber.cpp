// OOP244 Workshop 5: Classes with resources 
// File: PhoneNumber.cpp
// Version: 1.0
// Date: 2015/10/13
// Author: Fardad Soleimanloo
/////////////////////////////////////////////

#include "PhoneNumber.h"
#include <cstring>
#include <iostream>     
#include <iomanip>
using namespace std;
namespace sict{
  void PhoneNumber::setEmpty(){
    _area = _number = 0;
    _type = (char*)0; // same as _type = nullptr, _type does not point to anything.
  }

  bool PhoneNumber::isValid(int area, int number, const char* type)const{
       // "_type && _type[0], same as: _type != nullptr && _type[0] != '\0', which means, 
       //      first if _type is not null and is pointing to something, 
       //      then if "something" is not an empty string and etc....
       // lazy evaluation
    return type && type[0] && area >= 111 && area <= 999 && number >= 1111111 && number <= 9999999;
  }

  bool PhoneNumber::allocateAndCopy(int area, int number, const char* type){
    bool valid = isValid(area, number, type);
    if (valid){
      _area = area;
      _number = number;
      // dynamic resource allocation: 
      delete[] _type; // if not null delete the target of _type for new allocation 
      _type = new char[strlen(type) + 1];
      strcpy(_type, type);
    }
    return valid;
  }


  PhoneNumber::PhoneNumber(){
    setEmpty();
  }
  /* no need for this
  PhoneNumber::PhoneNumber(int area, int number, const char* type){
    _type = (char*)0; // same as _type = nullptr, setting unused pointer to null so allocateAndCopy does not delete
    // some random pointed memory causing segmentation fault. 
    if (!allocateAndCopy(area, number, type)){ // reusing logic
      setEmpty();
    }
  }
  */

  PhoneNumber::PhoneNumber(const PhoneNumber& cp){
    _type = (char*)0; // same as _type = nullptr, setting unused pointer to null so allocateAndCopy does not delete
                     // some random pointed memory causing segmentation fault. 
    if (!allocateAndCopy(cp._area, cp._number, cp._type)){ // reusing logic
      setEmpty();
    }
  }
  PhoneNumber::~PhoneNumber(){
    delete[] _type;
  }
  PhoneNumber& PhoneNumber::operator=(const PhoneNumber& ro){
    if (!allocateAndCopy(ro._area, ro._number, ro._type)){// reusing logic
      setEmpty();
    }
    return *this;
  }


  // Performs a fool-proof entry of phone number form console in following format:
  // Type 999 9999999
  void PhoneNumber::read(){
    bool bad = true;
    char type[16];
    int area;
    int number;
    while (bad){
      cin.getline(type, 16, ',') >> area >> number;
      if (cin.fail()){
        cin.clear();
        cout << "Incorrect format, retry please (NumberType, 999 999999): ";
      }
      else if (!allocateAndCopy(area, number, type)){
        cout << "Invalid phone number!" << endl
          << "Use this format: type, AAA NNNNNNN" <<endl
          << "type: maximum 15 chars (Home, Mobile, etc)" <<endl
          << "AAA: 111<=AAA<=999" << endl 
          << "NNNNNNN: 1111111<=NNNNNNN<=9999999" << endl
          << "Retry: ";
      }
      else{
        bad = false;
      }
      cin.ignore(1000, '\n');
    }
  }


  void PhoneNumber::display(bool goToNewLine)const{
    if (!isEmpty()){
      cout <<setw(15)<<left<<setfill('.') << _type << ", " << _area << " " << _number / 10000 << "-" << setw(4) << setfill('0') << _number % 10000;
      if (goToNewLine) cout << endl;
    }
  }
  bool PhoneNumber::isEmpty()const{
    return _type == (char*)0;
  }
}