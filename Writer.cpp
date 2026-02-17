#include <mutex>
//#include <winsock.h>
#include "Writer.h"
#include <iostream>


using namespace std;
extern mutex mtx;

Writer:: Writer(uint16_t* regs, uint16_t sz) : regPt(regs), rgSz(sz)
{
    counter.val = 0;
    for (int pos = 2; pos < rgSz; ++pos)
        regPt[pos] = pos;
}
void Writer::Refresh()
{
    lock_guard<mutex>lock(mtx);
    {
       ++counter.val;
        regPt[0] = counter.word[0];
        regPt[1] = counter.word[1];
        for (int pos = 2; pos < rgSz; ++pos)
            regPt[pos] = ++regPt[pos];

    }
}
