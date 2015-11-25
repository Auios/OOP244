// Final Project Milestone 2
// Submission Tester program
// File ms2.cpp
// Version 1.0
// Date 2015/07/28
// Author       Fardad Soleimanloo
// 
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// Fardad             2015/04/01           Preliminary release
/////////////////////////////////////////////////////////////////
#include <iostream>
#include "TestFile.h"
using namespace std;
using namespace sict;
int main(){  
  fstream file("ms2.txt", ios::out);
  file << "one" << endl << "two" << endl;
  file.close();
  TestFile F("ms2.txt");
  F.load(file);
  cout << "Linear: " << F << endl;
  cout << "As is: " << endl;
  F.print();
  cout << "Enter the folowing: " << endl << "three<ENTER>" << endl << "four<ENTER>" << endl << "<Ctrl-D>" << endl << endl;
  cin >> F;
  F.save(file);
  F.load(file);
  cout << F << endl;
  F.print();
  return 0;
}
