// Virtual Functions
// Animal.h

#include <iostream>

class Animal {
public:
	virtual void display() const;
};

class Horse : public Animal {
public:
	void display() const;
};