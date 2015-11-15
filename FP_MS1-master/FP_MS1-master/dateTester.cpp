// Final Project Milestone 1
// Date Tester program
// File	dateTester.cpp
// Version 1.0
// Date	2015/10/11
// Author	Fardad Soleimanloo
// Description
// This program is for students to test their implementation 
// of the Date class
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////

#include "Date.h"
#include "POS.h"
#include <iostream>
using namespace sict;
using namespace std;

// A fool proof Date entry from console
Date getDate(bool dateOnly);

int main(){
  Date
    D1,   // value to be recieved from console
    D2(2017,10, 20, 13, 52);
  cout << "Current Date-time: " << endl << D1 << endl;
  cout << "Please enter 2014/9/30: ";
  D1 = getDate(true);
  cout << "Youe entered: " << D1 << endl;
  cout << "Please enter a date to be compared to 2017/10/20, 13:52." << endl <<
    "YYYY/MM/DD, hh:mm > ";
  D1 = getDate(false);
  cout << "Your Entry: " << D1 << endl;
  cout << "Set by program to 2017/10/20, 13:52: " << D2 << endl;
  cout << "All the following statements must be correct: " << endl;
  if (D1 > D2){
    cout << D1 << " > " << D2 << endl;
  }
  else{
    cout << D1 << " <= " << D2 << endl;
  }
  if (D1 < D2){
    cout << D1 << " < " << D2 << endl;
  }
  else{
    cout << D1 << " >= " << D2 << endl;
  }
  if (D1 <= D2){
    cout << D1 << " <= " << D2 << endl;
  }
  else{
    cout << D1 << " > " << D2 << endl;
  }
  if (D1 >= D2){
    cout << D1 << " >= " << D2 << endl;
  }
  else{
    cout << D1 << " < " << D2 << endl;
  }
  if (D1 == D2){
    cout << D1 << " == " << D2 << endl;
  }
  else{
    cout << D1 << " != " << D2 << endl;
  }
  if (D1 != D2){
    cout << D1 << " != " << D2 << endl;
  }
  else{
    cout << D1 << " == " << D2 << endl;
  }
  cout << "Please enter a date to be compared to 2017/10/20" << endl <<
    "YYYY/MM/DD > ";
  D1 = getDate(true);
  D2.dateOnly(true);
  cout << "Your Entry: " << D1 << endl;
  cout << "Set by program to 2017/10/20: " << D2 << endl;
  cout << "All the following statements must be correct: " << endl;
  if (D1 > D2){
    cout << D1 << " > " << D2 << endl;
  }
  else{
    cout << D1 << " <= " << D2 << endl;
  }
  if (D1 < D2){
    cout << D1 << " < " << D2 << endl;
  }
  else{
    cout << D1 << " >= " << D2 << endl;
  }
  if (D1 <= D2){
    cout << D1 << " <= " << D2 << endl;
  }
  else{
    cout << D1 << " > " << D2 << endl;
  }
  if (D1 >= D2){
    cout << D1 << " >= " << D2 << endl;
  }
  else{
    cout << D1 << " < " << D2 << endl;
  }
  if (D1 == D2){
    cout << D1 << " == " << D2 << endl;
  }
  else{
    cout << D1 << " != " << D2 << endl;
  }
  if (D1 != D2){
    cout << D1 << " != " << D2 << endl;
  }
  else{
    cout << D1 << " == " << D2 << endl;
  }
  return 0;
}

Date getDate(bool dateOnly){
  Date D;
  D.dateOnly(dateOnly);
  do{
    cin >> D;      // get D from console
    switch (D.errCode())    {
    case CIN_FAILED:
      cin.clear();
      cout << "Invlid date Entry";
      break;
    case YEAR_ERROR:
      cout << "Invlid year; " << MIN_YEAR << "<= year <= " << MAX_YEAR;
      break;
    case MON_ERROR:
      cout << "Invlid month, 1<=Mon<=12";
      break;
    case DAY_ERROR:
      cout << "Invlid Day, 1<=Day<=" << D.mdays();
      break;
    case HOUR_ERROR:
      cout << "Invalid Hour, 0<=Hour<=23";
      break;
    case MIN_ERROR:
      cout << "Invalid Minute, 0<=Min<=59";
      break;
    }
    cin.ignore(2000, '\n');
  } while (D.bad() && cout << ", Please try again > ");  // if D is invalid, print ", Please try again > " and loop
  return D;
}
