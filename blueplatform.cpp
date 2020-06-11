#include "blueplatform.h"

Blueplatform::Blueplatform(int x, int y) : Greenplatform(x, y)
{
    pic.load(":/res/platform_blue.png");
    pic = pic.scaled(w,h,Qt::KeepAspectRatio);
    this->setPixmap(pic);
}

void Blueplatform::repeatMove() {
    if(direction) {
        if(x()+3+w > 500) {
            direction = 0;
            setX(x()-3);
        }
        else {
            setX(x()+3);
        }
    }
    else {
        if(x()-3 < 0) {
            direction = 1;
            setX(x()+3);
        }
        else {
            setX(x()-3);
        }
    }
}
