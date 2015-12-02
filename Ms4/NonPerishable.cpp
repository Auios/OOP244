#include <iostream>
#include <cstring>
#include "NonPerishable.h"

using namespace std;

namespace sict
{
	// Operators

	ostream& operator<<(ostream& os, const NonPerishable& A)
	{
		if (!A.isEmpty())
		{
			return A.write(os, true);
		}
		return os;
	}
	istream& operator>>(istream& is, NonPerishable& A)
	{
		return A.read(is);

	}

	// RW

	std::ostream& NonPerishable::write(std::ostream& os, bool linear)const
	{
		if (!isEmpty())
		{
			return os << _sku << _name << _quantity << _price << _taxed;
		}
		else
		{
			return os;
		}
	}
	std::istream& NonPerishable::read(std::istream& is)
	{
		char buf[2000];
		double dbuf;
		int ibuf;
		std::cout << "sku: ";
		is >> buf;
		sku(buf);
		std::cout << "name (no spaces): ";
		is >> buf;
		name(buf);
		std::cout << "qty: ";
		is >> ibuf;
		quantity(ibuf);
		std::cout << "is taxed? (1/0): ";
		is >> ibuf;
		taxed(bool(ibuf));
		std::cout << "price: ";
		is >> dbuf;
		price(dbuf);
		return is;
	}

	// Save/Load

	fstream& NonPerishable::save(fstream& file)const
	{

	}

	fstream& NonPerishable::load(fstream& file)
	{

	}
}