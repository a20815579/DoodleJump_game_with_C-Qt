#include "jetpack.h"

Jetpack::Jetpack(int x, int y) : Myobject(x,y)
{
    w = 30;
    h = 50;
    pic.load(":/res/jetpack.png");
    pic = pic.scaled(w,h,Qt::KeepAspectRatio);
    this->setPixmap(pic);
    object_type = "Jetpack";
}
