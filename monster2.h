#ifndef MONSTER2_H
#define MONSTER2_H
#include "monster.h"

class Monster2 : public Monster
{
    Q_OBJECT
public:
    Monster2(int x, int y, QGraphicsItem *doodle);
public slots:
    virtual void repeatMove();
private:
    int move_frame = -1;
};

#endif // MONSTER2_H
