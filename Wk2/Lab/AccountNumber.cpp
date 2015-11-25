// OOP244 Workshop 2: Compound types and privacy
// File	???????
// Version 1.0
// Date	???????????
// Author	?????????
// Description
// ?????????????????????
//
//
// Revision History
///////////////////////////////////////////////////////////
// Name			Date		Reason
// 
///////////////////////////////////////////////////////////
#include <iostream>
#include <cstring>
using namespace std;
#include "AccountNumber.h"

namespace sict
{
    void AccountNumber::displayName() const
    {
        cout << "Name: " << _name;
    }
    
    void AccountNumber::displayNumber() const
    {
        cout << "Account number: " << _bankCode << "-" << _branchCode << "-" << _accountNumber;
    }
    
    void AccountNumber::setName(const char name[])
    {
        strcpy(_name,name);
    }
    
    void AccountNumber::setAccountNumber(int bankCode, int branchCode, int accountNumber)
    {
        if((bankCode >= MIN_BANKCODE && bankCode <= MAX_BANKCODE) &&
            (branchCode >= MIN_BRANCHCODE && branchCode <= MAX_BRANCHCODE) &&
            (accountNumber >= MIN_ACCNO && accountNumber <= MAX_ACCNO))
        {
            _bankCode = bankCode;
            _branchCode = branchCode;
            _accountNumber = accountNumber;
            _validAccNumber = true;
        }
        else
        {
            _validAccNumber = false;
        }
    }
    
    bool AccountNumber::isValid() const
    {
        return _validAccNumber;
    }
    
    void AccountNumber::display() const
    {
        if(_validAccNumber)
        {
            cout << "Name: " << _name << ", Account number: " << _bankCode << "-" << _branchCode << "-" << _accountNumber << endl;
        }
        else
        {
            cout << _name << " does not have a valid account number." << endl;
        }
    }
    
    void AccountNumber::display(bool op1) const
    {
        if(op1 == false)
        {
            displayNumber();
            cout << endl;
        }
    }
    
    void AccountNumber::display(bool op1, bool op2) const
    {
        if(op1 == true && op2 == false)
        {
            displayName();
            cout << endl;
        }
    }
}









