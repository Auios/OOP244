#include <iostream>
#include <cstring>
#include "Item.h"

using namespace std;

namespace sict
{

	//Constructors

	Item::Item()
	{
		_sku[0] = 0;
		_name = 0;
		_price = 0.00;
		_taxed = false;
		_quantity = 0;

		_isEmpty = true;
	}

	Item::Item(const char* sku, const char* name, double price, bool taxed)
	{
		_name = new char[strlen(name) + 1];

		strncpy(_sku, sku, MAX_SKU_LEN); _sku[sizeof(_sku) - 1] = '\0';
		strcpy(_name, name);

		_quantity = 0;
		_price = price;
		_taxed = taxed;

		_isEmpty = false;
	}

	Item::Item(const Item& src)
	{
		_price = src._price;
		_taxed = src._taxed;
		_quantity = src._quantity;

		for (int i = 0; i < MAX_SKU_LEN; i++)
		{
			_sku[i] = src._sku[i];
		}

		if (src._name != 0) {
			_name = new char[strlen(src._name) + 1];
			strcpy(_name, src._name);
		}
		else
		{
			_name = 0;
		}

		_isEmpty = false;
	}

	//Destructors

	Item::~Item()
	{
		delete[] _name;
	}

	//Operators

	Item& Item::operator=(const Item& src)
	{
		_price = src._price;
		_taxed = src._taxed;
		_quantity = src._quantity;

		for (int i = 0; i < MAX_SKU_LEN; i++)
		{
			_sku[i] = src._sku[i];
		}
		delete[] _name;
		if (src._name != 0)
		{
			_name = new char[strlen(src._name) + 1];
			strcpy(_name, src._name);
		}
		else
		{
			_name = 0;
		}

		return *this;

		_isEmpty = false;
	}

	bool Item::operator==(const char* cmp)
	{
		return !strcmp(sku(), cmp);
	}

	int Item::operator-=(const int val)
	{
		return _quantity -= val;
	}

	int Item::operator+=(const int val)
	{
		return _quantity += val;
	}

	//Setters

	void Item::sku(const char sku[MAX_SKU_LEN + 1])
	{
		strcpy(_sku, sku);
	}

	void Item::name(const char* nme)
	{
		_name = new char[strlen(nme) + 1];
		strcpy(_name, nme);
	}

	void Item::price(const double price)
	{
		_price = price;
	}

	void Item::taxed(const bool taxed)
	{
		_taxed = taxed;
	}

	void Item::quantity(const int quantity)
	{
		_quantity = quantity;
	}

	//Getters

	const char* Item::sku()const
	{
		return _sku;
	}

	const char* Item::name()const
	{
		return _name;
	}

	double Item::price()const
	{
		return _price;
	}

	bool Item::taxed()const
	{
		return _taxed;
	}

	int Item::quantity()const
	{
		return _quantity;
	}

	double Item::cost()const
	{
		if (_taxed)
		{
			return _price*(1 + TAX);
		}
		return _price;
	}

	bool Item::isEmpty()const
	{
		return _isEmpty;
	}

	////////////////////////
	//Non-Member functions//
	////////////////////////


	//Operators

	double operator+=(double& A, const Item& B)
	{
		return A = (B.price()*B.quantity() + A);
	}

	ostream& operator<<(ostream& os, const Item& A)
	{
		if (!A.isEmpty())
		{
			return A.write(os, true);
		}
		return os;
	}
	istream& operator>>(istream& is, Item& A)
	{
		return A.read(is);

	}

	//RW

	std::ostream& Item::write(std::ostream& os, bool linear)const
	{
		if (!isEmpty())
		{
			return os << _sku << _name << _quantity << _price << _taxed;
		}
		else
		{
			return os;
		}
	}
	std::istream& Item::read(std::istream& is)
	{
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
}