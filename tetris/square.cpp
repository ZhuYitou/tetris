#include "square.h"

Square::Square()
{

}

void Square::setRelativeXY(){
    relativeX.resize(4);
    relativeY.resize(4);

    relativeX[0]= -10;
    relativeY[0]= -10;
    relativeX[1]= 10;
    relativeY[1]= 10;
    relativeX[2]= 10;
    relativeY[2]= -10;
    relativeX[3]= -10;
    relativeY[3]= 10;
}
