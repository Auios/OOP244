// Final Project Milestone 4
// Non-Periashable Tester program 1
// Version 1.1
// Date 2015/11/24
// Author Fardad Soleimanloo
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// Fardad             2015/11/24           Preliminary release    
// Fardad             2015/11/30           Capitalized labels
/////////////////////////////////////////////////////////////////
#include "NonPerishable.h"
#include "Perishable.h"
using namespace sict;
using namespace std;
const char nonPerFile[] = "nonper.txt";
const char PerFile[] = "per.txt";
void piv(const char* sku, const char* name, const char* price = "",
  const char* taxed = "", const char* qty = "", const char* date = ""){
  cout
    << "Enter the following: " << endl
    << "Sku: " << sku << endl
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
bool yes(){
  char ch;
  cin >> ch;
  cin.ignore(1000, '\n');
  return (ch == 'y' || ch == 'Y');
}
int main(){
  NonPerishable np;
  Perishable pr;
  bool ok = true;
  cout << "Tester 1 ---------------------------------------------------------------------" << endl
    << "--NonPerishable Error Handling test:" << endl;
  cout << "----Price validation test:" << endl;
  piv("abc", "abc", "abc");
  cin >> np;
  if (cin.fail()){
    cin.clear();
    cin.ignore(2000, '\n');
    cout << "Passed " << np << endl;
  }
  else{
    ok = false;
    cout << "Price validation failed" << endl;
    _pause();
  }
  if (ok){
    cout << "----Taxed validation test:" << endl;
    piv("abc", "abc", "10", "abc");
    cin >> np;
    if (cin.fail()){
      cin.clear();
      cin.ignore(2000, '\n');
      cout << "Passed " << np << endl;
    }
    else{
      ok = false;
      cout << "Taxed validaton failed" << endl;
      _pause();
    }
  }
  if (ok){
    cout << "----Quantity validation test:" << endl;
    piv("abc", "abc", "10", "y", "abc");
    cin >> np;
    if (cin.fail()){
      cin.clear();
      cin.ignore(2000, '\n');
      cout << "Passed " << np << endl;
    }
    else{
      ok = false;
      cout << "Quantity validaton failed" << endl;
      _pause();
    }
  }
  if (ok){
    cout << "Tester 2 ---------------------------------------------------------------------" << endl
      << "----Display test, the output of the Program and yours must match:" << endl;
    piv("1234", "Box", "123.45", "y", "2");
    cin >> np;
    cin.ignore(1000, '\n');
    cout << "--Linear------------" << endl;
    cout << "Program: 1234   |Box                 | 123.45| t |   2|   279.00|" << endl;
    cout << "  Yours: " << np << endl;
    cout << "--Form Display------" << endl;
    cout << "--Program: " << endl;
    cout << "Name:" << endl << "Box" << endl;
    cout << "Sku: 1234" << endl;
    cout << "Price: 123.45" << endl;
    cout << "Price after tax: 139.50" << endl;
    cout << "Quantity: 2" << endl;
    cout << "Total Cost: 279.00" << endl;
    cout << "--Yours: " << endl;
    np.write(cout, false);
    cout << endl << "Did the program and your outputs match? (y)es/(n)o: ";
    ok = yes();
  }
  if (ok){
    cout << "Tester 3 ---------------------------------------------------------------------" << endl;
    fstream npfile(nonPerFile, ios::out);
    cout << "----Storage and loading test, the output of the Program and yours must match:" << endl;
    NonPerishable tnp;
    np.taxed(false);
    np.save(npfile);
    np.save(npfile);
    npfile.close();
    cout << "--Save NonPerishable, program: " << endl
      << "N,1234,Box,123.45,0,2" << endl
      << "N,1234,Box,123.45,0,2" << endl;
    cout << "--Save NonPerishable, yours: " << endl;
    dumpFile(nonPerFile);
    cout << "--Load NonPerishable: " << endl;
    npfile.open(nonPerFile, ios::in);
    npfile.ignore(2);
    tnp.load(npfile);
    cout << "Program: 1234   |Box                 | 123.45|   |   2|   246.90|" << endl;
    cout << "  Yours: " << tnp << endl;
    npfile.clear();
    npfile.close();
    cout << endl << "Did the program and your outputs match? (y)es/(n)o: ";
    ok = yes();
  }
  if (ok){
    cout << "Tester 4 ---------------------------------------------------------------------" << endl;
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
      _pause();
    }
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
        _pause();
      }
    }
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
        _pause();
      }
    }
  }
  if (ok){
    cout << "Tester 5 ---------------------------------------------------------------------" << endl;
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
        _pause();
      }
    }
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
        _pause();
      }
    }
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
        _pause();
      }
    }
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
        _pause();
      }
    }
  }
  if (ok){
    cout << "Tester 6 ---------------------------------------------------------------------" << endl;
    cout << "----Display test, the output of the Program and yours must match:" << endl;
    piv("1234", "Box", "123.45", "y", "2", "2015/11/26");
    cin >> pr;
    cin.ignore(1000, '\n');
    cout << "--Linear------------" << endl;
    cout << "Program: 1234   |Box                 | 123.45| tp|   2|   279.00|" << endl;
    cout << "  Yours: " << pr << endl;
    cout << "--Form Display------" << endl;
    cout << "--Program: " << endl;
    cout << "Name:" << endl << "Box" << endl;
    cout << "Sku: 1234" << endl;
    cout << "Price: 123.45" << endl;
    cout << "Price after tax: 139.50" << endl;
    cout << "Quantity: 2" << endl;
    cout << "Total Cost: 279.00" << endl;
    cout << "Expiry date: 2015/11/26" << endl;
    cout << "--Yours: " << endl;
    pr.write(cout, false);
    cout << endl << "If the program outputs and your outputs match, the test is passed." << endl;
    cout << endl << "Did the program and your outputs match? (y)es/(n)o: ";
    ok = yes();
  }
  if (ok){
    cout << "Tester 7 ---------------------------------------------------------------------" << endl;
    fstream prfile(PerFile, ios::out);
    cout << "----Storage and loading test, the output of the Program and yours must match:" << endl;
    Perishable tpr;
    pr.taxed(false);
    pr.save(prfile);
    pr.save(prfile);
    prfile.close();
    cout << "--Save NonPerishable, program: " << endl
      << "P,1234,Box,123.45,0,2,2015/11/26" << endl
      << "P,1234,Box,123.45,0,2,2015/11/26" << endl;
    cout << "--Save Perishable, yours: " << endl;
    dumpFile(PerFile);
    cout << "--Load Perishable: " << endl;
    prfile.open(PerFile, ios::in);
    prfile.ignore(2);
    tpr.load(prfile);
    cout << "--Program: " << endl;
    cout << "Name:" << endl << "Box" << endl;
    cout << "Sku: 1234" << endl;
    cout << "Price: 123.45" << endl;
    cout << "Price after tax: N/A" << endl;
    cout << "Quantity: 2" << endl;
    cout << "Total Cost: 246.90" << endl;
    cout << "Expiry date: 2015/11/26" << endl;
    cout << "--Yours: " << endl;
    pr.write(cout, false);
    prfile.clear();
    prfile.close();
    cout << endl << "Did the program and your outputs match? (y)es/(n)o: ";
    ok = yes();
  }
  if (ok){
    cout << "It seems you passed all the tests" << endl << "If this program is running within the submission script, type exit to have the outputs tested." << endl;
  }
  else{
    cout << "Did not pass all the tests, please fix the problems and try again." << endl;
  }
}















