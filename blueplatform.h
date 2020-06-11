#ifndef BPLATFORM_H
#define BPLATFORM_H
#include "greenplatform.h"

class Blueplatform : public Greenplatform
{
    Q_OBJECT
public:
    Blueplatform(int x, int y);
public slots:
    virtual void repeatMove();
private:
    int direction = 0;
};

#endif // BPLATFORM_H
