#include "monster.h"

Monster::Monster(int x, int y, QGraphicsItem *doodle) : Myobject(x,y)
{
    w = 100;
    h = 70;
    pic.load(":/res/monster.png");
    pic = pic.scaled(w,h,Qt::KeepAspectRatio);
    this->setPixmap(pic);
    object_type = "Hazard";
    pos_vec = {QPointF(0,0),QPointF(0,30),QPointF(460,0)};
    doo = doodle;
    setZValue(1);
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(checkDied()));
    timer->start(25);
}

Monster::~Monster() {
    delete timer;
}

void Monster::checkDied() {    
    Myobject *my_ptr;
    QGraphicsItem *item_ptr;
    QList<QGraphicsItem*> temp_list = this->collidingItems();
    QPointF item_point,doo_pos = doo->scenePos();
    for(int i = 0; i < temp_list.length(); i++) {
        item_ptr = temp_list.at(i);
        item_point = item_ptr->scenePos();
        if(!pos_vec.contains(item_point) && item_point != doo_pos) {
            my_ptr = static_cast<Myobject*>(item_ptr);
            if(my_ptr->object_type == "Bullet") {
                scene()->removeItem(this);
                delete this;
            }
        }
    }
}

void Monster::repeatMove() {}
