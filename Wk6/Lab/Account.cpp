#include "cstring"
#include "iomanip"
#include "Account.h"
using namespace std;
namespace sict{
  Account::Account(){
    _name[0] = 0;
    _balance = 0;
  }
  Account::Account(double balance){
    _name[0] = 0;
    _balance = balance;
  }

  Account::Account(const char name[], double balance){
    strncpy(_name, name, 40);
    _name[40] = 0;
    _balance = balance;
  }
  ostream& Account::display(ostream& os)const{
    cout << _name << ": $" << setprecision(2) << fixed << _balance;
	return os;
  }

  double Account::getBal()const
  {
	  return _balance;
  }

  Account operator+(const Account A, const Account B)
  {
	  Account thisAccount(A.getBal() + B.getBal());
	  return thisAccount;
  }

  Account& Account::operator+=(const Account A)
  {
	  _balance += A.getBal();
	  return *this;
  }

  Account& Account::operator=(const char name[])
  {
	  strncpy(_name, name, 40);
	  _name[40] = 0;
	  return *this;

  }

  double operator+=(double& val, const Account& A)
  {
	  val += A.getBal();
	  return val;
  }
  std::ostream& operator<<(std::ostream& os, const Account A)
  {
	  return A.display(os);
  }
}