#ifndef _SICT_PERISHABLE_H_
#define _SICT_PERISHABLE_H_

#include "Item.h"
#include "ErrorMessage.h"
#include "Date.h"

namespace sict
{
	class Perishable : public Item
	{
	private:
		ErrorMessage _err;
		Date _expiry;

	public:
		//Constructor
		Perishable();

		//Expire
		const Date& expiry()const;
		void expiry(const Date &value);

		//File stuff
		std::fstream& save(std::fstream& fs)const;
		std::fstream& load(std::fstream& fs);
		std::ostream& write(std::ostream& ostr, bool linear)const;
		std::istream& read(std::istream& is);
	};
}
#endif
