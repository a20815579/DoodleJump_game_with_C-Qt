#include "bullet.h"

Bullet::Bullet(int x, int y) : Myobject(x,y)
{
    w = 20;
    h = 20;
    pic.load(":/res/bullet.png");
    pic = pic.scaled(w,h,Qt::KeepAspectRatio);
    this->setPixmap(pic);
    object_type = "Bullet";
    setZValue(1);
}

void Bullet::fly() {
    setY(y()-30);
    if(y() < -20) {
        scene()->removeItem(this);
        delete this;
    }

}
