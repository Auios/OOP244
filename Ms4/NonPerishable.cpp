#include <iostream>
#include <iomanip>
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
		const int len = 20;
		char tmpNme[len + 1];

		if(_err.isClear())
		{
			if(linear)
				strncpy(tmpNme,_name,len);
				tmpNme[len] = 0;

				if (_taxed)
				{
					return os
						<< setfill(' ')

						<< setw(MAX_SKU_LEN)
						<< left
						<< _sku

						<< "|"

						<< setw(len)
						<< left
						<< tmpNme

						<< "|"

						<< setw(7)
						<< setprecision(2)
						<< right
						<< _price

						<< "| t |"

						<< setw(4)
						<< right
						<< _quantity

						<< "|"

						<< setw(9)
						<< setprecision(2)
						<< right
						<< _price;
				}
				else
				{
					return os
					<< setfill(' ')

					<< setw(MAX_SKU_LEN)
					<< left
					<< _sku

					<< "|"

					<< setw(len)
					<< left
					<< tmpNme

					<< "|"

					<< setw(7)
					<< setprecision(2)
					<< right
					<< _price

					<< "|   |"

					<< setw(4)
					<< right
					<< _quantity

					<< "|"

					<< setw(9)
					<< setprecision(2)
					<< right
					<< _price;
				}
			}
			else
			{
				if (_taxed)
				{
					strncpy(tmpNme, _name, len);
					tmpNme[len] = 0;

					return os
					<< "Name:" << endl
					<< tmpNme << endl
					<< "Sku: " << _sku << endl
					<< "Price: " << _price << endl
					<< "Price after tax: " << cost() << endl
					<< "Quantity: " << _quantity << endl
					<< "Total Cost: " cost() * _quantity << endl;
				}
				else
				{
					strncpy(tmpNme, _name, len);
					tmpNme[len] = 0;

					return os
					<< "Name:" << endl
					<< tmpNme << endl
					<< "Sku: " << _sku << endl
					<< "Price: " << _price << endl
					<< "Price after tax: N/A" << endl
					<< "Quantity: " << _quantity << endl
					<< "Total Cost: " cost() * _quantity << endl;
				}
			}
		}
		else
		{
			return os << _err.;
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