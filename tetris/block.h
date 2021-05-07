#ifndef BLOCK_H
#define BLOCK_H

#include<vector>
#include<QVector>
#include<QRect>

#include"tetris.h"

using namespace std;

class Block
{
public:
    Block();
    void down();
    void left();
    void right();
    void turnR();
    void turnL();

    QVector<QRect> setBlock();
    virtual void setRelativeXY() = 0;

    friend void Tetris::createBlock();

protected:
    int centerX = 200;
    int centerY = 100;
    int pose = 0;
    vector<int> relativeX;
    vector<int> relativeY;
};

#endif // BLOCK_H
