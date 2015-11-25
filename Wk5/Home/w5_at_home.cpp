// OOP244 Workshop 5: Classes with resources 
// File: w5_in_lab.cpp
// Version: 1.0
// Date: 2015/10/13
// Author: Fardad Soleimanloo
// Description:
// This file tests at-home section of your workshp
/////////////////////////////////////////////

#include <iostream>
using namespace std;
#include "Contact.h"
using namespace sict;

int main() {
	Contact c("Empty Contact", 3);
	c.display();
	cout << "Enter Contact information: " << endl;
	c.read();
	c.display();
	cout << endl;
	for (int i = 0; i < 1000000; i++) {
		Contact temp("Testing the contact with a looooong "
			"name that should be taken care of", 20);
		if (!(i % 100000)) {
			cout << i << ":" << endl;
			temp.display();
		}
	}
	return 0;
}