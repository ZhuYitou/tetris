#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "block.h"


class Rectangle : public Block
{
public:
    Rectangle();

    virtual void setRelativeXY();
};

#endif // RECTANGLE_H
