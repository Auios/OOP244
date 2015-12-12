#include "NonPerishable.h"

#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

namespace sict
{
	fstream& NonPerishable::save(fstream& file)const
	{
		file << "N," << sku() << "," << name() << "," << price() << "," << taxed() << "," << quantity() << endl;
		return file;
	}

	fstream& NonPerishable::load(fstream& file)
	{
		double tmpPrice = 0;
		int tmpInt = 0;
		char buffer[1000];
		char tmpSku[MAX_SKU_LEN + 1];
		char tmpTax;

		file.getline(tmpSku, MAX_SKU_LEN + 1,',');
		file.getline(buffer, 1000, ',');
		file >> tmpPrice;
		file.ignore();
		file.get(tmpTax);
		file.ignore();
		file >> tmpInt;
		file.ignore();

		if (tmpTax == '1')
		{
			taxed(true);
		}
		else
		{
			taxed(false);
		}

		quantity(tmpInt);
		price(tmpPrice);
		name(buffer);
		sku(tmpSku);

		return file;
	}

	ostream& NonPerishable::write(ostream& os, bool linear)const
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
				strncpy(buffer, name(), 20);
				buffer[20] = 0;
				if (taxed())
				{
					os.setf(ios::fixed);
					os.precision(2);
					os
						<< left << setw(MAX_SKU_LEN)
						<< sku() << "|" << left << setw(20)
						<< name() << "|" << right << setw(7)
						<< price() << "| t |" << setw(4) << right
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
						<< name() << "|" << right << std::setw(7)
						<< price() << "|   |" << setw(4) << right
						<< quantity() << "|" << setw(9) << right
						<< cost() * quantity() << "|";
				}
			}
			else
			{
				if (taxed()) {
					os
						<< "Name: " << endl << _name << endl
						<< "Sku: " << sku() << endl
						<< "Price: " << price() << endl
						<< "Price after tax: " << cost() << endl
						<< "Quantity: " << quantity() << endl
						<< "Total Cost: " << cost() * quantity() << endl;
				}
				else {
					os
						<< "Name: " << endl << name() << endl
						<< "Sku: " << sku() << endl
						<< "Price: " << price() << endl
						<< "Price after tax: " << "N/A" << endl
						<< "Quantity: " << quantity() << endl
						<< "Total Cost: " << cost() * quantity() << endl;
				}
			}
			return os;
		}
	}
	
	istream& NonPerishable::read(istream& is)
	{
		double tmpPrice = 0;
		int tmpInt = 0;
		char buffer[1000];
		char tmpSku[1000];
		char sBuff = 0;

		_err.clear();
		is.clear();

		cout << endl
			<< "Non-Perishable Item Entry:" << std::endl;

		cout << "Sku: ";
		is.getline(tmpSku, 1000);

		cout << "Name:" << std::endl;;
		is.getline(buffer, 1000);

		cout << "Price: ";
		is >> tmpPrice;

		if (is.fail())
		{
			_err.message("Invalid Price Entry");
		}
		else
		{
			std::cout << "Taxed: ";
			is >> sBuff;
			if ('Y' != toupper(sBuff) && 'N' != toupper(sBuff)) {
				_err.message("Invalid Taxed Entry, (y)es or (n)o");
				is.setstate(ios::failbit);
			}
			else
			{
				cout << "Quantity: ";
				is >> tmpInt;

				if (is.fail())
				{
					_err.message("Invalid Quantity Entry");
				}
				else
				{
					sku(tmpSku);
					name(buffer);
					price(tmpPrice);
					quantity(tmpInt);

					if (toupper(sBuff) == 'N')
					{
						taxed(false);
					}
					else
					{
						taxed(true);
					}
				}
			}
		}

		return is;
	}
}