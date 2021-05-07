#include "zshape.h"

Zshape::Zshape()
{

}

void Zshape::setRelativeXY(){
    relativeX.resize(4);
    relativeY.resize(4);

    relativeX[0]= -30;
    relativeY[0]= -10;
    relativeX[1]= -10;
    relativeY[1]= -10;
    relativeX[2]= -10;
    relativeY[2]= 10;
    relativeX[3]= 10;
    relativeY[3]= 10;
}
