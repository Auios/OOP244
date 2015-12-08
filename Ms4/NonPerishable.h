#ifndef _SICT_NonPerishable_H_
#define _SICT_NonPerishable_H_

#include "Item.h"
#include "ErrorMessage.h"
#include "Date.h"

namespace sict
{
	class NonPerishable : public Item
	{
	private:
		ErrorMessage _err;

	public:
		std::fstream& save(std::fstream& file)const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear)const;
		std::istream& read(std::istream& is);
	};
}
#endif