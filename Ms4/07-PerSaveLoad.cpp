// Final Project Milestone 4
// Non-Periashable Tester program 7
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
  fstream prfile(FileName, ios::out);
  Perishable pr;
  cout << "----Storage and loading test, the output of the Program and yours must match:" << endl;
  piv("1234", "Box", "123.45", "y", "2", "2015/11/25");
  cin >> pr;
  cin.ignore(1000, '\n');
  Perishable tpr;
  pr.taxed(false);
  pr.save(prfile);
  pr.save(prfile);
  prfile.close();
  cout << "--Save NonPerishable, program: " << endl
    << "P,1234,Box,123.45,0,2,2015/11/25" << endl
    << "P,1234,Box,123.45,0,2,2015/11/25" << endl;
  cout << "--Save Perishable, yours: " << endl;
  dumpFile(FileName);
  cout << "--Load Perishable: " << endl;
  prfile.open(FileName, ios::in);
  prfile.ignore(2);
  tpr.load(prfile);
  cout << "Program: 1234   |Box                 | 123.45|  p|   2|   246.90|" << endl;
  cout << "  Yours: " << tpr << endl;
  prfile.clear();
  prfile.close();
  return 0;
}