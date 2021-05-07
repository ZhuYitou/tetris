#ifndef SQUARE_H
#define SQUARE_H

#include "block.h"


class Square : public Block
{
public:
    Square();

    virtual void setRelativeXY();
};

#endif // SQUARE_H
