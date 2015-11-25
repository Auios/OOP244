#include <iostream>
#include <iomanip>

using namespace std;

// int checkout()
// Description: prompts for and accepts an option selection from 
// standard input and returns the integer price for the selected option
// Outputs: returns the price of the selected option, -1 to cancel, 10 to pay 
// or 0 otherwise
///////////////////////////////////////////////////////////////////////////
int checkout(){
	int iSelection = 0;			//storage of the user response
	int iPrice = 0;
	cout << '\n';
	cout << "Please select from the following options :\n";
	cout << " 1 Shelf unit $2\n";
	cout << " 2 Desk $4\n";
	cout << " 3 Bed $4\n";
	cout << " 4 Chair $2\n";
	cout << " 5 Pay\n";
	cout << " 6 Cancel\n";

	cin >> iSelection;
	if ((iSelection > 0) && (iSelection < 7)){//if user response is valid
		if (iSelection == 1 || iSelection == 4)
			iPrice = 2;
		else if (iSelection < 5)
			iPrice = 4;
		else if (iSelection == 5)
			iPrice = 10;
		else
			iPrice = -1;
		cout << "Thank you\n";
	}
	else
		cout << "Incorrect entry\n";

	return iPrice;
}