//Mark.cpp
#include <cstring>
#include <iostream>
#include <iomanip>
#include "mark.h"
using namespace std;
namespace sict
{
    void Mark::allocate(int size)
    {
        deallocate();
        _name = new char[size];
    }
    
    void Mark::deallocate()
    {
        delete[] _name; //Delete memory
        _name = (char*)0; //Set pointer to null
    }
    
    void Mark::setOutOf(int outOf)
    {
        _outOf = outOf;
    }
    
    Mark::Mark()
    {
        _name = (char*)0;
        setValue(0);
        setOutof(0);
        cout << "Defaulting" << endl;
    }
    
    Mark::Mark(const Mark& CM)
    {
        _name = (char*)0;
        operator=(CM);
        //*this = CM;
        cout << "Copying " << CM._name << endl;
    
    Mark::Mark(const char* name, int value, int outOf)
    {
        _name = (char*)0;
        setName(name);
        setValue(value);
        setOutOf(outOf);
        cout << "Create" << _name << endl;
    }
    
    Mark::~Mark()
    {
        deallocate();
    }
    
    Mark& operator=(const Mark& RO)
    {
        if(this!=&RO)
        {
            deallocate();
            setname(RO._name);
            setValue(RO._value);
            setoutOf(RO._outof);
            cout << "Assigning to " << _name << endl;
        }
        return *this;
    }
    
    void Mark::setValue(int value)
    {
        _value = value;
    }
    
    void Mark::setName(const char* name)
    {
        allocate(strlen(name)+1);
        strcpy(_name,name);
    }
    void Mark::dspMark()const;
    {
        if(_outOf)
        {
            cout << "%" << setprecision(0) << double(_value) / double(_outOf) * 100;
        }
    }
    
    void Mark::dspName()const
    {
        if(_name)
        {
            cout << _name;
        }
        else
        {
            cout << "Unset Mark";
        }
    }
}
