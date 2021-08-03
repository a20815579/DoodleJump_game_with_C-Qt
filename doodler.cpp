#include "doodler.h"

Doodler::Doodler()
{
    pic_right.load(":/res/doodler_right.png");
    pic_right = pic_right.scaled(110,80,Qt::KeepAspectRatio);
    pic_left.load(":/res/doodler_left.png");
    pic_left = pic_left.scaled(110,80,Qt::KeepAspectRatio);
    rocket_right.load(":/res/rocket_right.png");
    rocket_right = rocket_right.scaled(110,110,Qt::KeepAspectRatio);
    rocket_left.load(":/res/rocket_left.png");
    rocket_left = rocket_left.scaled(110,110,Qt::KeepAspectRatio);
    shield_right.load(":/res/shield_right.png");
    shield_right = shield_right.scaled(110,110,Qt::KeepAspectRatio);
    shield_left.load(":/res/shield_left.png");
    shield_left = shield_left.scaled(110,110,Qt::KeepAspectRatio);
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
    point_text->setZValue(1);
    time_text = new QGraphicsTextItem();
    time_text->setPlainText(QString("00 : 00"));
    time_text->setFont(QFont("Arial",16));
    time_text->setPos(0,30);
    time_text->setZValue(1);

    pause_icon.addFile(":/res/pause_button.png");
    play_icon.addFile(":/res/play_button.png");
    pause_button = new QPushButton();
    pause_button->setIcon(pause_icon);
    pause_button->setIconSize(QSize(28,28));
    pause_button->setFlat(true);
    pause_button->setGeometry(460,0,40,40);

    pos_vec = {QPointF(0,0),QPointF(0,30),QPointF(460,0)};
    timer2 = new QTimer();
    connect(timer2,SIGNAL(timeout()),this,SLOT(timing()));
    timer2->start(1000);
}

Doodler::~Doodler() {
    delete timer;
    delete timer2;
    delete time_text;
    delete point_text;
    delete pause_button;
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
    if(this->y()-a > 800) {
        disconnect(timer,SIGNAL(timeout()),this,SLOT(addJump()));
        emit gameOverSignal(point);
        return;
    }
    else if(this->y()-a > 350) {
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
    if(is_shild) {
        if(shield_frame == 300) {
            shield_frame = 0;
            is_shild = false;
        }
        else
            shield_frame++;
    }
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
    else if(is_shild)
        this->setPixmap(shield_right);
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
    else if(is_shild)
        this->setPixmap(shield_left);
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
    scene()->addItem(time_text);
    scene()->addWidget(pause_button);
    connect(pause_button,SIGNAL(clicked()),this,SLOT(clickPause()));
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

bool Doodler::collideOtherPlat(QGraphicsItem *ptr) {
    temp_list = ptr->collidingItems();
    for(int i = 0; i < temp_list.length(); i++) {
        if(!pos_vec.contains(temp_list.at(i)->scenePos())) {
            return true;
        }
    }
    return false;
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
    if(collideOtherPlat(ptr)) {
        scene()->removeItem(ptr);
        delete ptr;
        return false;
    }
    else{
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
    int x, y, range;
    bool have_succeed = false;
    if(countPlatform() > platform_num)
        return;
    while(1) {
        if(have_succeed)
            break;
        else {
            x = rand() % 400;
            range = (exceed_dist>30)? exceed_dist : exceed_dist+30;
            y = rand() % range;
            have_succeed = SpawnPlat(x, y);
        }
    }
}

void Doodler::checkCollide() {
    Myobject *ptr;
    temp_list = this->collidingItems();
    for(int i = 0; i < temp_list.length(); i++) {
        if(!pos_vec.contains(temp_list.at(i)->scenePos())) {
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
            else if(ptr->object_type == "BrownPlatform" && jump_frame > 17
               && ptr->y() > last_y+75) {
                delete ptr;
            }
            else if(ptr->object_type == "Jetpack") {
                scene()->removeItem(ptr);
                delete ptr;
                touchJetpack();
                break;
            }
            else if((ptr->object_type == "Monster" || ptr->object_type == "Blackhole")
                    && !is_shild) {
                disconnect(timer,SIGNAL(timeout()),this,SLOT(addJump()));
                emit gameOverSignal(point);
                return;
            }
            else if(ptr->object_type == "Shield") {
                scene()->removeItem(ptr);
                delete ptr;
                touchShield();
            }
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
    jump_frame2 = 0;
    up_state = 2;
    if(this->pixmap() == pic_right)
        this->setPixmap(rocket_right);
    else
        this->setPixmap(rocket_left);
    changePos();
}

void Doodler::touchShield() {
    is_shild = true;
    jump_frame2 = 0;
    if(this->pixmap() == pic_right)
        this->setPixmap(shield_right);
    else
        this->setPixmap(shield_left);
}

void Doodler::createItem() {
    int relative_h = point % 6500;
    int r, r1;
    if(6400 < relative_h && relative_h < 6500 && !create_rocket) {
        create_rocket = true;
        r = rand() % 400 + 20;
        Jetpack *jet = new Jetpack(r,0);
        jet->setZValue(1);
        scene()->addItem(jet);
        connect(this,SIGNAL(tooHigh(int)),jet,SLOT(moveDown(int)));
    }
    if(0 <= relative_h && relative_h < 100)
        create_rocket = false;

    relative_h = point % 5000;
    if(4900 < relative_h && relative_h < 5000 && !create_shield) {
        create_shield = true;
        r = rand() % 420 + 20;
        Protectshield *shield = new Protectshield(r,0);
        shield->setZValue(1);
        scene()->addItem(shield);
        connect(this,SIGNAL(tooHigh(int)),shield,SLOT(moveDown(int)));
    }
    if(0 <= relative_h && relative_h < 100)
        create_shield = false;

    relative_h = point % 300;
    if(270 < relative_h && relative_h < 300 && !create_brown) {
        create_brown = true;
        r = rand() % 400;
        BrownPlatform *brown = new BrownPlatform(r,0);
        scene()->addItem(brown);
        connect(this,SIGNAL(tooHigh(int)),brown,SLOT(moveDown(int)));
    }
    if(0 <= relative_h && relative_h < 30)
        create_brown = false;

    relative_h = point % 3000;
    if(2900 < relative_h && relative_h < 3000 && !create_hazard) {
        create_hazard = true;
        r = rand() % 400;
        r1 = rand() % 4;
        if(!r1) {
            Blackhole *hole = new Blackhole(r,0);
            scene()->addItem(hole);
            connect(this,SIGNAL(tooHigh(int)),hole,SLOT(moveDown(int)));
        }
        else {
            Monster *mon;
            switch(r1){
                case 1:
                    mon = new Monster(r,0,this);
                    break;
                case 2:
                    mon = new Monster2(r,0,this);
                    break;
                case 3:
                    mon = new Monster3(r,0,this);
            }
            scene()->addItem(mon);
            connect(this,SIGNAL(tooHigh(int)),mon,SLOT(moveDown(int)));
            connect(timer,SIGNAL(timeout()),mon,SLOT(repeatMove()));
        }

    }
    if(0 <= relative_h && relative_h < 100)
        create_hazard = false;

}

void Doodler::decidePlatNum() {
    if(3000 < point && point < 3100)
        platform_num = 13;
    else if(6000 < point && point < 6100)
        platform_num = 12;
    else if(9000 < point && point < 9100)
        platform_num = 11;
    else if(12000 < point && point < 12100)
        platform_num = 10;
    else if(15000 < point && point < 15100)
        platform_num = 9;
}

int Doodler::countPlatform() {
    temp_list = scene()->items();
    int count = 0;
    Myobject *my_ptr;
    QGraphicsItem *item_ptr;
    for(int i = 0; i < temp_list.length(); i++) {
        item_ptr = temp_list.at(i);
        if(item_ptr != this && !pos_vec.contains(item_ptr->scenePos())) {
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

void Doodler::clickPause() {
    if(!is_pause) {
        is_pause = true;
        disconnect(timer,SIGNAL(timeout()),this,SLOT(addJump()));
        pause_button->setIcon(play_icon);
        this->clearFocus();
        disconnect(timer2,SIGNAL(timeout()),this,SLOT(timing()));
        temp_list = scene()->items();
        Myobject *my_ptr;
        QGraphicsItem *item_ptr;
        for(int i = 0; i < temp_list.length(); i++) {
            item_ptr = temp_list.at(i);
            if(item_ptr != this && !pos_vec.contains(item_ptr->scenePos())) {
                my_ptr = static_cast<Myobject*>(item_ptr);
                if(my_ptr->object_type == "Monster" || my_ptr->object_type == "Platform")
                    disconnect(timer,SIGNAL(timeout()),my_ptr,SLOT(repeatMove()));
                else if(my_ptr->object_type == "Bullet")
                    disconnect(timer,SIGNAL(timeout()),my_ptr,SLOT(fly()));
            }
        }
    }
    else {
        is_pause = false;
        connect(timer,SIGNAL(timeout()),this,SLOT(addJump()));
        pause_button->setIcon(pause_icon);
        connect(timer2,SIGNAL(timeout()),this,SLOT(timing()));
        Myobject *my_ptr;
        QGraphicsItem *item_ptr;
        for(int i = 0; i < temp_list.length(); i++) {
            item_ptr = temp_list.at(i);
            if(item_ptr != this && !pos_vec.contains(item_ptr->scenePos())) {
                my_ptr = static_cast<Myobject*>(item_ptr);
                if(my_ptr->object_type == "Monster" || my_ptr->object_type == "Platform")
                    connect(timer,SIGNAL(timeout()),my_ptr,SLOT(repeatMove()));
                else if(my_ptr->object_type == "Bullet")
                    connect(timer,SIGNAL(timeout()),my_ptr,SLOT(fly()));
            }
        }
        this->setFocus();        
    }
}

void Doodler::timing()
{
    if(second == 60) {
        second = 0;
        minute++;
    }
    else {
        second++;
    }
    if(second < 10) {
        second_text = QString::number(0) + QString::number(second);
    }
    else {
        second_text = QString::number(second);
    }
    if(minute < 10) {
        minute_text = QString::number(0) + QString::number(minute);
    }
    else {
        minute_text = QString::number(minute);
    }
    time_text->setPlainText(minute_text + QString(" : ") + second_text);
}

