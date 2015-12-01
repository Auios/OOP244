// Final Project Milestone 3 
// Item Tester program
// File	ItemTester.cpp
// Version 1.0
// Date	2015/11/19
// Author	Fardad Soleimanloo
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// Fardad             2015/11/19		       Preliminary release
/////////////////////////////////////////////////////////////////


#define TAB '\t'
#include <iostream>
#include <iomanip>
using namespace std;
#include "Item.h"
namespace sict{
  class SItem :public Item{
  public:
    SItem(){};
    SItem(const char* thesku, const char * theName,
      double thePrice) :Item(thesku, theName, thePrice){}
    SItem(const char* thesku, const char * theName,
      double thePrice, bool taxed) :Item(thesku, theName, thePrice, taxed){}
    SItem(const SItem& SG) :Item(SG){};
    virtual std::fstream& save(std::fstream& file)const{
      file.open("ms3.txt", ios::out);
      file << sku() << TAB << name() << TAB << quantity() << TAB
        << int(taxed()) << TAB << price() << endl;
      file.close();
      return file;
    }
    virtual std::fstream& load(std::fstream& file){
      file.open("ms3.txt", ios::in);
      char buf[2000];
      double dbuf;
      int ibuf;
      file >> buf;
      sku(buf);
      file >> buf;
      name(buf);
      file >> ibuf;
      quantity(ibuf);
      file >> ibuf;
      taxed(bool(ibuf));
      file >> dbuf;
      price(dbuf);
      file.close();
      return file;
    }
    virtual std::ostream& write(std::ostream& os, bool linear)const{
      return os << sku() << ": " << name() << endl
        << "Qty: " << quantity() << endl
        << "Cost (price * tax): " << fixed << setprecision(2) << cost();
    }
    virtual std::istream& read(std::istream& is){
      char buf[2000];
      double dbuf;
      int ibuf;
      cout << "sku: ";
      is >> buf;
      sku(buf);
      cout << "name (no spaces): ";
      is >> buf;
      name(buf);
      cout << "qty: ";
      is >> ibuf;
      quantity(ibuf);
      cout << "is taxed? (1/0): ";
      is >> ibuf;
      taxed(bool(ibuf));
      cout << "price: ";
      is >> dbuf;
      price(dbuf);
      return is;
    }
  };
}

using namespace sict;
int main(){
  double res, val = 0.0;
  fstream F;
  SItem Empty;
  SItem A("456", "AItem", 200);
  SItem B("567", "BItem", 300, false);
  B.quantity(50);
  cout << Empty << endl;
  cout << A << endl << B << endl << endl;
  cout << "Enter Item info for A: (Enter 123 for sku)" << endl;
  cin >> A;
  cout << "Copying A in C ----" << endl;
  SItem C = A;
  cout << C << endl << endl;
  cout << "Saving A---------" << endl;
  A.save(F);
  cout << "Loading B----------" << endl;
  B.load(F);
  cout << "A: ----------" << endl;
  cout << A << endl << endl;
  cout << "B: ----------" << endl;
  cout << B << endl << endl;
  cout << "C=B; op=----------" << endl;
  C = B;
  cout << C << endl << endl;;
  cout << "Operator ==----------" << endl;
  cout << "op== is " << ((A == "123") && !(A == "234") ? "OK" : "NOT OK") << endl << endl;
  cout << "op+=: A += 20----------" << endl;
  A += 20;
  cout << A << endl << endl;
  cout << "op-=: A -= 10----------" << endl;
  A -= 10;
  cout << A << endl << endl;
  cout << "op+=double: ----------" << endl;
  res = val += A;
  cout << res << "=" << val << endl << endl;
  return 0;
}