#ifndef SICT_ITEM_H_
#define SICT_ITEM_H_
#include "PosIO.h"
#include "POS.h"
#include <iostream>

namespace sict {
	class Item : public PosIO {
	private:
		char _sku[MAX_SKU_LEN + 1];
		char* _name;
		double _price;
		bool _taxed;
		int _quantity;
		
	public:
		Item();
		Item(const char* thesku ,const char* name, double price, bool taxed = true);
		Item(const Item& A);
		Item& operator=(const Item& A);
		virtual ~Item();
		void sku(const char sku[MAX_SKU_LEN + 1]);
		void price(const double prce);
		void name(const char* nme);
		void taxed(const bool txed);
		void quantity(const int quntity);
		const char* sku()const;
		const char* name()const;
		double price()const;
		bool taxed()const;
		int quantity()const;
		double cost()const;
		bool isEmpty()const;
		bool operator==(const char*);
		int operator+=(int);
		int operator-=(int);
		std::ostream& write(std::ostream& os, bool linear)const;
		std::istream& read(std::istream& is);
	};
	double operator+=(double& a, const Item& B);
	std::ostream& operator<<(std::ostream&, const Item&);
	std::istream& operator>>(std::istream&,  Item&);
	
}
#endif // !SICT_ITEM_H_
