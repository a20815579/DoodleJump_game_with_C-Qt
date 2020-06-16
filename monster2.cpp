#include "monster2.h"

Monster2::Monster2(int x, int y, QGraphicsItem *doodle) : Monster(x,y,doodle)
{
    w = 80;
    h = 60;
    pic.load(":/res/monster2.png");
    pic = pic.scaled(w,h,Qt::KeepAspectRatio);
    this->setPixmap(pic);
}

void Monster2::repeatMove() {
    if(move_frame == 13)
        move_frame = 0;
    else
        move_frame++;
    if(move_frame < 7)
        setX(x()+6);
    else
        setX(x()-6);
}
