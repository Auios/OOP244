#include <iostream>
#include <cstring>
#include "Item.h"

using namespace sict;
using namespace std;

//Constructors

Item::Item()
{
	_sku[sizeof(_sku) - 1] = 0;
	_name = 0;
	_price = 0.00;
	_taxed = false;
	_quantity = 0;

	_isEmpty = true;
}

Item::Item(char sku[MAX_SKU_LEN-1], const char* name[], int quantity = 0, bool taxed = true)
{
	strncpy(_sku, sku, sizeof(_sku) - 1); _sku[sizeof(_sku) - 1] = '\0';
	strncpy(_name, *name, sizeof(name) - 1); _name[sizeof(_name) - 1] = '\0';
	_quantity = quantity;
	_taxed = taxed;

	_isEmpty = false;
}

Item::Item(const Item& src)
{
	strncpy(_sku, src._sku, sizeof(_sku) - 1); _sku[sizeof(_sku) - 1] = '\0';
	strncpy(_name, src._name, sizeof(_name) - 1); _sku[sizeof(_name) - 1] = '\0';
	_price = src._price;
	_taxed = src._taxed;
	_quantity = src._quantity;

	_isEmpty = false;
}

//Destructors

Item::~Item()
{
	_sku[sizeof(_sku) - 1] = 0;
	_name = 0;
	_price = 0.00;
	_taxed = false;
	_quantity = 0;

	_isEmpty = true;
}

//Operators

Item& Item::operator=(const Item& src)
{
	strncpy(_sku, src._sku, sizeof(_sku) - 1); _sku[sizeof(_sku) - 1] = '\0';
	strncpy(_name, src._name, sizeof(_name) - 1); _sku[sizeof(_name) - 1] = '\0';
	_price = src._price;
	_taxed = src._taxed;
	_quantity = src._quantity;

	_isEmpty = false;
}

bool Item::operator==(const char* cmp)
{
	return *cmp == *_sku;
}

int Item::operator-=(const int val)
{
	return _quantity += val;
}

int Item::operator+=(const int val)
{
	return _quantity -= val;
}

//Setters

void Item::Sku(const char sku[MAX_SKU_LEN - 1])
{
	strncpy(_sku, sku, sizeof(_sku) - 1); _sku[sizeof(_sku) - 1] = '\0';
}

void Item::Name(const char* name[])
{
	strncpy(_name, *name, sizeof(name) - 1); _name[sizeof(_name) - 1] = '\0';
}

void Item::Price(const double price)
{
	_price = price;
}

void Item::Taxed(const bool taxed)
{
	_taxed = taxed;
}

void Item::Quantity(const int quantity)
{
	_quantity = quantity;
}

//Getters

const char* Item::Sku()
{
	return _sku;
}

const char* Item::Name()
{
	return _name;
}

double Item::Price()
{
	return _price;
}

bool Item::Taxed()
{
	return _taxed;
}

int Item::Quantity()
{
	return _quantity;
}

double Item::cost()
{
	if (_taxed)
	{
		return _price + (_price*TAX);
	}
	return _price;
}

bool Item::isEmpty()
{
	return _isEmpty;
}