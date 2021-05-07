#include "tetris.h"
#include "ui_tetris.h"
#include "square.h"
#include "rectangle.h"
#include "zshape.h"
#include "lshape.h"
#include "tshape.h"

#include <Qpainter>
#include <QTimer>
#include <QKeyEvent>


Tetris::Tetris(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Tetris),
    blsRun(false)
{
    ui->setupUi(this);
    this->setGeometry(QRect(10,30,550,1000));
}

Tetris::~Tetris()
{
    delete ui;
    delete block;
}

void Tetris::paintEvent(QPaintEvent *event){
    QPainter painter(this);

//内墙
painter.setPen(Qt::black);
painter.setBrush(Qt::black);
painter.drawRect(80,150,400,800);

//画格子
painter.setPen(Qt::blue);
for(int i=1;i<=40;i++){
    painter.drawLine(80,150+i*20,480,150+i*20);//画横线
}
for(int i=1;i<=20;i++){
    painter.drawLine(80+i*20,150,80+i*20,950);//画竖线
}

painter.setPen(Qt::red);
painter.drawLine(80,150+5*20,480,150+5*20);//生死线

if(!blsRun){
InitTetris();
} else {
block->setRelativeXY();
vBlock = block->setBlock();
}

if(isCrashWell()){
    vBlock = vBlockOld;
   for(int i=0;i<vBlock.size();i++){
       vBlock[i]=QRect(vBlock[i].left(),vBlock[i].top()+20,20,20);
   }
}

if(isUnderHit()){
    for(int i=0;i<vBlockOld.size();i++){
        alreadyHave[(vBlockOld[i].left()-80)/20][(vBlockOld[i].top()-150)/20]=true;
    }

    delete block;

    createBlock();
    block->setRelativeXY();
    vBlock = block->setBlock();
    vBlockOld = vBlock;

    painter.setPen(Qt::blue);
    painter.setBrush(Qt::red);
    painter.drawRects(&vBlock[0],vBlock.size());
}
else if(isBesideHit()){
    vBlock = vBlockOld;
   for(int i=0;i<vBlock.size();i++){
       vBlock[i]=QRect(vBlock[i].left(),vBlock[i].top()+20,20,20);
   }

   painter.setPen(Qt::blue);
   painter.setBrush(Qt::red);
   painter.drawRects(&vBlock[0],vBlock.size());

   vBlockOld = vBlock;
}
else{
painter.setPen(Qt::blue);
painter.setBrush(Qt::red);
painter.drawRects(&vBlock[0],vBlock.size());

vBlockOld = vBlock;
}

disappear();

for(int i=0;i<20;i++){
    for(int j=0;j<40;j++){
        if(alreadyHave[i][j]){
            painter.setPen(Qt::blue);
            painter.setBrush(Qt::yellow);
            painter.drawRect(80+i*20,150+j*20,20,20);
        }
    }
}

if (isLose()){
    timer->stop();
    ui->label->setText("游戏结束！");
}

}



void Tetris::InitTetris(){
    blsRun=true;

    createBlock();
    block->setRelativeXY();
    vBlock = block->setBlock();
    vBlockOld = vBlock;


    timer=new QTimer(this);//设定定时器
    timer->start(200);//设定时间200ms
    connect(timer,SIGNAL(timeout()),SLOT(Tetris_update()));



}



void Tetris::Tetris_update(){

    block->down();

    switch (nDirection){
    case 1://up
        block->turnR();
        break;
    case 2://down
        block->turnL();
        break;
    case 3://left
        block->left();
        break;
    case 4://right
        block->right();
        break;
    default:;
    }
    nDirection=0;

    update();//更新

}



void Tetris::keyPressEvent(QKeyEvent *event){
     QKeyEvent *key=(QKeyEvent*) event;
     switch(key->key())
   {
    case Qt::Key_Up:nDirection=1;
      break;
    case Qt::Key_Down:nDirection=2;
      break;
    case Qt::Key_Left:nDirection=3;
      break;
    case Qt::Key_Right:nDirection=4;
      break;
    default:;
   }
}


void Tetris::createBlock(){
    int kind=qrand()%5;

    switch(kind)
  {
    case 0:
        block = new Square;
        break;
    case 1:
        block = new Rectangle;
        break;
    case 2:
        block = new Zshape;
        break;
    case 3:
        block = new Lshape;
        break;
    case 4:
        block = new Tshape;
        break;
    default:;
  }

    block->centerX = ((qrand()%14)+3)*20;
    block->centerY = 90;
    block->pose = qrand()%4;

}

bool Tetris::isUnderHit(){
     for(int i=0;i<vBlock.size();i++){
         if(vBlockOld[i].top()+20>930||alreadyHave[(vBlockOld[i].left()-80)/20][(vBlockOld[i].top()-150+20)/20])
             return true;
     }
     return false;
}

bool Tetris::isBesideHit(){
     for(int i=0;i<vBlock.size();i++){
         if(vBlock[i].top()>930||alreadyHave[(vBlock[i].left()-80)/20][(vBlock[i].top()-150)/20])
             return true;
     }
     return false;
}

bool Tetris::isCrashWell(){
    for(int i=0;i<vBlock.size();i++){
        if(vBlock[i].left()<80||vBlock[i].left()>460)
            return true;
    }
    return false;
}

void Tetris::disappear(){
    bool fullLine[40]={};
    for(int i=0;i<40;i++){
        bool flag=true;
        for(int j=0;j<20&&flag;j++){
            flag=alreadyHave[j][i];
        }
        fullLine[i]=flag;
        if(flag){
            for(int j=0;j<20;j++){
                alreadyHave[j][i]=false;
            }
        }
    }

    for(int i=38;i>=0 && !fullLine[i];i--){
        bool flag=true;
        int downLines=0;
        while(flag&&downLines<39-i){
        for(int j=0;j<20&&flag;j++){
            flag=!alreadyHave[j][i+downLines+1];
        }

        if(flag){
            downLines++;
        }
     }

        if(downLines>0){
        for(int j=0;j<20;j++){
            alreadyHave[j][i+downLines]=alreadyHave[j][i];
            alreadyHave[j][i]=false;
        }
        }
  }
}

bool Tetris::isLose(){
    bool flag=false;
    for(int j=0;j<20&&!flag;j++){
        flag=alreadyHave[j][4];
    }

    return flag;
}
