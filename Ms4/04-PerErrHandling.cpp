// Final Project Milestone 4
// Non-Periashable Tester program 4
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
    << "Name:" << endl << name << endl;
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
  cout << "--Perishable Error Handling test:" << endl;
  cout << "Each test must display the error message related to the test." << endl << endl;
  cout << "----Price validation test:" << endl;
  piv("abc", "abc", "abc");
  cin >> pr;
  if (cin.fail()){
    cin.clear();
    cin.ignore(2000, '\n');
    cout << "Error: " << pr << endl;
  }
  else{
    ok = false;
    cout << "Price validation failed" << endl;
  }
  _pause();
  if (ok){
    cout << "----Taxed validation test:" << endl;
    piv("abc", "abc", "10", "abc");
    cin >> pr;
    if (cin.fail()){
      cin.clear();
      cin.ignore(2000, '\n');
      cout << "Error: " << pr << endl;
    }
    else{
      ok = false;
      cout << "Taxed validaton failed" << endl;
    }
  }
  _pause();
  if (ok){
    cout << "----Quantity validation test:" << endl;
    piv("abc", "abc", "10", "y", "abc");
    cin >> pr;
    if (cin.fail()){
      cin.clear();
      cin.ignore(2000, '\n');
      cout << "Error: " << pr << endl;
    }
    else{
      ok = false;
      cout << "Quantity validaton failed" << endl;
    }
  }
  cout << "----------------------------------------------" << endl;
  if (ok){
    cout << "If proper error messages were displayed, error handling tests passed!"<<endl <<"Now run 02-NPDisplayTest.cpp." << endl;
  }
  else{
    cout << "Did not pass all the tests, please fix the problems and try again." << endl;
  }
  return 0;
}