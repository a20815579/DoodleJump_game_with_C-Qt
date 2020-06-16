#include "brownplatform.h"

BrownPlatform::BrownPlatform(int x, int y) : Myobject(x,y)
{
    w = 100;
    h = 30;
    pic.load(":/res/platform_brown.png");
    pic = pic.scaled(w,h,Qt::KeepAspectRatio);
    this->setPixmap(pic);
    object_type = "BrownPlatform";
}
