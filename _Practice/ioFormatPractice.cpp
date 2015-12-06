#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

int main( )
{
	int len = 10;
	char OMG[] = "abcdefghijklmnopqrstuvwxyz";
	char tempOMG[len + 1];

	strncpy(tempOMG,OMG,len);
	tempOMG[len] = 0;

	cout << "---Start---" << endl
	<< "."
	<< setfill(' ')

	<< setw(len)
	<< left

	<< tempOMG

	<< "|"
	<< setw(len)
	<< right
	<< -456
	<< "."
	<< endl;

     return 0;
 }