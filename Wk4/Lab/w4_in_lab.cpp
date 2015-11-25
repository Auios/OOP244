// OOP244 Workshop 4: Constructors
// File: w4_in_lab.cpp
// Version: 1.0
// Date: 2015/10/4
// Author: Fardad Soleimanloo
// Description:
// This file tests in-lab section of your workshp
/////////////////////////////////////////////


#include <iostream>
#include "Enrollment.h"

using namespace std;
using namespace sict;

void displayEnrollments(const Enrollment& e1, const Enrollment& e2);

int main(){
  // constructors
  Enrollment e1("College English", "EAC150", 2015, 1, 5);
  Enrollment e2, e3;
  Enrollment BadE[9] = {
    Enrollment("Intro to Programming in C", "IPC144", 2015, 1, 5),
    Enrollment((char*)0, "IPC144", 2015, 1, 5),
    Enrollment("Intro to Programming in C", (char*)0, 2015, 1, 5),
    Enrollment("", "IPC144", 2015, 1, 5),
    Enrollment("Intro to Programming in C", "", 2015, 1, 5),
    Enrollment("Intro to Programming in C", "IPC144", 2014, 1, 5),
    Enrollment("Intro to Programming in C", "IPC144", 2015, 0, 5),
    Enrollment("Intro to Programming in C", "IPC144", 2015, 4, 5),
    Enrollment("Intro to Programming in C", "IPC144", 2015, 1, 0)
  };

  cout << "Testing Enrollment objects" << endl << endl;

  // testing two invalid Enrollments
  displayEnrollments(e3, e2);

  // testing valid and invalid Enrollments
  displayEnrollments(e1, e2);

  // setting the second one to OOP244
  e2.set("Object Oriented Programming", "OOP244", 2015, 1, 5);

  displayEnrollments(e1, e2);

  // setting the enrollment to true;
  e2.set("Object Oriented Programming", "OOP244", 2015, 1, 5, true);

  displayEnrollments(e1, e2);

  // removing conflict;
  e2.set("Object Oriented Programming", "OOP244", 2015, 1, 6);

  displayEnrollments(e1, e2);

  // making sure all the conditions are met for an invalid Enrollment.
  cout << endl << "Only index 0 should be valid:" << endl;
  for (int i = 0; i < 9; i++){
    cout <<"index: " << i << " - "<< (BadE[i].valid() ? "V" : "Not v") << "alid." << endl;
  }
  return 0;
}
void displayEnrollments(const Enrollment& e1, const Enrollment& e2){
  cout << "----------------------------------------------" << endl;
  e1.display();
  cout << (e1.isEnrolled() ? "E" : "Not e") << "nrolled" << endl;
  e2.display();
  cout << endl<<  "There is " << (e1.hasConflict(e2)? "" : "not ") << "a conflict!" << endl;
}

/* output:
Testing Enrollment objects

----------------------------------------------
Invalid enrollment!
Not enrolled
Invalid enrollment!

There is not a conflict!
----------------------------------------------
College English
EAC150, Year: 2015 semester: 1 Slot: 5
Status: Not enrolled.
Not enrolled
Invalid enrollment!

There is not a conflict!
----------------------------------------------
College English
EAC150, Year: 2015 semester: 1 Slot: 5
Status: Not enrolled.
Not enrolled
Object Oriented Programming
OOP244, Year: 2015 semester: 1 Slot: 5
Status: Not enrolled.

There is a conflict!
----------------------------------------------
College English
EAC150, Year: 2015 semester: 1 Slot: 5
Status: Not enrolled.
Not enrolled
Object Oriented Programming
OOP244, Year: 2015 semester: 1 Slot: 5
Status: Enrolled.

There is a conflict!
----------------------------------------------
College English
EAC150, Year: 2015 semester: 1 Slot: 5
Status: Not enrolled.
Not enrolled
Invalid enrollment!

There is not a conflict!

Only index 0 should be valid:
index: 0 - Valid.
index: 1 - Not valid.
index: 2 - Not valid.
index: 3 - Not valid.
index: 4 - Not valid.
index: 5 - Not valid.
index: 6 - Not valid.
index: 7 - Not valid.
index: 8 - Not valid.
*/