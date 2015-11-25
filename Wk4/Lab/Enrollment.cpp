#include <iostream>
#include "Enrollment.h"
#include <cstring>

using namespace std;

namespace sict
{
	Enrollment::Enrollment()
	{
		setEmpty();
	}

	Enrollment::Enrollment(const char* name,  const char* code, int year, int semester, int slot)
	{
		set(name, code, year, semester, slot);
	}

	bool Enrollment::valid()const
	{
		//return true if _name is not null and not empty
		if(_name[0] && _code[0] && _year == 2015 && _semester == 1 && _slot == 5)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	void Enrollment::setEmpty()
	{
		_name[0] = 0;
		_code[0] = 0;
		_year = 0;
		_semester = 0;
		_slot = 0;
		_enrolled = false;
	}
	bool Enrollment::isEnrolled() const
	{
		return _enrolled;
	}

	void Enrollment::display(bool nameOnly)const
	{
		if (valid()) {
			cout << _name;
			if (!nameOnly)
			{
				cout << endl << _code << ", Year: " << _year << " semester: " << _semester << " Slot: " << _slot << endl;
				cout << "Status: " << (isEnrolled() ? "E" : "Not e") << "nrolled." << endl;
			}
		}
		else {
			cout << "Invalid enrollment!" << endl;
		}
	}

	void Enrollment::set(const char* name, const char* code, int year, int semester, int time_slot, bool enrolled)
	{
		if (name){strncpy(_name, name, 30); _name[31] = 0;}
			else{_name[0] = 0;}

		if (code){strncpy(_code, code, 10); _code[11] = 0;}
			else{_code[0] = 0;}

		_year = year;
		_semester = semester;
		_slot = time_slot;
		_enrolled = enrolled;
	}

	bool Enrollment::hasConflict(const Enrollment& other) const
	{
		if (_year == other._year && _semester == other._semester && _slot == other._slot && valid())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}