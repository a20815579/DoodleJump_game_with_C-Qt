#ifndef GRAYPLATFORM_H
#define GRAYPLATFORM_H
#include "greenplatform.h"

class Grayplatform : public Greenplatform
{
    Q_OBJECT
public:
    Grayplatform(int x, int y);
public slots:
    virtual void repeatMove();
private:
    int direction = 0;
};

#endif // GRAYPLATFORM_H
