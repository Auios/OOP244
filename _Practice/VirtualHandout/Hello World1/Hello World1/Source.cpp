// Virtual Functions
// h16.cpp

#include "Animal.h"

void foo(Animal a)  {
	a.display();
}
void goo(Animal& a) {
	a.display();
}

int main() {
	Animal* a;

	a = new Animal();
	a->display();
	foo(*a);
	goo(*a);
	delete a;
	a = new Horse();
	a->display();
	foo(*a);
	goo(*a);
	delete a;

	getchar();
	return 0;
}