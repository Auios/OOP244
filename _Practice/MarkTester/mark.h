//Header
#ifndef SICT_MARK_H__
#define SICT_MARK_H__
#include <iostream>
using namespace std;
namespace sict
{
    class Mark
    {
        char* _name;
        int _value;
        int _outOf;
        void allocate(int size);
        void deallocate();
    public:
        Mark();
        Mark(const char* name, int value, int outOf = 100);
        //Mark(const Mark& CM) = delete; //To prevent copying
        Mark(const Mark& CM);
        //Mark& operator=(const Mark& CM) = delete; //To prevent assigning to another
        Mark& operator=(const Mark& RO);
        void setValue(int value);
        void setOutOf(int outOf);
        void setName(const char* name);
        const Mark& dspMark()const;
        const Mark& dspName()const;
        ~Mark();
        
        const Mark& nl()const;
        const Mark& sp()const;
    };
}
#endif
