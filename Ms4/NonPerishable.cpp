#include "NonPerishable.h"

#include <iostream>
#include <iomanip>
#include <cstring>

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
		char buffer[21];

		if (!_err.isClear())
		{
			return os << _err;
		}
		else
		{
			if (linear)
			{
				strncpy(buffer, _name, strlen(buffer));
				buffer[strlen(buffer)] = 0;
				if (_taxed)
				{
					os << left << setw(MAX_SKU_LEN)
						<< _sku << "|" << left << setw(20)
						<< _name << "|" << right << setprecision(2) << std::setw(7)
						<< _price << "| t |" << setw(4) << right
						<< _quantity << "|" << setw(9) << setprecision(2) << right << cost() << "|";
					return os;
				}
				else
				{
					os << left << setw(MAX_SKU_LEN)
						<< _sku << "|" << left << setw(20)
						<< _name << "|" << right << setprecision(2) << std::setw(7)
						<< _price << "|   |" << setw(4) << right
						<< _quantity << "|" << setw(9) << setprecision(2) << right << cost() << "|";
					return os;
				}
			}
			else
			{
				if (_taxed) {
					os << setw(80) << "Name: " << _name << endl
						<< "Sku: " << _sku << endl
						<< "Price: " << _price << endl
						<< "Price after tax: " << cost() << endl
						<< "Quantity: " << _quantity << endl
						<< "Total Cost: " << _quantity * cost() << endl;
					return os;
				}
				else {
					os << setw(80) << "Name: " << _name << endl
						<< "Sku: " << _sku << endl
						<< "Price: " << _price << endl
						<< "Price after tax: " << "N/A" << endl
						<< "Quantity: " << _quantity << endl
						<< "Total Cost: " << _quantity * cost() << endl;
					return os;
				}
			}
		}
	}
	
	std::istream& NonPerishable::read(std::istream& is)
	{
		double tmpPrice = 0;
		int tmpInt = 0;
		char tmp[1000];
		char tmp2[1000];

		std::cout << "Non-Perishable Item Entry: " << std::endl;

		std::cout << "Sku: ";
		is.getline(tmp, 1000);
		sku(tmp);

		std::cout << "Name: " << std::endl;;
		is.getline(tmp, 1000);
		name(tmp);

		std::cout << "Price: ";
		is >> tmpPrice;
		is.ignore(1000, '\n');

		if (is.fail())
		{
			_err.message("Invalid Price Entry");
			return is;
		}
		price(tmpPrice);

		std::cout << "Taxed: ";
		is.getline(tmp2, 1000);

		if (strlen(tmp2) > 2) {
			_err.message("Invalid Taxed Entry, (y)es or (n)o");
			is.setstate(std::ios::failbit);
			return is;
		}

		taxed(true);
		std::cout << "Quantity: ";
		is >> tmpInt;

		if (is.fail())
		{
			_err.message("Invalid Quantity Entry");
			return is;
		}

		quantity(tmpInt);
		is.ignore(1000, '\n');
		return is;
	}

	// Save/Load

	fstream& NonPerishable::save(fstream& file)const
	{
		file << "N," << _sku << "," << _name << "," << _price << "," << _taxed << "," << _quantity << endl;
		return file;
	}

	std::fstream& NonPerishable::load(std::fstream& file)
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