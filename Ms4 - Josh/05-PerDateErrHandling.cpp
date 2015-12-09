// Final Project Milestone 4
// Non-Periashable Tester program 5
// Version 1.0
// Date 2015/11/24
// Author Fardad Soleimanloo
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// Fardad             2015/08/07           Preliminary release    
/////////////////////////////////////////////////////////////////
#include "Perishable.h"
using namespace sict;
using namespace std;
#define FileName "perish.txt"
void piv(const char* upc, const char* name, const char* price = "", 
  const char* taxed = "", const char* qty = "", const char* date = ""){
  cout
    << "Enter the following: " << endl
    << "Sku: " << upc << endl
    << "Name:" <<endl << name << endl;
  if (price[0]) cout << "Price: " << price << endl;
  if (taxed[0]) cout << "Taxed: " << taxed << endl;
  if (qty[0]) cout << "Quantity: " << qty << endl;
  if (date[0]) cout << "Expiry date: " << date << endl;
  cout << endl;
}
void dumpFile(const char* fname){
  ifstream f(fname);
  char ch;
  while (!f.get(ch).fail()){
    cout.put(ch);
  }
  f.clear();
  f.close();
}
void _pause(){
  cout << "****press enter to continue...";
  cin.ignore(1000, '\n');
}

int main(){
  Perishable pr;
  bool ok = true;
  int i;
  cout << "--Perishable Expiry Date Error Handling test:" << endl;
  cout << "Each test must display the error message related to the test." << endl << endl;
  if (ok){
    cout << "----Invalid Date Entry validation test:" << endl;
    piv("a", "a", "1", "y", "1", "a");
    cin >> pr;
    if (cin.fail()){
      cin.clear();
      cin.ignore(2000, '\n');
      cout << "Error: " << pr << endl;
    }
    else{
      ok = false;
      cout << "Date validaton failed" << endl;
    }
  }
  _pause();
  if (ok){
    cout << "----Invalid Year Entry validation test:" << endl;
    piv("a", "a", "1", "y", "1", "10/10/10");
    cin >> pr;
    if (cin.fail()){
      cin.clear();
      cin.ignore(2000, '\n');
      cout << "Error: " << pr << endl;
    }
    else{
      ok = false;
      cout << "Year validaton failed" << endl;
    }
  }
  _pause();
  if (ok){
    cout << "----Invalid Month Entry validation test:" << endl;
    piv("a", "a", "1", "y", "1", "2000/13/10");
    cin >> pr;
    if (cin.fail()){
      cin.clear();
      cin.ignore(2000, '\n');
      cout << "Error: " << pr << endl;
    }
    else{
      ok = false;
      cout << "Month validaton failed" << endl;
    }
  }
  _pause();
  if (ok){
    cout << "----Invalid Day Entry validation test:" << endl;
    piv("a", "a", "1", "y", "1", "2000/10/0");
    cin >> pr;
    if (cin.fail()){
      cin.clear();
      cin.ignore(2000, '\n');
      cout << "Error: " << pr << endl;
    }
    else{
      ok = false;
      cout << "Year validaton failed" << endl;
    }
  }
  cout << "----------------------------------------------" << endl;
  if (ok){
    cout << "If proper error messages were displayed, error handling tests passed!" << endl << "Now run 06-PerDisplayTest.cpp." << endl;
  }
  else{
    cout << "Did not pass all the tests, please fix the problems and try again." << endl;
  }
 
  return 0;
}