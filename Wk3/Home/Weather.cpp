/*Weather.cpp*/
//  includes go here
#include "Weather.h"
#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;
// sict namespace
namespace SICT
{
    void Weather::set(const char* date, double low, double high)
    {
        // set
        strncpy(_date,date,7);
        _low = low;
        _high = high;
    }
    
	//getDate
	const char* Weather::getDate() const
	{
		return _date;
	}
	
	//getlowtemp
    double Weather::getLowTemp() const
	{
		return _low;
	}
	
    void Weather::display() const
    {
        // display
        cout
        << left << setw(10) << setfill('_') << _date
        << setw(6) << fixed << setfill('_') << right << setprecision(1) << _high
        << setw(6) << fixed << setfill('_') << right << setprecision(1) << _low
        << endl;
    }
}
