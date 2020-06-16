#ifndef MONSTER_H
#define MONSTER_H
#include "myobject.h"
#include <QVector>

class Monster : public Myobject
{
    Q_OBJECT
public:
    Monster(int x, int y, QGraphicsItem *doodle);
    ~Monster();
    QGraphicsItem *doo;
    QTimer *timer;
    QVector<QPointF> pos_vec;
public slots:
    void checkDied();
    virtual void repeatMove();
};

#endif // MONSTER_H
