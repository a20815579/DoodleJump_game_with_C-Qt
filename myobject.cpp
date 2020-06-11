#include "myobject.h"

Myobject::Myobject(int x, int y)
{
    this->setPos(x,y);
}

void Myobject::moveDown(int down_dist) {
    if(y()+down_dist > 800) {
        scene()->removeItem(this);
        delete this;
    }
    else{
        setY(y()+down_dist);
    }
}
