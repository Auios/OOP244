#ifndef SICT_POSIO_H_
#define SICT_POSIO_H_
#include <fstream>


namespace sict {
	class PosIO {
	private:
		virtual std::fstream& save(std::fstream& fs)const = 0;
		virtual std::fstream& load(std::fstream& fs) = 0;
		virtual std::ostream& write(std::ostream& os, bool linear)const = 0;
		virtual std::istream& read(std::istream& is) = 0;
	};
}
#endif