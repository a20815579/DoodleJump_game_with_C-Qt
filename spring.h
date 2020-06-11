#ifndef SPRING_H
#define SPRING_H
#include "myobject.h"

class Spring : public Myobject
{
    Q_OBJECT
public:
    Spring(int x, int y);
};

#endif // SPRING_H
