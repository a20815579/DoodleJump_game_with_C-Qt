#ifndef MYOBJECT_H
#define MYOBJECT_H
#include <iostream>
#include <QVector>
#include <QPixmap>
#include <QList>
#include <QKeyEvent>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QObject>
#include <QPointF>
#include <string>

class Myobject : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Myobject(int x, int y);
    int w, h;
    std::string object_type;    
    QPixmap pic;
public slots:
    void moveDown(int down_dist);
};

#endif // MYOBJECT_H
