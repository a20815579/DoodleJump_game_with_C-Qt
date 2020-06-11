#include "grayplatform.h"

Grayplatform::Grayplatform(int x, int y) : Greenplatform(x, y)
{
    pic.load(":/res/platform_gray.png");
    pic = pic.scaled(w,h,Qt::KeepAspectRatio);
    this->setPixmap(pic);
}

void Grayplatform::repeatMove() {
    if(direction) {
        if(y()-3 < 50) {
            direction = 0;
            setY(y()+3);
        }
        else {
            setY(y()-3);
        }
    }
    else {
        if(y()+3+h > 800) {
            direction = 1;
            setY(y()-3);
        }
        else {
            setY(y()+3);
        }
    }
}
