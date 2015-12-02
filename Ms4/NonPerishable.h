#ifndef _SICT_NonPerishable_H
#define _SICT_NonPerishable_H

#include "Item.h"
#include "ErrorMessage.h"

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

	std::ostream& operator<<(std::ostream&, const NonPerishable&);
	std::istream& operator>>(std::istream&, NonPerishable&);
}
#endif