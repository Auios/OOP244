#include <cstring>
#include <iostream>
#include "Contact.h"
using namespace std;

namespace sict
{

	Contact::Contact()
	{
		_name[0] = 0;
		_noPN = 0;
		_pn = (PhoneNumber*)0;
	}

	Contact::Contact(const char* name, int phoneNumbers)
	{
		strncpy(_name, name, 40); //Getting errors. This was working nicely before... What changed?
		_pn = new PhoneNumber[phoneNumbers];
		_name[40] = '\0';
		_noPN = phoneNumbers;
	}

	Contact::~Contact()
	{
		delete[] _pn;
		_pn = (PhoneNumber*)0;
	}

	Contact::Contact(const Contact& src)
	{
		int i = 0;

		if (src.isEmpty)
		{
			setEmpty();
		}
		else
		{
			strncpy(_name, src._name, 40);
			_noPN = src._noPN;
			_pn = new PhoneNumber[src._noPN];

			for (i = 0; i < src._noPN; i++)
			{
				//Is this correct? I doubt it.
				//_pn[i] = src._pn[i];
			}
		}
	}

	Contact& Contact::operator=(const Contact& c)
	{
		int i = 0;
		if (this == &c) //If the address of 'this' and the address of the object being passed is the same then...
		{
			//They are the same object
			//Return 'this'?
			return *this;// this;
		}
		else
			//Not the same
			delete[] _pn;
			_pn = (PhoneNumber*)0;

			//Copy Constructor Code
			strncpy(_name, c._name, 40); //Getting errors. This was working nicely before... What changed?
			_noPN = c._noPN;
			_pn = new PhoneNumber[c._noPN];

			for (i = 0; i < c._noPN; i++)
			{
				//Is this correct? I doubt it.
				//_pn[i] = c._pn[i];
			}
			return *this;
			//End Copy Constructor Code
		}

	void Contact::display()const {
		int i = 0;
		//display the name and go to new line
		cout << _name << endl;
		// loop through elements of _pn up to _noPN and display them one by one
		for (i = 0; i < _noPN; i++)
		{
			_pn[i].display();
		}

		// draw a 40 char line using '-' and go to new line
		for (i = 0; i < 40; i++)
		{
			cout << "-";
		}
		cout << endl;
	}

	void Contact::read() {
		cout << "Contact Name: ";
		cin.getline(_name, 41, '\n');
		cout << "Please enter " << _noPN << " phone numbers: " << endl;
		for (int i = 0; i < _noPN; i++) {
			cout << i + 1 << ": ";
			_pn[i].read();
		}
	}

	bool Contact::isEmpty()const {
		return _pn == (PhoneNumber*)0;
	}
	void Contact::setEmpty() {
		_name[0] = 0;
		_noPN = 0;
		_pn = (PhoneNumber*)0;// same as _pn = nullptr;
	}
}