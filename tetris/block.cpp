#include "block.h"

Block::Block()
{

}

void Block::down(){
    centerY += 20;
}

void Block::left(){
    centerX -= 20;
}

void Block::right(){
    centerX += 20;
}

void Block::turnR(){
    pose = (pose+1)%4;
}

void Block::turnL(){
    pose = (pose+3)%4;
}

QVector<QRect> Block::setBlock(){

    for(int i=0;i<pose;i++){
        for(int i=0;i<relativeX.size();i++){//旋转矩阵
            int temp=relativeX[i];
            relativeX[i]=relativeY[i];
            relativeY[i]=-temp;
        }
    }

    QVector<QRect> vRect;
    vRect.resize(4);

    for(int i=0;i<vRect.size();i++){
        vRect[i]=QRect(80+centerX+10+relativeX[i],centerY+10+relativeY[i],20,20);
    }

    return vRect;
}
