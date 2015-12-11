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

	ostream& NonPerishable::write(ostream& os, bool linear)const
	{
		char buffer[21];

		if (!_err.isClear())
		{
			return os << _err; //??????????????????????????????
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
						<< _name << "|" << right << fixed << setprecision(2) << std::setw(7)
						<< _price << "| t |" << setw(4) << right
						<< _quantity << "|" << setw(9) << setprecision(2) << right << cost() * quantity() << "|";
					return os;
				}
				else
				{
					os << left << setw(MAX_SKU_LEN)
						<< _sku << "|" << left << setw(20)
						<< _name << "|" << right << fixed << setprecision(2) << std::setw(7)
						<< _price << "|   |" << setw(4) << right
						<< _quantity << "|" << setw(9) << setprecision(2) << right << cost() * quantity() << "|";
					return os;
				}
			}
			else
			{
				if (_taxed) {
					os << "Name:" << endl << _name << endl
						<< "Sku: " << _sku << endl
						<< "Price: " << _price << endl
						<< "Price after tax: " << cost() << endl
						<< "Quantity: " << _quantity << endl
						<< "Total Cost: " << _quantity * cost() << endl;
					return os;
				}
				else {
					os << "Name:" << endl << _name << endl
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
	
	istream& NonPerishable::read(istream& is)
	{
		double tmpPrice = 0;
		int tmpInt = 0;
		char buffer[1000];
		char sBuff = 0;

		_err.clear();
		is.clear();

		cout << "NonPerishable Item Entry:" << std::endl;

		cout << "Sku: ";
		is.getline(buffer, 1000);
		sku(buffer);

		cout << "Name:" << endl;
		is.getline(buffer, 1000);
		name(buffer);

		cout << "Price: ";
		is >> tmpPrice;
		//is.ignore(1000, '\n');

		if (is.fail())
		{
			_err.message("Invalid Price Entry"); //???????????????????
			//is.setstate(ios::failbit);
			return is;
		}
		price(tmpPrice);

		cout << "Taxed: ";
		is >> sBuff;
		
		if ('Y' != toupper(sBuff) && 'N' != toupper(sBuff))
		{
			_err.message("Invalid Taxed Entry, (y)es or (n)o");
			is.setstate(ios::failbit);

			return is;
		}
		else
		{
			if (toupper(sBuff) == 'N')
				{taxed(false);}
			else
				{taxed(true);}
		}

		cout << "Quantity: ";
		is >> tmpInt;

		if (is.fail())
		{
			_err.message("Invalid Quantity Entry");
			return is;
		}
		quantity(tmpInt);
		//is.ignore(1000, '\n');

		return is;
	}

	// Save/Load

	fstream& NonPerishable::save(fstream& file)const
	{
		file << "N," << _sku << "," << _name << "," << _price << "," << _taxed << "," << _quantity << endl;
		return file;
	}

	fstream& NonPerishable::load(fstream& file)
	{
		double tmpPrice = 0;
		int tmpInt = 0;
		char buffer[1000];

		file.getline(buffer, 1000, ',');
		sku(buffer);

		file.getline(buffer, 1000, ',');
		name(buffer);

		file >> tmpPrice;
		price(tmpPrice);

		file.ignore(1000,',');
		file >> tmpInt;
		taxed(tmpInt);

		file.ignore(1000, ',');
		file >> tmpInt;
		quantity(tmpInt);

		return file;
	}
}