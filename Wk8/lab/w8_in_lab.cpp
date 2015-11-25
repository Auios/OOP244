// OOP244 Workshop 8: Derived Classes
// File	w8_in_lab.cpp
// Version 1.0
// Date	2015/11/18
// Author	Franz Newland, Eden Burton, Fardad soleimanloo
// Description
// This file demonstrates the client module of w8 
/////////////////////////////////////////////////////

#include <iostream>
#include "Hero.h"
using namespace sict;
using namespace std;
int main(){
  Hero m("Mom", 20);
  Hero d("Dad", 10);
  cout << m << endl << d << endl;
  m += 70;
  d += 20;
  cout << m << endl << d << endl;
  cout << "Comparing Mom and Dad: " << endl;
  GameCharacter* gcp = (m < d) ? &d : &m;
  cout << *gcp << " is stronger!" << endl;
  d -= 25; 
  m -= 200; 
  cout << m << endl << d << endl;
  cout << "Comparing Mom and Dad: " << endl;
  gcp = (m > d) ? &m : &d;
  cout << *gcp << " is stronger!" << endl;
  return 0;
}
