#include <iomanip>
#include <iostream>
#include <ctime>
using namespace std;
#include "Date.h"
#include "POS.h"
namespace sict {

	void Date::set() {
		time_t t = time(NULL);
		tm lt = *localtime(&t);
		_day = lt.tm_mday;
		_mon = lt.tm_mon + 1;
		_year = lt.tm_year + 1900;
		if (dateOnly()) {
			_hour = _min = 0;
		}
		else {
			_hour = lt.tm_hour;
			_min = lt.tm_min;
		}
	}

	int Date::value()const {
		return _year * 535680 + _mon * 44640 + _day * 1440 + _hour * 60 + _min;
	}


	int Date::mdays()const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int mon = _mon >= 1 && _mon <= 12 ? _mon : 13;
		mon--;
		return days[mon] + int((mon == 1)*((_year % 4 == 0) && (_year % 100 != 0)) || (_year % 400 == 0));
	}

	Date::Date() {
		_dateOnly = false;
		set();
	}
	Date::Date(int year, int mon, int day) {
		_dateOnly = true;
		_year = year;
		_mon = mon;
		_day = day;
		_hour = 0;
		_min = 0;
		_readErrorCode = NO_ERROR;
	}
	Date::Date(int year, int mon, int day, int hour, int min) {
		_dateOnly = false;
		_year = year;
		_mon = mon;
		_day = day;
		_hour = hour;
		_min = min;
		_readErrorCode = NO_ERROR;
	}

	void Date::errCode(int errorCode) {
		_readErrorCode = errorCode;
	}
	void Date::set(int year, int mon, int day, int hour, int min) {
		_year = year;
		_mon = mon;
		_day = day;
		_hour = hour;
		_min = min;
		_readErrorCode = NO_ERROR;
	}

	bool Date::operator==(const Date& D)const {
		if (this->value() == D.value())
			return true;
		return false;
	}
	bool Date::operator!=(const Date& D)const {
		if (this->value() != D.value())
			return true;
		return false;
	}
	bool Date::operator<(const Date& D)const {
		if (this->value() < D.value())
			return true;
		return false;
	}
	bool Date::operator>(const Date& D)const {
		if (this->value() > D.value())
			return true;
		return false;
	}
	bool Date::operator<=(const Date& D)const {
		if (this->value() <= D.value())
			return true;
		return false;
	}
	bool Date::operator>=(const Date& D)const {
		if (this->value() >= D.value())
			return true;
		return false;
	}

	int Date::errCode()const {
		return _readErrorCode;
	}
	bool Date::bad()const {
		if (_readErrorCode != 0)
			return true;
		return false;
	}
	bool Date::dateOnly()const {
		return _dateOnly;
	}
	void Date::dateOnly(bool value) {
		_dateOnly = value;
		if (value == true) {
			_hour = 0;
			_min = 0;
		}
	}
	int Date::valid() {
		if (_dateOnly) {
			if (_year > MAX_YEAR || _year < MIN_YEAR)
				return YEAR_ERROR;
			else if (_mon > 12 || _mon < 1)
				return MON_ERROR;
			else if (_day <= 0 || _day > mdays())
				return DAY_ERROR;
			
		}
		if(!_dateOnly){
			if (_year > MAX_YEAR || _year < MIN_YEAR)
				return YEAR_ERROR;
			else if (_mon > 12 || _mon < 1)
				return MON_ERROR;
			else if (_day <= 0 || _day > mdays())
				return DAY_ERROR;
			else if (_hour < MIN_HOUR|| _hour > MAX_HOUR)
				return HOUR_ERROR;
			else if (_min < MIN_MIN || _min > MAX_MIN)
				return MIN_ERROR;
			
		}
		return NO_ERROR;
	}
std::istream& Date::read(std::istream& is) {

	is >> _year;
	is.ignore(4, '/');

	is >> _mon;
	is.ignore(2, '/');

	is >> _day;

	if (!_dateOnly) {
		is.ignore(5, ',');

		is >> _hour;
		is.ignore(2, ':');

		is >> _min;
	}
	errCode(valid());
	if (is.fail()) {
		_readErrorCode = CIN_FAILED;
		return is;
	}
	return is;

}
	std::ostream& Date::write(std::ostream& os) const {
		if (_dateOnly) {
			os << _year << '/' << std::right << std::setfill('0') << std::setw(2) << _mon << '/' << std::right << std::setfill('0') << std::setw(2) << _day;
			return os;
		}
		else {
			os << _year << '/' << std::right << std::setfill('0') << std::setw(2) << _mon << '/' << std::right << std::setfill('0') << std::setw(2) << _day << ", " << std::right << std::setfill('0') << std::setw(2) << _hour << ":" << std::right << std::setfill('0') << std::setw(2) << _min;
		return os;
		}
	}
	std::ostream& operator<<(std::ostream& os, const Date& d) {
		d.write(os);
		return os;
	}
	std::istream& operator>>(std::istream& is, Date& d) {
		d.read(is);
		return is;
	}
}