// OOP244 Workshop 2: Compound types and privacy
// File w2_in_lab_prof.cpp
// Version 1.0
// Date 2015/09/21
// Author       Fardad Soleimanloo
// Description
// This file is used to submit student work for workshop2
//
// Revision History
///////////////////////////////////////////////////////////
// Name                 Date            Reason
// 
///////////////////////////////////////////////////////////

#include <iostream>
using namespace std;
#include "AccountNumber.h"
using namespace sict;
void profMessage();
int main(){
  AccountNumber myNumber;
  char name[41];
  int bankCode;
  int branchCode;
  int accNumber;
  profMessage();
  cout << "Bank account app" << endl <<
    "===================" << endl << endl;
  cout << "Please enter your name: ";
  cin >> name;
  cout << "please enter your bank account ,branch code" <<
    ", and account number as follows:" << endl << "999 999 99999: ";
  do{
    cin >> bankCode >> branchCode >> accNumber;
    myNumber.setName(name);
    myNumber.setAccountNumber(bankCode, branchCode, accNumber);
    myNumber.display();
  } while (!myNumber.isValid()
    && cout << "Invalid account number, (999 999 9999), try again: ");
  cout << "Thank you!" << endl;
  return 0;
}

void profMessage(){
  cout << endl <<"When program asks for your name enter \"John\" (note that J is capital)" << endl 
    << "Then enter the following sequence of numbers exactly as shown below." << endl
    << "If you make a mistake, press CTRL-C, exit and cancel the submission" << endl
    << "and start over." << endl
    << "DO NOT press BACKSPACE to correct the mistake, it will not work. " << endl
    << "Here are the numbers for testing the program: " << endl
    << "A: 1 123 12345" << endl
    << "B: 123 0 12345" << endl
    << "D: 123 1234 12345" << endl
    << "C: 123 123 123456" << endl
    << "E: 123 123 12345" << endl
    << "Press <ENTER> to start";
  cin.ignore(1000, '\n');
}
