#ifndef GAME_H
#define GAME_H
#include "doodler.h"
#include <QGraphicsProxyWidget>

class Game : public QObject
{
    Q_OBJECT
public:
    Game();
    QGraphicsView *view;
    QGraphicsScene *scene;    
public slots:
    void gameOverSlot(int point);
    void newGameSlot();
private:
    Doodler *doo;
    QPushButton *restart_button;
    QGraphicsProxyWidget *proxy;
    QGraphicsTextItem *point_text, *over_text;
    bool first = true;
};

#endif // GAME_H
