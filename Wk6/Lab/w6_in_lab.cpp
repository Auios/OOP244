// OOP244 Workshop 6: operators 
// File: w6_in_lab.cpp
// Version: 1.0
// Date: 2015/11/03
// Author: Fardad Soleimanloo
// Description:
// This file tests in-lab section of your workshop
/////////////////////////////////////////////

#include <iostream>
#include "Account.h"
using namespace sict;
using namespace std;

int main(){
  Account A;
  Account B("Saving", 10000.99);
  Account C("Checking", 100.99);
  double value = 0;
  cout << A << endl << B << endl << C << endl << "--------" << endl;
  A = B + C;
  A = "Joint";
  cout << A << endl << B << endl << C << endl << "--------" << endl;
  A = B += C;
  cout << A << endl << B << endl << C << endl << "--------" << endl;
  value += A;
  value += B;
  value += C;
  cout << "Total balance: " << value << endl;
  return 0;
}