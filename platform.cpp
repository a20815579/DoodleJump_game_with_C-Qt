#include "platform.h"

Platform::Platform(int x, int y) : Myobject(x, y)
{

}

void Platform::moveDown(int down_dist) {
    if(y()+down_dist > 800 - h) {
        emit beRemove();
        scene()->removeItem(this);
        delete this;
    }
    else{
        setY(y()+down_dist);
    }
}
