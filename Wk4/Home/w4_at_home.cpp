// OOP244 Workshop 4: Constructors 
// File: w4_at_home.cpp
// Version: 1.0
// Date: 2015/10/4
// Author: Fardad Soleimanloo
// Description:
// This file tests at-home section of your workshop
/////////////////////////////////////////////


#include <iostream>
#include "Enrollment.h"
using namespace std;
using namespace sict;
void displayEnrollments(const Enrollment& e1, const Enrollment& e2);
int main(){
  // change this slot array to an Enrollment pointer dynamic memory allocation. 
  Enrollment slots[3];
  Enrollment current;
  char name[31];
  char code[11];
  int year;
  int semester;
  int slot;
  int i = 0;
  //  uncomment the following comment to dynamically allocate memory for slots.
  //  cout << "Please enter the number of course sections: ";

  cout << "Please enter the following " << 3 << " course sections for enrollment:" << endl;
  while (i < 3){
    cout << "Course section " << (i + 1) << ":" << endl
      << "Subject Name: ";
    cin.getline(name, 30, '\n');
    cout << "Subject Code: ";
    cin.getline(code, 10, '\n');
    cout << "Year: ";
    cin >> year;
    cout << "Semester: ";
    cin >> semester;
    cout << "Slot: ";
    cin >> slot;
    cin.ignore(1000, '\n');
    current.set(name, code, year, semester, slot);
    if (current.valid()){
      int c;
      if ((c = current.enrol(slots, 3)) == 0){
        char res;
        slots[i] = current;
        cout << "Enrolled!" << endl;
        i++;
        cout << "Continue? (y/n)";
        res = cin.get();
        if (res != 'y' && res != 'Y'){
          i = 3;
        }
        cin.ignore(1000, '\n');
      }
      else{
        cout << "There is a conflict with the following, please change enrollment time: " << endl;
        slots[c - 1].display();
      }
    }
    else{
      cout << "Invalid information entered, please redo: " << endl;
    }
  }
  for (i = 0; i < 3; i++){
    cout << "------------------------------" << endl;
    slots[i].display();
  }
  // testing withdraw();
  slots[0].withdraw();
  slots[0].display();

  // deallocate the slots memory here;
  return 0;
}
