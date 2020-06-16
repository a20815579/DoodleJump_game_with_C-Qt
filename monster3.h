#ifndef MONSTER3_H
#define MONSTER3_H
#include "monster.h"

class Monster3 : public Monster
{
    Q_OBJECT
public:
    Monster3(int x, int y, QGraphicsItem *doodle);
public slots:
    virtual void repeatMove();
private:
    int direction = 0;
    QPixmap pic2;
};

#endif // MONSTER3_H
