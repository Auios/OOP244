#include "Item.h"
#include <cstring>
namespace sict {
	Item::Item() {
		_sku[0] = '\0';
		_name = nullptr;
		_price = 0;
		_quantity = 0;
	}
	Item::Item(const char* thesku, const char* name, double price, bool taxed) {
		strncpy(_sku, thesku, MAX_SKU_LEN);
		_sku[MAX_SKU_LEN] = '\0';
		_name = new char[strlen(name) + 1];
		strcpy(_name, name);
		_quantity = 0;
		_price = price;
		_taxed = taxed;

	}
	Item::Item(const Item& A) {
		_price = A._price;
		_quantity = A._quantity;
		_taxed = A._taxed;
		for (int i = 0; i < MAX_SKU_LEN; i++) {
			_sku[i] = A._sku[i];
		}
		if (A._name != nullptr) {
			_name = new char[strlen(A._name) + 1];
			strcpy(_name, A._name);
		}
		else
			_name = nullptr;
	}
	Item& Item::operator=(const Item& A) {
		_price = A._price;
		_quantity = A._quantity;
		_taxed = A._taxed;
		for (int i = 0; i < MAX_SKU_LEN; i++) {
			_sku[i] = A._sku[i];
		}
		delete[] _name;
		if (A._name != nullptr) {
			_name = new char[strlen(A._name) + 1];
			strcpy(_name, A._name);
		}
		else
			_name = nullptr;
		return *this;
	}
	Item::~Item() {
		delete[] _name;
	}
	void Item::sku(const char sku[MAX_SKU_LEN + 1]) {
		strcpy(_sku, sku);
	}
	void Item::price(const double prce) {
		_price = prce;
	}
	void Item::name(const char* nme) {
		strcpy(_name, nme);
	}
	void Item::taxed(const bool txed) {
		_taxed = txed;
	}
	void Item::quantity(const int quntity) {
		_quantity = quntity;
	}
	const char* Item::sku()const {
		return _sku;
	}
	const char* Item::name() const {
		return _name;
	}
	double Item::price()const {
		return _price;
	}
	bool Item::taxed() const {
		return _taxed;
	}
	int Item::quantity() const {
		return _quantity;
	}
	double Item::cost() const {
		if (taxed())
			return price()*(1 + TAX);
		else
			return price();
	}
	bool Item::isEmpty() const {
		if (sku()[0] == '\0' && price() == 0 && name() == nullptr && quantity() == 0)
			return true;
		return false;
	}
	bool Item::operator==(const char* a) {
		if (strcmp(sku(), a) == 0)
			return true;
		return false;
	}
	int Item::operator+=(int b) {
		quantity(quantity() + b);
		return quantity();
	}
	int Item::operator-=(int c) {
		quantity(quantity() - c);
		return quantity();
	}
	double operator+=(double& a, const Item& B) {
		return a=(B.price()*B.quantity()+ a );
	}
	std::ostream& Item::write(std::ostream& os , bool linear)const {
		if (!isEmpty())
			return os << _sku << _name << _quantity << _price << _taxed;
		else
			return os;
	}
	std::istream& Item::read(std::istream& is) {
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
	std::ostream& operator<<(std::ostream& os, const Item& a) {
		if (!a.isEmpty())
			return a.write(os, true);
		return os;
	}
	std::istream& operator>>(std::istream& is,  Item& a) {
		return a.read(is);

	}
}
