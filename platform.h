#ifndef PLATFORM_H
#define PLATFORM_H
#include "myobject.h"


class Platform : public Myobject
{
    Q_OBJECT
public:
    Platform(int x, int y);
signals:
    void beRemove();
public slots:
    void moveDown(int);
};

#endif // PLATFORM_H
