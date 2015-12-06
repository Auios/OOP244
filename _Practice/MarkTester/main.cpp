#include "mark.h"

using namespace sict;

int main()
{
    //Cannot do Mark M2(M1);
    //Cannot do M1 = M2;
    Mark A("Test 1", 30);
    Mark B("Test 2",40,50);
    Mark C = B;
    A.dspName();
    cout << " ";
    A.dspMark();
    cout << endl;
    
    return 0;
}
