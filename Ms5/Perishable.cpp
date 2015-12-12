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
		return _expiry;
	}

	void Perishable::expiry(const Date &val)
	{
		_expiry = val;
	}

	fstream& Perishable::save(fstream& fs)const
	{
		fs << "P," << sku() << "," << name() << "," << price() << "," << taxed() << "," << quantity() << "," << _expiry << endl;
		return fs;
	}

	fstream& Perishable::load(fstream& file)
	{
		double tmpPrice = 0;
		int tmpInt = 0;
		char buffer[1000];
		char tmpSku[MAX_SKU_LEN + 1];
		char sBuff;
		Date tmpDate;

		file.getline(tmpSku, MAX_SKU_LEN + 1, ',');
		file.getline(buffer, 1000, ',');
		file >> tmpPrice;
		file.ignore();
		file.get(sBuff);
		file.ignore();
		file >> tmpInt;
		file.ignore();
		file >> _expiry;

		quantity(tmpInt);
		price(tmpPrice);
		name(buffer);
		sku(tmpSku);

		if (sBuff == '1')
		{
			taxed(true);
		}
		else
		{
			taxed(false);
		}

		return file;
	}

	ostream& Perishable::write(ostream& os, bool linear)const
	{
		if (!_err.isClear())
		{
			return os << _err;
		}
		else
		{
			if (linear)
			{
				if (taxed())
				{
					os.setf(ios::fixed);
					os.precision(2);
					os
						<< left << setw(MAX_SKU_LEN)
						<< sku() << "|" << left << setw(20)
						<< name() << "|" << right << setw(7)
						<< price() << "| tp|" << setw(4) << right
						<< quantity() << "|" << setw(9) << right
						<< cost() * quantity() << "|";
				}
				else
				{
					os.setf(ios::fixed);
					os.precision(2);
					os
						<< left << setw(MAX_SKU_LEN)
						<< sku() << "|" << left << setw(20)
						<< name() << "|" << right << setw(7)
						<< price() << "|  p|" << setw(4) << right
						<< quantity() << "|" << setw(9) << right
						<< cost() * quantity() << "|";
					return os;
				}
			}
			else
			{
				if (taxed())
				{
					os
						<< "Name:" << endl << name() << endl
						<< "Sku: " << sku() << endl
						<< "Price: " << price() << endl
						<< "Price after tax: " << cost() << endl
						<< "Quantity: " << quantity() << endl
						<< "Total Cost: " << cost() * quantity() << endl
						<< "Expiry date: " << _expiry << endl;
					return os;
				}
				else
				{
					os
						<< "Name:" << endl << name() << endl
						<< "Sku: " << sku() << endl
						<< "Price: " << price() << endl
						<< "Price after tax: " << "N/A" << endl
						<< "Quantity: " << quantity() << endl
						<< "Total Cost: " << cost() * quantity() << endl
						<< "Expiry date: " << _expiry << endl;
					return os;
				}
			}
			return os;
		}
	}

	istream& Perishable::read(istream& is)
	{
		double tmpPrice = 0;
		int tmpInt = 0;
		char buffer[1000];
		char sBuff;

		_expiry.resetError();

		Date tmpDate;
		tmpDate.dateOnly(true);

		cout << endl
			<< "Perishable Item Entry: " << endl;

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
		is.ignore(1000, '\n');

		if (is.fail()) {
			_err.message("Invalid Quantity Entry");
			return is;
		}
		quantity(tmpInt);

		cout << "Expiry date (YYYY/MM/DD): ";
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
}