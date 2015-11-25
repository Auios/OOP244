#ifndef SICT_ACCOUNT_H__
#define SICT_ACCOUNT_H__
#include <iostream>
namespace sict{
  class Account{
    char _name[41];
    double _balance;
  public:
    Account();
    Account(const char name[], double balance = 0.0);
    Account(double balance);
    std::ostream& display(std::ostream& os)const;
	double getBal()const;
	Account& operator+=(const Account A);
	Account& operator=(const char name[]);
  };
  Account operator+(const Account A, const Account B);
  double operator+=(double& val, const Account& A);
  std::ostream& operator<<(std::ostream& os, const Account A);
}

#endif
