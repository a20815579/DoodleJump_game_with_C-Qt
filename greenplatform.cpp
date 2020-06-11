#include "greenplatform.h"

Greenplatform::Greenplatform(int x, int y) : Myobject(x,y)
{
    w = 100;
    h = 30;
    object_type = "Platform";
    pic.load(":/res/platform_green.png");
    pic = pic.scaled(w,h,Qt::KeepAspectRatio);
    this->setPixmap(pic);
}

void Greenplatform::moveDown(int down_dist) {
    if(y()+down_dist > 800) {
        emit beRemove(down_dist);
        scene()->removeItem(this);
        delete this;
    }
    else{
        setY(y()+down_dist);
    }
}

void Greenplatform::repeatMove() {}
