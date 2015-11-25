// compilation safegaurds
#ifndef _SICT_WEATHER_H_
#define _SICT_WEATHER_H_

/*Weather.h*/

 // sict namespace
 namespace SICT
 {  
    class Weather
    {
    // member variables
        char _date[7];
        double _high;
        double _low;
        
        public:
        // member function
        void set(const char* date, double low, double high);
		const char* getDate() const;
		double getLowTemp() const;
        void display() const;
    };
}

#endif
