#ifndef LSHAPE_H
#define LSHAPE_H


#include "block.h"


class Lshape : public Block
{
public:
    Lshape();

    virtual void setRelativeXY();
};

#endif // LSHAPE_H
