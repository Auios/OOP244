// Final Project Milestone 2
// Tester program
// File	TestFile.h
// Version 1.0
// Date	2015/11/16
// Author	Fardad Soleimanloo
//
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// Fardad             2015/11/16           Preliminary release
/////////////////////////////////////////////////////////////////
#ifndef SICT_TESTFILE_H__
#define SICT_TESTFILE_H__
#include "PosIO.h"
namespace sict
{
	class TestFile : public PosIO
	{
	private:
		char _fname[256];
		char _text[10000];
	public:
		TestFile(const char* fname);
		std::fstream& save(std::fstream& file)const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear)const;
		std::istream& read(std::istream& is);
		void print();
	};
	std::ostream& operator<<(std::ostream& os, const TestFile& RO);
	std::istream& operator>>(std::istream& id, TestFile& RO);
}
#endif