#include "jetpack.h"

Jetpack::Jetpack(int x, int y) : Myobject(x,y)
{
    w = 50;
    h = 70;
    pic.load(":/res/jetpack.png");
    pic = pic.scaled(w,h,Qt::KeepAspectRatio);
    this->setPixmap(pic);
    object_type = "Jetpack";
}
