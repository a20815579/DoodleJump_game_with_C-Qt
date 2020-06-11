#include "monster.h"

Monster::Monster(int x, int y, QGraphicsItem *doodle) : Myobject(x,y)
{
    w = 100;
    h = 70;
    pic.load(":/res/monster.png");
    pic = pic.scaled(w,h,Qt::KeepAspectRatio);
    this->setPixmap(pic);
    object_type = "Monster";
    doo = doodle;
    setZValue(1);
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(checkDied()));
    timer->start(25);
}

void Monster::checkDied() {    
    Myobject *my_ptr;
    QGraphicsItem *item_ptr;
    QList<QGraphicsItem*> temp_list = this->collidingItems();
    QPointF doo_pos = doo->scenePos();
    for(int i = 0; i < temp_list.length(); i++) {
        item_ptr = temp_list.at(i);
        if(item_ptr->scenePos() != QPointF(0,0) && item_ptr->scenePos() != doo_pos) {
            my_ptr = static_cast<Myobject*>(item_ptr);
            if(my_ptr->object_type == "Bullet") {
                scene()->removeItem(this);
                delete this;
            }
        }
    }
}
