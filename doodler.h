#ifndef DOODLER_H
#define DOODLER_H
#include <iostream>
#include <QVector>
#include <QGraphicsScene>
#include <QPixmap>
#include <QLabel>
#include <QWidget>
#include <QString>
#include <QList>
#include <QKeyEvent>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QMessageBox>
#include <iomanip>
#include <QTextStream>
#include <QFile>
#include <QDateTime>
#include <QTimer>
#include <QObject>
#include <cstdlib>
#include <ctime>
#include <string>
#include <QList>
#include <QTest>
#include "blueplatform.h"
#include "grayplatform.h"
#include "spring.h"
#include "jetpack.h"
#include "monster2.h"
#include "monster3.h"
#include "bullet.h"

class Doodler : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Doodler();        
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
    void firstSpawn();    
    std::string object_type = "Doodler";
signals:
    void tooHigh(int down_dist);
public slots:
    void addJump();
    void newPlatform(int exceed_dist);
private:
    bool SpawnPlat(int x, int y);
    int countPlatform();
    void moveRight();
    void moveLeft();
    void changePos();
    void checkCollide();
    void stepPlatform();
    void stepSpring();
    void touchJetpack();
    void createItem();
    void decidePlatNum();    
    void shootBullet();
    int jump_frame = 0, jump_frame2 = 0,point = 0, up_state = 0;
    int last_y = 720, platform_num = 12;
    bool right = false, left = false;
    bool create_rocket = false, create_monster = false;
    QPixmap pic_right, pic_left, rocket_right, rocket_left, pic_shoot;
    QList<QGraphicsItem*> temp_list;
    QTimer *timer;
    QGraphicsTextItem *point_text;
};

#endif // DOODLER_H
