#ifndef BLACKHOLE_H
#define BLACKHOLE_H
#include "myobject.h"

class Blackhole : public Myobject
{
    Q_OBJECT
public:
    Blackhole(int x, int y);
};

#endif // BLACKHOLE_H
