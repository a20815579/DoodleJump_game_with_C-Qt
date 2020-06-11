#include "spring.h"

Spring::Spring(int x, int y) : Myobject(x,y)
{
    w = 25;
    h = 25;
    pic.load(":/res/spring3.png");
    pic = pic.scaled(w,h,Qt::KeepAspectRatio);
    this->setPixmap(pic);
    object_type = "Spring";
}
