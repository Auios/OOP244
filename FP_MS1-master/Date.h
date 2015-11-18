// add your information in here, 
// use dateTester.h comments an a template

#ifndef SICT_DATE_H__
#define SICT_DATE_H__

#define NO_ERROR	0
#define CIN_FAILED	1
#define YEAR_ERROR	2
#define MON_ERROR	3
#define DAY_ERROR	4
#define HOUR_ERROR	5
#define MIN_ERROR	6

#include <iostream>

namespace sict
{
	class Date
	{
	private:
			int value()const;
			int errCode();
			void set(int year, int month, int day, int hour, int min);

			int _min;
			int _hour;
			int _day;
			int _month;
			int _year;

			bool _dateOnly;
			int _readErrorCode;

		public:
			Date();
			Date(int year, int month, int day);
			Date(int year, int month, int day, int hour, int min = 0);

			void set();
			void set(int year, int month, int day, int hour, int min);

			int mdays()const;

			bool bad()const;

			bool dateOnly()const;
			void dateOnly(bool value);

			bool operator==(const Date& D)const;
			bool operator!=(const Date& D)const;
			bool operator>(const Date& D)const;
			bool operator<(const Date& D)const;
			bool operator>=(const Date& D)const;
			bool operator<=(const Date& D)const;

			std::istream& read(std::istream& is = std::cin);
			std::ostream& write(std::ostream& ostr = std::cout)const;
	};
}
#endif