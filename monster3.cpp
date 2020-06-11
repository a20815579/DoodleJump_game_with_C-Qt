#include "monster3.h"

Monster3::Monster3(int x, int y, QGraphicsItem *doodle) : Monster(x,y,doodle)
{
    w = 60;
    h = 80;
    pic.load(":/res/monster3_right.png");
    pic = pic.scaled(w,h,Qt::KeepAspectRatio);
    pic2.load(":/res/monster3_left.png");
    pic2 = pic2.scaled(w,h,Qt::KeepAspectRatio);
    this->setPixmap(pic2);
}

void Monster3::repeatMove() {
    if(direction) {
        if(x()+3+w > 500) {
            direction = 0;
            setX(x()-5);
            setPixmap(pic2);
        }
        else {
            setX(x()+5);
        }
    }
    else {
        if(x()-3 < 0) {
            direction = 1;
            setX(x()+5);
            setPixmap(pic);
        }
        else {
            setX(x()-5);
        }
    }
}
