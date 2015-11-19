// Final Project Milestone 2
// Development Tester program
// File	PosIOTester.cpp
// Version 1.0
// Date	2015/11/16
// Author	Fardad Soleimanloo
//
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// Fardad             2015/11/16          Preliminary release
/////////////////////////////////////////////////////////////////
#include <iostream>
#include "TestFile.h"
using namespace std;
using namespace sict;
int main(){  
  fstream file;
  TestFile F("posfile.txt");
  cout << "Run this program few times and keep adding to" <<endl<<"the content of the file created." << endl;
  F.load(file);
  cout << "Linear content of file readwrite.txt: " << endl << endl << F << endl << "---------------------" << endl;
  cout << "Press <ENTER> to continue...";
  cin.ignore();
  cout << endl << "readwrite.txt as is: " << endl;
  F.print();
  cout << " ---------------- " << endl << "Enter few lines of text and then"
        <<endl<<"On windows end it by pressing <Ctrl-Z> and <ENTER> in a new line"
        <<endl<<"On Linux or mac end it with a new line with <Ctrl-D>" 
        <<endl<< "to append to the end of readwrite.txt:" << endl;
  cin >> F;
  F.save(file);
  cout << "Re-run the program to see the appended lines." << endl;
  return 0;
}