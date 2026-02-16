#ifndef WRITER_H
#define WRITER_H

#include "GeneralDefs.h"

union iAndSh
{
  uint32_t val;
  uint16_t word[2];
};

class Writer
{
    uint16_t* regPt;
    uint16_t rgSz;
    iAndSh counter;
public:
    Writer(uint16_t* regs, uint16_t sz);
    void Refresh();
    ~Writer(){}
};

#endif // WRITER_H
