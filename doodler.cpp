#include "doodler.h"

Doodler::Doodler()
{
    pic_right.load(":/res/doodler_right3.png");
    pic_right = pic_right.scaled(110,80,Qt::KeepAspectRatio);
    pic_left.load(":/res/doodler_left3.png");
    pic_left = pic_left.scaled(110,80,Qt::KeepAspectRatio);
    rocket_right.load(":/res/rocket_right.png");
    rocket_right = rocket_right.scaled(110,110,Qt::KeepAspectRatio);
    rocket_left.load(":/res/rocket_left.png");
    rocket_left = rocket_left.scaled(110,110,Qt::KeepAspectRatio);
    pic_shoot.load(":/res/doodler_attack.png");
    pic_shoot = pic_shoot.scaled(110,80,Qt::KeepAspectRatio);
    this->setPixmap(pic_right);
    this->setPos(120,640);
    this->setZValue(2);
    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFocus();
    point_text = new QGraphicsTextItem();
    point_text->setPlainText(QString("Point : ") + QString::number(point));
    point_text->setFont(QFont("Arial",16));
}

void Doodler::changePos() {
    last_y = y();
    int a;
    switch(up_state) {
        case 0:
            a = (17-jump_frame)*2;
            a = (a < -34)? -34 : a;
            break;
        case 1:
            a = (25-jump_frame2)*2;
            break;
        case 2:
            if(jump_frame2 <= 40)
                a = 60;
            else
                a = (60-jump_frame2)*3;
    }
    int down_dist;
    if(this->y()-a > 350) {
        this->setY(y()-a);
    }
    else {
        down_dist = 350 - (this->y()-a);
        this->setY(350);
        point += down_dist;
        point_text->setPlainText(QString("Point : ") + QString::number(point));
        emit tooHigh(down_dist);
        createItem();
        decidePlatNum();
    }
    if(right)
        moveRight();
    else if(left)
        moveLeft();
    if(up_state != 2)
        checkCollide();
}

void Doodler::addJump() {
    switch(up_state) {
        case 0:
            jump_frame++;
            break;
        case 1:
            if(jump_frame2 == 25) {
                jump_frame2 = 0;
                up_state = 0;
            }
            else
               jump_frame2++;
            break;
        case 2:
            if(jump_frame2 == 60) {
                jump_frame2 = 0;
                up_state = 0;
                if(this->pixmap() == rocket_right)
                    this->setPixmap(pic_right);
                else
                    this->setPixmap(pic_left);
            }
            else
               jump_frame2++;
    }
    changePos();
}

void Doodler::moveRight() {
    if(up_state == 2)
        this->setPixmap(rocket_right);
    else
        this->setPixmap(pic_right);
    if(x()+3 < 420) {
        this->setX(x()+10);
    }
    else {
        this->setX(0);
    }
}

void Doodler::moveLeft() {
    if(up_state == 2)
        this->setPixmap(rocket_left);
    else
        this->setPixmap(pic_left);
    if(x()-3 > 0) {
        this->setX(x()-10);
    }
    else {
        this->setX(420);
    }
}

void Doodler::keyPressEvent(QKeyEvent *e)
{
    switch(e->key()) {
        case Qt::Key_Right :
            this->right = true;
            break;

        case Qt::Key_Left :
            this->left = true;
            break;
        case Qt::Key_Space :
            shootBullet();
    }
}

void Doodler::keyReleaseEvent (QKeyEvent *e)
{
    switch(e->key()) {
        case Qt::Key_Right :
            this->right = false;
            break;

        case Qt::Key_Left :
            this->left = false;
            break;
    }
}

void Doodler::firstSpawn() {
    scene()->addItem(point_text);
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(addJump()));
    timer->start(30);
    srand(time(NULL));
    int x, y;
    for(int i = 0; i < 12; i++) {
        x = rand() % 400;
        y = rand() % 350 + 50;
        y = (i < 6)? y : y+350;
        if(!SpawnPlat(x, y))
            i--;
    }
}

bool Doodler::SpawnPlat(int x, int y) {
    int r = rand() % 12;
    int r1, r2;
    Greenplatform *ptr;
    if(r == 0) {
        ptr = new Blueplatform(x,y);
    }
    else if(r == 1 || r == 2) {
        ptr = new Grayplatform(x,y);
    }
    else {
        ptr = new Greenplatform(x,y);
    }
    scene()->addItem(ptr);
    temp_list = ptr->collidingItems();
    if(temp_list.length() != 0) {
        //qDebug() << "fail";
        scene()->removeItem(ptr);
        delete ptr;
        return false;
    }
    else{
        //qDebug() << "secuess";
        if(r > 2) {
            r1 = rand() % 20;
            if(r1 == 0) {
                r2 = rand() % 65 + 5;
                Spring *sp = new Spring(x+r2,y-20);
                scene()->addItem(sp);
                connect(this,SIGNAL(tooHigh(int)),sp,SLOT(moveDown(int)));
            }
        }
        connect(this,SIGNAL(tooHigh(int)),ptr,SLOT(moveDown(int)));
        connect(ptr,SIGNAL(beRemove(int)),this,SLOT(newPlatform(int)));
        connect(timer,SIGNAL(timeout()),ptr,SLOT(repeatMove()));
        return true;
    }
}

void Doodler::newPlatform(int exceed_dist) {
    int x, y, fail_time = 0;
    bool have_succeed = false;
    if(countPlatform() > platform_num)
        return;
    while(1) {
        if(have_succeed)
            break;
        else {
            fail_time++;
            x = rand() % 400;
            y = rand() % (exceed_dist+1) + 40;
            if(fail_time > 5) {
                x = rand() % 250 + 150;
                y = rand() % 10;
            }
            have_succeed = SpawnPlat(x, y);
        }
    }
}

void Doodler::checkCollide() {
    Myobject *ptr;
    temp_list = this->collidingItems();
    for(int i = 0; i < temp_list.length(); i++) {
        ptr = static_cast<Myobject*>(temp_list.at(i));
        if(ptr->object_type == "Spring" && jump_frame > 17
                && ptr->y() > last_y+75) {
            stepSpring();
            break;
        }
        else if(ptr->object_type == "Platform" && jump_frame > 17
           && ptr->y() > last_y+75) {
            stepPlatform();
            break;
        }
        else if(ptr->object_type == "Jetpack") {
            scene()->removeItem(ptr);
            delete ptr;
            touchJetpack();
            break;
        }
        else if(ptr->object_type == "Monster") {
            //qDebug() << "died";
            break;
        }
    }
}

void Doodler::stepPlatform() {
    QTest::qSleep(30);
    jump_frame = 0;
    changePos();
}

void Doodler::stepSpring() {
    QTest::qSleep(30);
    jump_frame = 17;
    up_state = 1;
    changePos();
}

void Doodler::touchJetpack(){
    QTest::qSleep(30);
    jump_frame = 17;
    up_state = 2;
    if(this->pixmap() == pic_right)
        this->setPixmap(rocket_right);
    else
        this->setPixmap(rocket_left);
    changePos();
}

void Doodler::createItem() {
    int relative_h = point % 6000;
    int r;
    if(5900 < relative_h && relative_h < 6000 && !create_rocket) {
        create_rocket = true;
        r = rand() % 400 + 20;
        Jetpack *jet = new Jetpack(r,10);
        jet->setZValue(1);
        scene()->addItem(jet);
        connect(this,SIGNAL(tooHigh(int)),jet,SLOT(moveDown(int)));
    }
    if(0 < relative_h && relative_h < 100)
        create_rocket = false;

//    relative_h = point % 4000;
//    if(3900 < relative_h && relative_h < 4000 && !create_monster) {
//        create_monster = true;
//        r = rand() % 400;
//        Monster *mon = new Monster(r,0,this);
//        mon->setZValue(1);
//        scene()->addItem(mon);
//        connect(this,SIGNAL(tooHigh(int)),mon,SLOT(moveDown(int)));
//    }
//    if(0 < relative_h && relative_h < 100)
//        create_monster = false;

    relative_h = point % 1000;
    if(900 < relative_h && relative_h < 1000 && !create_monster) {
        create_monster = true;
        r = rand() % 350;
        Monster2 *mon2 = new Monster2(r,0,this);
        mon2->setZValue(1);
        scene()->addItem(mon2);
        connect(this,SIGNAL(tooHigh(int)),mon2,SLOT(moveDown(int)));
        connect(timer,SIGNAL(timeout()),mon2,SLOT(repeatMove()));
    }
    if(0 < relative_h && relative_h < 100)
        create_monster = false;
}

void Doodler::decidePlatNum() {
    if(3000 < point && point < 3100)
        platform_num = 11;
    else if(6000 < point && point < 6100)
        platform_num = 10;
    else if(9000 < point && point < 9100)
        platform_num = 9;
    else if(12000 < point && point < 12100)
        platform_num = 8;
    else if(15000 < point && point < 15100)
        platform_num = 7;
}

int Doodler::countPlatform() {
    temp_list = scene()->items();
    int count = 0;
    Myobject *my_ptr;
    QGraphicsItem *item_ptr;
    for(int i = 0; i < temp_list.length(); i++) {
        item_ptr = temp_list.at(i);
        if(item_ptr != point_text && item_ptr != this) {
            my_ptr = static_cast<Myobject*>(item_ptr);
            if(my_ptr->object_type == "Platform")
                count++;
        }
    }
    return count;
}

void Doodler::shootBullet() {
    this->setPixmap(pic_shoot);
    Bullet *bullet = new Bullet(x()+45, y()-20);
    scene()->addItem(bullet);
    connect(timer,SIGNAL(timeout()),bullet,SLOT(fly()));
}
