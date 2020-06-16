#include "protectshield.h"

Protectshield::Protectshield(int x, int y) : Myobject(x,y)
{
    w = 50;
    h = 50;
    pic.load(":/res/shield.png");
    pic = pic.scaled(w,h,Qt::KeepAspectRatio);
    this->setPixmap(pic);
    object_type = "Shield";
}
