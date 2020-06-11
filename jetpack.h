#ifndef JETPACK_H
#define JETPACK_H
#include "myobject.h"

class Jetpack: public Myobject
{
    Q_OBJECT
public:
    Jetpack(int x, int y);
};

#endif // JETPACK_H
