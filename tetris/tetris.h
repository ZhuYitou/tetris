#ifndef TETRIS_H
#define TETRIS_H

#include <QMainWindow>
#include<QVector>
#include<QRect>


class Block;

namespace Ui {
class Tetris;
}

class Tetris : public QMainWindow
{
    Q_OBJECT

public:
    explicit Tetris(QWidget *parent = 0);
    ~Tetris();
     void paintEvent(QPaintEvent *event);
     void InitTetris();
     void keyPressEvent(QKeyEvent *event);

     void createBlock();

     bool isUnderHit();
     bool isBesideHit();
     bool isCrashWell();

     void disappear();
     bool isLose();

private slots:
     void Tetris_update();

private:
    Ui::Tetris *ui;

    Block *block = nullptr;
    QVector<QRect> vBlock;
    QVector<QRect> vBlockOld;

    QTimer *timer;//定时器
    int nDirection;//按键方向
    bool blsRun;//是否开始
    bool alreadyHave[50][50]={};//哪里已有块
};

#endif // TETRIS_H
