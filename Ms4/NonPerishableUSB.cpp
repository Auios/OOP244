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
			if (_err.isClear())
			{
				return os << _sku << _name << _quantity << _price << _taxed;
			}
			else
			{
				return os << _err.message();
			}
		}
		else
		{
			return os;
		}
	}
	std::istream& NonPerishable::read(std::istream& is)
	{
		char buf[2000];
		char itax;
		double dbuf;
		//int ibuf;

		std::cout << "Sku: ";
		is >> buf;
		sku(buf);

		std::cout << "Name: " << endl;
		is >> buf;
		name(buf);

		std::cout << "Price: ";
		is >> dbuf;
		if (is.fail())
		{
			_err.message("Invalid Price Entry");
			return is;
		}
		price(dbuf);

		std::cout << "is taxed? (1/0): " << endl;
		is >> itax;
		if (itax != 'y' && itax != 'n')
		{
			is.setstate(ios::failbit);
			_err.message("Invalid Taxed Entry");
			return is;
		}
		taxed(bool(itax));

		return is;
	}

	// Save/Load

	std::fstream& NonPerishable::save(fstream& file)const
	{
		file << "N," << sku() << "," << name() << "," << price() << "," << taxed() << "," << quantity() << std::endl;
		return file;
	}

	std::fstream& NonPerishable::load(fstream& file)
	{
		double tmpPrice = 0;
		int tmpInt = 0;
		char buffer[1000];
		file.getline(buffer, 1000, ',');
		sku(buffer);
		file.getline(buffer, 1000, ',');
		name(buffer);
		file << tmpPrice;
		price(tmpPrice);
		file.ignore(',');
		file << tmpInt;
		taxed(tmpInt);
		file.ignore(',');
		file << tmpInt;
		quantity(tmpInt);
		return file;
	}
}