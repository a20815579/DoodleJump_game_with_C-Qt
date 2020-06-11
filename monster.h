#ifndef MONSTER_H
#define MONSTER_H
#include "myobject.h"

class Monster : public Myobject
{
    Q_OBJECT
public:
    Monster(int x, int y, QGraphicsItem *doodle);
    QGraphicsItem *doo;
    QTimer *timer;
public slots:
    void checkDied();  
};

#endif // MONSTER_H
