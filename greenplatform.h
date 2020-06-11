#ifndef GPLATFORM_H
#define GPLATFORM_H
#include "myobject.h"

class Greenplatform : public Myobject
{
    Q_OBJECT
public:
    Greenplatform(int x, int y);
signals:
    void beRemove(int exceed_dist);
public slots:
    void moveDown(int);
    virtual void repeatMove();
private:

};

#endif // GPLATFORM_H
