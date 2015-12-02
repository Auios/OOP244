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

		if(_err.isClear())
		{
			if(linear)
			{
				int len = 20;
				char tmpNme[len+1];

				strncpy(tmpNme,_name,len);
				tmpNme[len] = 0;

				return os

				<< setfill(' ')

				<< setw(MAX_SKU_LEN)
				<< left
				<< _sku

				<< "|"

				<< setw(len)
				<< left
				<< _tmpNme

				<< "|";

				<< setw(7)
				<< setprecision(2)
				<< right
				<< _price

				if(_taxed){<< "| t |"}else{<< "|   |"}

				<< setw(4)
				<< right
				<< quantity

				<< "|"

				<< setw(9)
				<< setprecision(2)
				<< right
				<< _price
			}
			else
			{
				int len = 80;
				char tmpNme[len+1];

				strncpy(tmpNme,_name,len);
				tmpNme[len] = 0;

				return os

				<< "Name:" << endl
				<< tmpNme << endl
				<< "Sku: " << _sku << endl
				<< "Price: " << _price << endl

				if(_taxed)
					{<< "Price after tax: " << cost() << endl}
				else
					{<< "Price after tax: N/A" << endl}

				<< "Quantity: " << _quantity << endl
				<< "Total Cost: " cost()*quantity << endl;
			}
		}
		else
		{
			return os << _err;
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

	std::fstream& NonPerishable::load(std::fstream& fs)
	{
		double tPrice;
		int tInt;
		char t[1000];
		fs.getline(t, 1000, ',');
		sku(t);
		fs.getline(t, 1000, ',');
		name(t);
		fs << tPrice;
		price(tPrice);
		fs.ignore(',');
		fs << tInt;
		taxed(tInt);
		fs.ignore(',');
		fs << tInt;
		quantity(tInt);
		return fs;
	}
}