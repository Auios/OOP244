// OOP244 Workshop 3: Dynamic Memory
// File	w3_in_lab.cpp
// Version 1.0
// Date	2015/05/30
// Author	A.C. Coder
// Description
// This file is used to demonstrate dynamic memory in 
// C++ and to process an array of objects of compound 
// type where the user specifies the number of 
// elements in the array at run-time.
/////////////////////////////////////////////////////
#include <iostream>
#include "Weather.h"
using namespace std;
using namespace SICT;

int main(){
    int n; //the count of days worth of weather
    // initialize the weather pointer here
    Weather* weather;


    cout << "Weather Data\n";
    cout << "=====================" << endl;
    cout << "Days of Weather: ";
    cin >> n;
    cin.ignore();
    // allocate dynamic memory here
    weather = new Weather[n];
    

    for (int i = 0; i < n; i++)
    {
        char date_description[7];
        double high = 0.0, low = 0.0;
        
        // ... add code to accept user input for
        //weather
        
        cout << "Enter date: ";
        cin >> date_description;
        
        cout << "Enter high: ";
        cin >> high;
        
        cout << "Enter low: ";
        cin >> low;
        
        weather[i].set(date_description,low,high);
    }
    
    cout << endl;
    cout << "Weather report:\n";
    cout << "======================" << endl;

    for (int i = 0; i < n; i++)
    {
        weather[i].display();
    }
    
    // deallocate dynamic memory here
    delete [] weather;
    weather = 0;
    
    return 0;
}


/*
Output Example :
Weather Data
== == == == == == == == == == =
Days of Weather : 3
Enter date : Oct / 1
Enter high : 15
Enter low : 10
Enter date : Nov / 13
Enter high : 10
Enter low : 1.1
Enter date : Dec / 15
Enter high : 5.5
Enter low : -6.5

Weather report :
== == == == == == == == == == ==
Oct / 1_______15.0__10.0
Nov / 13______10.0___1.1
Dec / 15_______5.5__ - 6.5
*/
