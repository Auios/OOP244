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
		fs << "P," << _sku << "," << _name << "," << _price << "," << _taxed << "," << _quantity << "," << _expiry << endl;
		return fs;
	}

	fstream& Perishable::load(fstream& file)
	{
		double tmpPrice = 0;
		int tmpInt = 0;
		char buffer[1000];
		char sBuff;
		Date tmpDate;

		file.getline(buffer, 1000, ',');
		sku(buffer);

		file.getline(buffer, 1000, ',');
		name(buffer);

		file >> tmpPrice;
		price(tmpPrice);
		
		file.ignore(1000, ',');
		file.get(sBuff);

		if (sBuff == '1')
		{
			taxed(true);
		}
		else
		{
			taxed(false);
		}

		file.ignore(1000, ',');

		file >> tmpInt;
		quantity(tmpInt);

		_expiry = tmpDate;
		_err.isClear();

		return file;
	}

	istream& Perishable::read(istream& is)
	{
		double tmpPrice = 0;
		int tmpInt = 0;
		char buffer[1000];
		char sBuff;

		_err.clear();
		is.clear();

		Date tmpDate;
		tmpDate.dateOnly(true);

		cout << "Perishable Item Entry: " << endl;

		cout << "Sku: ";
		is.getline(buffer, 1000);
		sku(buffer);

		cout << "Name:" << endl;
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
			{
				taxed(false);
			}
			else
			{
				taxed(true);
			}
		}

		cout << "Quantity: ";
		is >> tmpInt;
		is.ignore(1000,'\n');

		if (is.fail()) {
			_err.message("Invalid Quantity Entry");
			return is;
		}
		quantity(tmpInt);

		cout << "Expiry date (YYYY/MM/DD) : ";
		is >> tmpDate;

		if (tmpDate.bad())
		{
			if (tmpDate.errCode() == CIN_FAILED)
			{
				_err.message("Invalid Date Entry");
				is.setstate(ios::failbit);
			}
			else if (tmpDate.errCode() == YEAR_ERROR)
			{
				_err.message("Invalid Year in Date Entry");
				is.setstate(ios::failbit);
			}
			else if (tmpDate.errCode() == MON_ERROR)
			{
				_err.message("Invalid Month in Date Entry");
				is.setstate(ios::failbit);
			}
			else if (tmpDate.errCode() == DAY_ERROR)
			{
				_err.message("Invalid Day in Date Entry");
				is.setstate(ios::failbit);
			}

			return is;
		}

		_expiry = tmpDate;

		return is;
	}

	ostream& Perishable::write(ostream& os, bool linear)const
	{
		char tmp[] = "|  p|";
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

				os << left << setw(MAX_SKU_LEN) << _sku << "|" << left << setw(20) << _name << "|" << right << fixed
					<< setprecision(2) << setw(7) << _price << tmp << setw(4) << right
					<< quantity() << "|" << setw(9) << fixed << setprecision(2) << right << cost() * quantity() << "|";
			}
			else
			{
				if (_taxed)
				{
					os << "Name:" << endl << name() << endl
						<< "Sku: " << sku() << endl
						<< "Price: " << price() << endl
						<< "Price after tax: " << cost() << endl
						<< "Quantity: " << quantity() << endl
						<< "Total Cost: " << quantity() * cost() << endl
						<< "Expiry date: " << _expiry << endl;
				}
				else
				{
					os << "Name:" << endl << name() << endl
						<< "Sku: " << sku() << endl
						<< "Price: " << price() << endl
						<< "Price after tax: " << "N/A" << endl
						<< "Quantity: " << quantity() << endl
						<< "Total Cost: " << quantity()*cost() << endl
						<< "Expiry date: " << _expiry << endl;
				}
			}
			return os;
		}
	}
}