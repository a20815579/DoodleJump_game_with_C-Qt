#include "game.h"

Game::Game()
{
    scene = new QGraphicsScene();
    QPixmap background(":/res/background.png");
    scene->setBackgroundBrush(background.scaled(500,800));
    scene->setSceneRect(0,0,500,800);
    view = new QGraphicsView(scene);
    view->setFixedSize(500,800);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->show();

    doo = new Doodler();
    scene->addItem(doo);
    doo->firstSpawn();
    connect(doo,SIGNAL(gameOverSignal(int)),this,SLOT(gameOverSlot(int)));
}

void Game::gameOverSlot(int point) {
    scene->removeItem(doo);
    delete doo;
    scene->clear();
    if(first) {
        first = false;
        over_text = new QGraphicsTextItem();
        over_text->setPlainText(QString("Game Over"));
        over_text->setFont(QFont("Calibri",40));
        over_text->setPos(100,200);
        QColor color;
        color.setRgb(109,0,0);
        over_text->setDefaultTextColor(color);
        scene->addItem(over_text);
        point_text = new QGraphicsTextItem();
        point_text->setPlainText(QString("Point : ") + QString::number(point));
        point_text->setFont(QFont("Calibri",28));
        point_text->setPos(100,350);
        scene->addItem(point_text);

        QPixmap pic(":/res/restart.png");
        pic = pic.scaled(195,75,Qt::KeepAspectRatio);
        QIcon ButtonIcon(pic);
        restart_button = new QPushButton();
        restart_button->setIcon(ButtonIcon);
        restart_button->setIconSize(pic.rect().size());
        restart_button->setFlat(true);
        restart_button->setGeometry(150,500,195,75);
        proxy = scene->addWidget(restart_button);
        connect(restart_button,SIGNAL(clicked()),this,SLOT(newGameSlot()));
    }
    else {
        point_text->setPlainText(QString("Point : ") + QString::number(point));
        scene->addItem(proxy);
        scene->addItem(over_text);
        scene->addItem(point_text);
        connect(restart_button,SIGNAL(clicked()),this,SLOT(newGameSlot()));
    }
}

void Game::newGameSlot() {
    scene->removeItem(proxy);
    scene->removeItem(over_text);
    scene->removeItem(point_text);
    disconnect(restart_button,SIGNAL(clicked()),this,SLOT(newGameSlot()));
    doo = new Doodler();
    scene->addItem(doo);
    doo->firstSpawn();
    connect(doo,SIGNAL(gameOverSignal(int)),this,SLOT(gameOverSlot(int)));
}
