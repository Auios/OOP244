#include "NonPerishable.h"
#include <iostream>
#include <iomanip>
#include <cstring>

namespace sict {
	std::fstream& NonPerishable::save(std::fstream& fs)const {
		fs << "N," << sku() << "," << name() << "," << price() << "," << taxed() << "," << quantity() << std::endl;
		return fs;
	}
	std::fstream& NonPerishable::load(std::fstream& fs) {
		double tPrice;
		int tInt;
		char t[1000];
		char itax;
		fs.getline(t, 1000, ',');
		sku(t);
		fs.getline(t, 1000, ',');
		name(t);
		fs >> tPrice;
		price(tPrice);
		fs.ignore(1000,',');
		fs.get(itax);
		if (itax == '1')
			taxed(true);
		else
			taxed(false);
		fs.ignore(1000, ',');
		fs >> tInt;
		quantity(tInt);
		_err.clear();
		return fs;
	}
	std::ostream& NonPerishable::write(std::ostream& ostr, bool linear)const {
		char t[] = "|   |";
		char t3[] = "| t |";
		char t2[21];
				
		if (!_err.isClear())
			return ostr << _err;
		else {
			if (linear ) {

				strncpy(t2, name(), 20);
				t2[20] = '\0';
				if (taxed()) {
					ostr.setf(std::ios::fixed);
					ostr.precision(2);
					ostr << std::left << std::setw(MAX_SKU_LEN) << sku() << "|" << std::left << std::setw(20) << name() << "|" << std::right << std::setw(7) << price() << t3 << std::setw(4) << std::right << quantity() << "|" << std::setw(9) << std::right << cost()*quantity() << "|";
				}
				else {
					ostr.setf(std::ios::fixed);
					ostr.precision(2);
					ostr << std::left << std::setw(MAX_SKU_LEN) << sku() << "|" << std::left << std::setw(20) << name() << "|" << std::right << std::setw(7) << price() << t << std::setw(4) << std::right << quantity() << "|" << std::setw(9) << std::right << cost()*quantity() << "|";
				}
				return ostr;
			}
			else {
				if (taxed()) {
					ostr << "Sku: " << sku() << std::endl
						<< "Name: " << name() << std::endl						
						<< "Price: " << price() << std::endl
						<< "Price after tax: " << cost() << std::endl
						<< "Quantity: " << quantity() << std::endl
						<< "Total Cost: " << quantity()*cost() << std::endl;
					return ostr;
				}
				else {
					ostr << "Sku: " << sku() << std::endl
						<< "Name: " << name() << std::endl						
						<< "Price: " << price() << std::endl
						<< "Price after tax: " << "N/A" << std::endl
						<< "Quantity: " << quantity() << std::endl
						<< "Total Cost: " << quantity()*cost() << std::endl;
					return ostr;
				}

				
			}
		}
	}
	std::istream& NonPerishable::read(std::istream& istr) {
		double tPrice;
		int tInt;
		char t[1000];
		char t2;
		istr.clear();
		std::cout << "Non-Perishable Item Entry: " << std::endl;
		std::cout << "Sku: ";
		istr.getline(t, 1000);
		sku(t);
		std::cout << "Name: " << std::endl;;
		istr.getline(t, 1000);
		name(t);
		std::cout << "Price: ";
		istr >> tPrice;
		istr.ignore(1000, '\n');
		if (istr.fail()) {
			_err.message("Invalid Price Entry");
			return istr;
		}
		price(tPrice);
		
		std::cout << "Taxed: ";
		istr.get(t2);
		istr.ignore(1000, '\n');
		if ('Y' != toupper(t2) && 'N' != toupper(t2)) {
			_err.message("Invalid Taxed Entry, (y)es or (n)o");
			istr.setstate(std::ios::failbit);
			return istr;
		}
		taxed(true);
		std::cout << "Quantity: ";
		istr >> tInt;
		istr.ignore(1000, '\n');
		if (istr.fail()) {
			_err.message("Invalid Quantity Entry");
			return istr;
		}
		quantity(tInt);
		
		return istr;
	}
}