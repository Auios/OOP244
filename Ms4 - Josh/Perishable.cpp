#include "Perishable.h"
#include "Date.h"
#include <iostream>
#include <iomanip>
#include <cstring>

namespace sict {
	Perishable::Perishable() {
		_expiry.dateOnly(true);
	}
	const Date& Perishable::expiry()const {
		return  _expiry;
	}
	void Perishable::expiry(const Date &value) {
		_expiry = value;
	}
	std::fstream& Perishable::save(std::fstream& fs)const {
		fs << "P," << sku() << "," << name() << "," << price() << "," << taxed() << "," << quantity() << "," << _expiry << std::endl;
		return fs;
	}
	std::fstream& Perishable::load(std::fstream& fs) {
		double tPrice;
		int tInt;
		char t[1000];
		char itax;
		Date expiry;
		fs.getline(t, 1000, ',');
		sku(t);
		fs.getline(t, 1000, ',');
		name(t);
		fs >> tPrice;
		price(tPrice);
		fs.ignore(1000, ',');
		fs.get(itax);
		if (itax == '1')
			taxed(true);
		else
			taxed(false);
		fs.ignore(1000, ',');
		fs >> tInt;
		quantity(tInt);
		_expiry = expiry;
		_err.clear();
		return fs;
	}
	std::ostream& Perishable::write(std::ostream& ostr, bool linear)const {
		char t[] = "|  p|";
		char t2[21];
		char t3[] = "| tp|";

		if (!_err.isClear())
			return ostr << _err;
		else {
			if (linear) {
				strncpy(t2, name(), 20);
				t2[20] = '\0';
				if (taxed()) {
					ostr.setf(std::ios::fixed);
					ostr.precision(2);
					ostr << std::left << std::setw(MAX_SKU_LEN) << sku() << "|" << std::left << std::setw(20) << name() << "|" << std::right << std::setprecision(2) << std::setw(7) << price() << t3 << std::setw(4) << std::right << quantity() << "|" << std::setw(9) << std::setprecision(2) << std::right << cost()*quantity() << "|";
				}
				else {
					ostr.setf(std::ios::fixed);
					ostr.precision(2);
					ostr << std::left << std::setw(MAX_SKU_LEN) << sku() << "|" << std::left << std::setw(20) << name() << "|" << std::right << std::setprecision(2) << std::setw(7) << price() << t << std::setw(4) << std::right << quantity() << "|" << std::setw(9) << std::setprecision(2) << std::right << cost()*quantity() << "|";
				}
				return ostr;
			}
			else {
				if (taxed()) {
					ostr<< "Sku: " << sku() << std::endl
						<< "Name: " << name() << std::endl
						<< "Price: " << price() << std::endl
						<< "Price after tax: " << cost() << std::endl
						<< "Quantity: " << quantity() << std::endl
						<< "Total Cost: " << quantity()*cost() << std::endl
						<< "Expiry date: " << _expiry << std::endl;
					return ostr;
				}
				else {
					ostr<< "Sku: " << sku() << std::endl
						<< "Name: " << name() << std::endl
						<< "Price: " << price() << std::endl
						<< "Price after tax: " << "N/A" << std::endl
						<< "Quantity: " << quantity() << std::endl
						<< "Total Cost: " << quantity()*cost() << std::endl
						<< "Expiry date: " << _expiry << std::endl;
					return ostr;
				}


			}
		}
	}
	std::istream& Perishable::read(std::istream& istr) {
		double tPrice;
		int tInt;
		char t[1000], t2;
		std::cout << "Perishable Item Entry: " << std::endl;
		std::cout << "Sku: ";
		istr.getline(t, 1000);
		sku(t);
		std::cout << "Name: " << std::endl;
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
		std::cout << "Expiry date (YYYY/MM/DD) : ";
		istr >> _expiry;
		istr.ignore(1000, '\n');
		if (_expiry.errCode() == CIN_FAILED) {
			_err.message("Invalid Date Entry");
			istr.setstate(std::ios::failbit);
			return istr;
		}
		else if (_expiry.errCode() == YEAR_ERROR) {
			_err.message("Invalid Year in Date Entry");
			istr.setstate(std::ios::failbit);
			return istr;
		}
		else if (_expiry.errCode() == MON_ERROR) {
			_err.message("Invalid Month in Date Entry");
			istr.setstate(std::ios::failbit);
			return istr;
		}
		else if (_expiry.errCode() == DAY_ERROR) {
			_err.message("Invalid Day in Date Entry");
			istr.setstate(std::ios::failbit);
			return istr;
		}
		
		return istr;
	}
}