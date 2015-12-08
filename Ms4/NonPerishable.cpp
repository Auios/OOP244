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
		double tPrice;
		int tInt;
		char t[1000];
		char t2[1000];
		char sub;

		std::cout << "Non-Perishable Item Entry: " << std::endl;
		std::cout << "Sku: ";
		is.getline(t, 1000);
		sku(t);
		std::cout << "Name: " << std::endl;;
		is.getline(t, 1000);
		name(t);
		std::cout << "Price: ";
		is >> tPrice;
		is.ignore(1000, '\n');
		if (is.fail()) {
			_err.message("Invalid Price Entry");
			return is;
		}
		price(tPrice);

		std::cout << "Taxed: ";
		is.getline(t2, 1000);

		if (strlen(t2) > 2) {
			_err.message("Invalid Taxed Entry, (y)es or (n)o");
			is.setstate(std::ios::failbit);
			return is;
		}
		taxed(true);
		std::cout << "Quantity: ";
		is >> tInt;
		if (is.fail()) {
			_err.message("Invalid Quantity Entry");
			return is;
		}
		quantity(tInt);
		is.ignore(1000, '\n');
		return is;
	}

	// Save/Load

	fstream& NonPerishable::save(fstream& file)const
	{
		file << "N," << _sku << "," << _name << "," << _price << "," << _taxed << "," << _quantity << endl;
		return file;
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