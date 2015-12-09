#ifndef NONPERISHABLE_H_
#define NONPERISHABLE_H_
#include "Item.h"
#include "ErrorMessage.h"
#include "Date.h"
namespace sict {
	class NonPerishable : public Item {
	private:
		ErrorMessage _err;
	public:
		std::fstream& save(std::fstream& fs)const;
		std::fstream& load(std::fstream& fs);
		std::ostream& write(std::ostream& ostr, bool linear)const;
		std::istream& read(std::istream& is);
	};
}
#endif