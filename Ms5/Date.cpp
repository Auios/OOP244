#include <iomanip>
#include <iostream>
#include <ctime>
using namespace std;
#include "Date.h"
#include "POS.h"
namespace sict
{

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

	void Date::set(int year, int month, int day, int hour, int min)
	{
		_year = year;
		_month = month;
		_day = day;
		_hour = hour;
		_min = min;
		_readErrorCode = NO_ERROR;
	}

	void Date::resetError()
	{
		_readErrorCode = NO_ERROR;
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

	int Date::errCode()const
	{
		return _readErrorCode;
	}

	void Date::errCode(int errorCode)
	{
		_readErrorCode = errorCode;
	}

	bool Date::bad()const
	{
		if (_readErrorCode == NO_ERROR)
		{
			return false;
		}
		else
		{
			return true;
		}
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

	int Date::valid()
	{
		//_readErrorCode = NO_ERROR;
		errCode(NO_ERROR);

		if(_dateOnly)
		{
			if (_year > MAX_YEAR || _year < MIN_YEAR)
			{
				_year = MIN_YEAR + 1;
				return YEAR_ERROR;
			}
			else if (_month > 12 || _month < 1)
			{
				_month = 1;
				return MON_ERROR;
			}
			else if (_day <= 0 || _day > mdays())
			{
				_day = 1;
				return DAY_ERROR;
			}
		}

		if(!_dateOnly)
		{	
			if (_year > MAX_YEAR || _year < MIN_YEAR)
			{
				_year = MIN_YEAR + 1;
				return YEAR_ERROR;
			}
			else if (_month > 12 || _month < 1)
			{
				_month = 1;
				return MON_ERROR;
			}
			else if (_day <= 0 || _day > mdays())
			{
				_day = 1;
				return DAY_ERROR;
			}
			else if(_hour <= 0 || _hour > MAX_HOUR)
			{
				_hour = 1;
				return HOUR_ERROR;
			}
			else if(_min <= 0 || _min > MAX_MIN)
			{
				_min = 1;
				return MIN_ERROR;
			}
		}
		return NO_ERROR;
	}

	std::istream& Date::read(std::istream& is)
	{
		//_readErrorCode = NO_ERROR;
		errCode(NO_ERROR);

		is >> _year;
		is.ignore(100,'/');

		is >> _month;
		is.ignore(100,'/');

		is >> _day;
		is.ignore(100, '\n');

		/*
		if(!_dateOnly)
		{
			is.ignore(5,',');

			is >> _hour;
			is.ignore(2,':');

			is >> _min;
		}
		*/

		errCode(valid());
		if (is.fail())
		{
			_readErrorCode = CIN_FAILED;
			return is;
		}
		
		return is;
	}

	std::ostream& Date::write(std::ostream& os) const
	{
		if(_dateOnly)
		{
			os << _year << '/' << std::right << std::setfill('0') << std::setw(2) << _month << '/' << std::right << std::setfill('0') << std::setw(2) << _day;
		}
		else
		{
			os << _year << '/' << std::right << std::setfill('0') << std::setw(2) << _month << '/' << std::right << std::setfill('0') << std::setw(2) << _day << ", " << std::right << std::setfill('0') << std::setw(2) << _hour << ':' << std::right << std::setfill('0') << std::setw(2) << _min;
		}
		return os;
	}

	std::ostream& operator<<(std::ostream& os, const Date& d)
	{
		d.write(os);
		return os;
	}

	std::istream& operator>>(std::istream& is, Date& d)
	{
		d.read(is);
		return is;
	}
}
