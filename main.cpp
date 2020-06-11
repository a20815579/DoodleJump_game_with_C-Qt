#include "mainwindow.h"
#include <QApplication>
#include "doodler.h"
#include "greenplatform.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene *scene = new QGraphicsScene();
    QPixmap background(":/res/background.png");
    scene->setBackgroundBrush(background.scaled(500,800));
    scene->setSceneRect(0,0,500,800);
    QGraphicsView *view = new QGraphicsView(scene);
    view->setFixedSize(500,800);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->show();

    Doodler *doo = new Doodler();
    scene->addItem(doo);
    doo->firstSpawn();

    return a.exec();
}
