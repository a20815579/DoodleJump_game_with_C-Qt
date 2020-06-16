#include "blackhole.h"

Blackhole::Blackhole(int x, int y) : Myobject(x,y)
{
    w = 100;
    h = 100;
    pic.load(":/res/black_hole.png");
    pic = pic.scaled(w,h,Qt::KeepAspectRatio);
    this->setPixmap(pic);
    object_type = "Blackhole";
    setZValue(1);
}
