// Final Project Milestone 1
// Student constructor tester
// Version 1.1
// Date	2015/11/15
// Author	Fardad Soleimanloo
// Description
// This program test the student implementation of the Date class
// for submission.
//
// For you final test before submission:
//      DO NOT MODIFY THIS FILE IN ANY WAY
//
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// Fardad             2015/11/15           Preliminary release
// Fardad             2015/11/15           bug fix equalDates
//                                         on linux
/////////////////////////////////////////////////////////////////
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "Date.h"
#include "POS.h"
using namespace std;
using namespace sict;
ostream &operator<<(ostream& os, tm& lt);
bool equalDates(const char* A, const char* B);
bool yes();
int main(){
  int ret = 0;
  bool ok = true;
  if (ok){
    cout << "Testing Date() constructor and operator<< overload; " << endl;
    Date Current;
    time_t t = time(NULL);
    tm lt = *localtime(&t);

    cout << "Are these two the same date and time? (regardless of format)" << endl
      << "1- " << lt << endl
      << "2- " << Current << endl
      << "(y)es/(n)o: ";

    if (!yes()){
      cout << "Either the Date() constructor or operator<< is not implemented correctly." << endl;
      ok = false;
    }
    else{
      cout << "Passed!" << endl;
    }
  }
  if (ok){
    Date A(2018, 10, 18);
    Date B = A;
    cout << "Testing Date(int, int, int) constructor and operator>> overload; " << endl;
    cout << "enter the following date, 2018/10/18" << endl << ">";;
    cin >> B;

    if (!equalDates((const char*)&A, (const char*)&B)){
      cout << "Either the constructor or operator>> is not implemented correctly." << endl;
      ok = false;
    }
    else{
      cout << "Passed!" << endl;
    }
  }
  if (ok){
    Date A(2015, 9, 7, 14, 30);
    Date B = A;
    B.dateOnly(false);
    cout << "Testing Date(int, int, int,int,int) constructor and operator>> overload; " << endl;
    cout << "enter the following date, 2015/9/7, 14:30" << endl << ">";
    cin >> B;

    if (!equalDates((const char*)&A, (const char*)&B)){
      cout << "Either the constructor or operator>> is not implemented correctly." << endl;
      ok = false;
    }
    else{
      cout << "Passed!" << endl;
    }
  }
  if (ok){
    Date A(2015, 9, 7, 15);
    Date B = A;
    B.dateOnly(false);
    cout << "Testing Date(int, int, int,int,int=0) constructor and operator>> overload; " << endl;
    cout << "enter the following date, 2015/9/7, 15:0" << endl << ">";
    cin >> B;

    if (!equalDates((const char*)&A, (const char*)&B)){
      cout << "Either the constructor or operator>> is not implemented correctly." << endl;
      ok = false;
    }
    else{
      cout << "Passed!" << endl;
    }
  }
  if (ok){
    cout << "You passed all Constructor tests, run test no 3!" << endl;
  }
  else{
    cout << "You did not pass all the tests, keep working on your project!" << endl;
    ret = 1;
  }


  return ret;
}
bool equalDates(const char* A, const char* B){
  unsigned int i;
  for (i = 0; i < sizeof(Date); i++){
    if (A[i] != B[i]) i = sizeof(Date);
  }
  return sizeof(Date) == i;
}

ostream &operator<<(ostream& os, tm& lt){
  return os << (lt.tm_year + 1900) << "/" << (lt.tm_mon + 1) << "/"
    << (lt.tm_mday) << ", " << (lt.tm_hour) << ":" << lt.tm_min;
}

bool yes(){
  char ch;
  ch = cin.get();
  cin.ignore(1000, '\n');
  return ch == 'y' || ch == 'Y';
}
