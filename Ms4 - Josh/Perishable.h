#ifndef PERISHABLE_H_
#define PERISHABLE_H_
#include "Item.h"
#include "ErrorMessage.h"
#include "Date.h"
namespace sict {
	class Perishable : public Item {
	private:
		ErrorMessage _err;
		Date _expiry;
	public:
		Perishable();
		const Date& expiry()const;
		void expiry(const Date &value);
		std::fstream& save(std::fstream& fs)const;
		std::fstream& load(std::fstream& fs);
		std::ostream& write(std::ostream& ostr, bool linear)const;
		std::istream& read(std::istream& is);
	};
}
#endif
