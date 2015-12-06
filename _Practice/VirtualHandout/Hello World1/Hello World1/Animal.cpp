// Virtual Functions
// Animal.cpp

#include "Animal.h"

void Animal::display() const {
	std::cout << "Animal" << std::endl;
}

void Horse::display() const {
	Animal::display();
	std::cout << "Horse" << std::endl;
}