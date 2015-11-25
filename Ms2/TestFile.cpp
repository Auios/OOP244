// Final Project Milestone 2
// Tester program
// File	TestFile.cpp
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
#include <iostream>
#include <fstream>
#include <cstring>
#include "TestFile.h"
using namespace std;
namespace sict{

  TestFile::TestFile(const char* fname){
    _text[0] = char(0);
    strcpy(_fname, fname);
  }
  fstream& TestFile::save(std::fstream& file)const{
    file.open(_fname, ios::app|ios::out);
    int i = 0;
    while (_text[i]){
      file << _text[i];
      i++;
    }
    file.close();
    return file;
  }
  fstream& TestFile::load(std::fstream& file){
    file.open(_fname, ios::in);
    int i=0;
    while (!file.fail()){
      _text[i++] = file.get();
    }
    file.clear();
    file.close();
    if(i > 0) i--;
    _text[i] = 0;
    return file;
  }
  ostream& TestFile::write(std::ostream& os, bool linear)const{
    for (int i = 0; _text[i]; i++){
      if (linear && _text[i] == '\n'){
        os << " ";
      }
      else{
        os << _text[i];
      }
    }
    return os;
  }
  istream& TestFile::read(std::istream& is){
    is.getline(_text, 9999, EOF);
    return is;
  }
  void TestFile::print(){
    write(cout, false);
    cout << endl;
  }
  std::ostream& operator<<(std::ostream& os, const TestFile& RO){
    return RO.write(os, true);
  }
  std::istream& operator>>(std::istream& is, TestFile& RO){
    return RO.read(is);
  }
}