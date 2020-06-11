#ifndef BULLET_H
#define BULLET_H
#include "myobject.h"

class Bullet : public Myobject
{
    Q_OBJECT
public:
    Bullet(int x, int y);
public slots:
    void fly();
};

#endif // BULLET_H
