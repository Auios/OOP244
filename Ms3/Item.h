#ifndef _SICT_ITEM_H
#define _SICT_ITEM_H

#include "POS.h"
#include "PosIO.h"

namespace sict
{
	class Item : public PosIO
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
		Item(const char* sku, const char* name, double price, bool taxed = true);
		Item(const Item& src);

		//Destructors
		virtual ~Item();

		//Operators
		Item& operator=(const Item& src);
		bool operator==(const char* cmp);
		int operator+=(const int val);
		int operator-=(const int val);

		//Setters
		void sku(const char sku[MAX_SKU_LEN + 1]);
		void name(const char* name);
		void price(const double price);
		void taxed(const bool taxed);
		void quantity(const int quantity);

		//Getters
		const char* sku()const;
		const char* name()const;
		double price()const;
		bool taxed()const;
		int quantity()const;

		double cost()const;

		//Flags
		bool isEmpty()const;

		//RW
		std::ostream& write(std::ostream& os, bool linear)const;
		std::istream& read(std::istream& is);
	};

	double operator+=(double& A, const Item& B);
	std::ostream& operator<<(std::ostream&, const Item&);
	std::istream& operator>>(std::istream&, Item&);
}
#endif