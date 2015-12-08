#include "Perishable.h"
#include "Date.h"
#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

namespace sict
{
	Perishable::Perishable()
	{
		_expiry.dateOnly(true);
	}

	const Date& Perishable::expiry()const
	{
		return  _expiry;
	}

	void Perishable::expiry(const Date &val)
	{
		_expiry = val;
	}

	fstream& Perishable::save(fstream& fs)const
	{
		fs << "P," << _sku << "," << _name << "," << _price << "," << _taxed << "," << _quantity << _expiry << endl;
		return fs;
	}

	fstream& Perishable::load(fstream& file)
	{
		double tmpPrice = 0;
		int tmpInt = 0, tmpInt1 = 0, tmpInt2 = 0;
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

		file.ignore(',');
		file << tmpInt;

		file.ignore('/');
		file << tmpInt1;

		file.ignore('/');
		file << tmpInt2;

		_expiry.set(tmpInt, tmpInt1, tmpInt2, 0, 0);

		return file;
	}

	istream& Perishable::read(istream& is)
	{
		double tmpPrice = 0;
		int tmpInt = 0;
		char buffer[1000];
		char sBuff;

		cout << "Perishable Item Entry: " << endl;
		cout << "Sku: ";
		is.getline(buffer, 1000);
		sku(buffer);

		cout << "Name: " << endl;
		is.getline(buffer, 1000);
		name(buffer);

		std::cout << "Price: ";
		is >> tmpPrice;

		if (is.fail())
		{
			_err.message("Invalid Price Entry");
			return is;
		}

		price(tmpPrice);
		cout << "Taxed: ";
		is.get(sBuff);
		is.ignore(1000, '\n');

		if (sBuff == 'y' || sBuff == 'Y' || sBuff == 'n' || sBuff == 'N')
		{
			if (sBuff == 'y' || sBuff == 'Y')
			{
				taxed(true);
			}
			if (sBuff == 'n' || sBuff == 'N')
			{
				taxed(false);
			}
		}
		else
		{
			_err.message("Invalid Taxed Entry, (y)es or (n)o");
			is.setstate(ios::failbit);

			return is;
		}

		cout << "Quantity: ";
		is >> tmpInt;
		is.ignore('\n');

		if (is.fail()) {
			_err.message("Invalid Quantity Entry");
			return is;
		}
		quantity(tmpInt);
		cout << "Expiry date (YYYY/MM/DD) : ";
		is >> _expiry;
		if (_expiry.errCode() == CIN_FAILED)
		{
			_err.message("Invalid Date Entry");
			is.setstate(ios::failbit);
			return is;
		}
		else if (_expiry.errCode() == YEAR_ERROR)
		{
			_err.message("Invalid Year in Date Entry");
			is.setstate(ios::failbit);
			return is;
		}
		else if (_expiry.errCode() == MON_ERROR)
		{
			_err.message("Invalid Month in Date Entry");
			is.setstate(ios::failbit);
			return is;
		}
		else if (_expiry.errCode() == DAY_ERROR)
		{
			_err.message("Invalid Day in Date Entry");
			is.setstate(ios::failbit);
			return is;
		}
		is.ignore('\n');
		return is;
	}

	ostream& Perishable::write(ostream& os, bool linear)const
	{
		char tmp[] = "| p|";
		char tmp2[21];

		if (_taxed)
		{
			strcpy(tmp,"| tp|");
		}

		if (!_err.isClear())
		{
			return os << _err;
		}
		else
		{
			if (linear)
			{
				strncpy(tmp2, name(), 20);
				tmp2[20] = '\0';

				os << left << setw(MAX_SKU_LEN) << _sku << "|" << left << setw(20) << _name << "|" << right
					<< setprecision(2) << setw(7) << _price << tmp << setw(4) << right
					<< quantity() << "|" << setw(9) << setprecision(2) << right << cost() << "|";

				return os;
			}
			else
			{
				if (_taxed)
				{
					os << setw(80) << "Name: " << _name << endl
						<< "Sku: " << _sku << endl
						<< "Price: " << price() << endl
						<< "Price after tax: " << cost() << endl
						<< "Quantity: " << _quantity << endl
						<< "Total Cost: " << _quantity*cost() << endl
						<< "Expiry date:" << _expiry << endl;

					return os;
				}
				else
				{
					os << setw(80) << "Name: " << name() << std::endl
						<< "Sku: " << sku() << std::endl
						<< "Price: " << price() << std::endl
						<< "Price after tax: " << "N/A" << std::endl
						<< "Quantity: " << quantity() << std::endl
						<< "Total Cost: " << quantity()*cost() << std::endl
						<< "Expiry date:" << _expiry << std::endl;

					return os;
				}
			}
		}
	}
}