#include "obstacle.h"
#include "ui_obstacle.h"
#include <QPixmap>
#include <QDebug>

#define INFINITY 1000000000
Obstacle::Obstacle(QString path,Xy_pos po,int type)
{
    QPixmap pix;
    imgpath=path;
    pix.load(imgpath);
    bool ret =pix.load(imgpath);
    if(!ret)
    {
        qDebug()<<"fail to load!";
        return ;
    }
    this->setFixedSize(20,20);
    pix.scaled(20,20);
    this->setStyleSheet("QLabel{border:0px;}");
    this->setPixmap(pix);
    pos=po;
    this->move(pos.x*20,pos.y*20);
    switch(type)
    {
        case 1:         // food
            lifetime=INFINITY;
            move_direction=0;
            move_speed=0;
            attack=0;
            break;
        case 2:

            break;
        default:
            break;
    }
}


Obstacle::~Obstacle()
{
    delete ui;
}


void Obstacle::mymove()
{

}

void Obstacle::disaapear()
{

}

Xy_pos Obstacle::get_pos()
{
    return pos;
}


QList<Obstacle> obstacles;
