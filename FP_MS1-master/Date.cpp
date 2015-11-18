#include <iomanip>
#include <iostream>
#include <ctime>
using namespace std;
#include "Date.h"
#include "POS.h"
namespace sict{

void Date::set()
{
	time_t t = time(NULL);
	tm lt = *localtime(&t);
	_day = lt.tm_mday;
	_month = lt.tm_mon + 1;
	_year = lt.tm_year + 1900;

	if (dateOnly())
	{
		_hour = _min = 0;
	}
	else
	{
		_hour = lt.tm_hour;
		_min = lt.tm_min;
	}
}

	int Date::value()const
	{
		return _year * 535680 + _month * 44640 + _day * 1440 + _hour * 60 + _min;
	}


	int Date::mdays()const
	{
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int mon = _month >= 1 && _month <= 12 ? _month : 13;
		mon--;
		return days[mon] + int((mon == 1)*((_year % 4 == 0) && (_year % 100 != 0)) || (_year % 400 == 0));
	}

	Date::Date()
	{
		_dateOnly = false;
		set();
	}

	Date::Date(int year, int month, int day)
	{
		_dateOnly = true;
		_year = year;
		_month = month;
		_day = day;
		_hour = 0;
		_min = 0;
		_readErrorCode = NO_ERROR;
	}

	Date::Date(int year, int month, int day, int hour, int min)
	{
		_dateOnly = false;
		_year = year;
		_month = month;
		_day = day;
		_hour = hour;
		_min = min;
		_readErrorCode = NO_ERROR;
	}

	void Date::set(int year, int month, int day, int hour, int min)
	{
		_year = year;
		_month = month;
		_day = day;
		_hour = hour;
		_min = min;
		_readErrorCode = NO_ERROR;
	}

	int Date::errCode()
	{
		return _readErrorCode;
	}

	bool Date::bad()const
	{
		return !!_readErrorCode;
	}

	bool Date::dateOnly()const
	{
		return _dateOnly;
	}

	void Date::dateOnly(bool value)
	{
		_dateOnly = value;
		if (value)
		{
			_hour = 0;
			_min = 0;
		}
	}

	bool Date::operator==(const Date& D)const
	{
		return this->value() == D.value();
	}

	bool Date::operator!=(const Date& D)const
	{
		return this->value() != D.value();
	}

	bool Date::operator>(const Date& D)const
	{
		return this->value() > D.value();
	}

	bool Date::operator<(const Date& D)const
	{
		return this->value() < D.value();
	}

	bool Date::operator>=(const Date& D)const
	{
		return this->value() >= D.value();
	}

	bool Date::operator<=(const Date& D)const
	{
		return this->value() <= D.value();
	}

	std::istream& Date::read(std::istream& is = std::cin)
	{
		/*Input formatted text
			...
			If format = YYYY/MM/DD,hh:mm
		*/

		if (_dateOnly) /*or if format is true*/
		{
			
		}
		else
		{
			/*No prompt*/
		}
	}

	std::ostream& Date::write(std::ostream& ostr = std::cout)const
	{

	}
}
