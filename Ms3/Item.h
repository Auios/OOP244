#ifndef _SICT_ITEM_H
#define _SICT_ITEM_H

#include "POS.h"
#include "PosIO.h"

namespace sict
{
	class Item
	{
	protected:
		//Local variables
		char _sku[MAX_SKU_LEN-1];
		char* _name;
		double _price;
		bool _taxed;
		int _quantity;

		bool _isEmpty;

	public:
		//Constructors
		Item();
		Item(char sku[MAX_SKU_LEN-1], const char* name[], int quantity = 0, bool taxed = true);
		Item(const Item& src);

		//Destructors
		virtual ~Item();

		//Operators
		Item& operator=(const Item& src);
		bool operator==(const char* cmp);
		int operator+=(const int val);
		int operator-=(const int val);

		//Setters
		void Sku(const char sku[MAX_SKU_LEN - 1]);
		void Name(const char* name[]);
		void Price(const double price);
		void Taxed(const bool taxed);
		void Quantity(const int quantity);

		//Getters
		const char* Sku();
		const char* Name();
		double Price();
		bool Taxed();
		int Quantity();

		double cost();
		bool isEmpty();
	};
}
#endif