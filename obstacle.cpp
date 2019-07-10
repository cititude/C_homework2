#include "obstacle.h"
#include "ui_obstacle.h"
#include <QPixmap>
#include <QDebug>

#define INFINITY 1000000000
Obstacle::Obstacle(QString path,Xy_pos po,int ttype,int direction)
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
    pix=pix.scaled(20,20);
    this->setStyleSheet("QLabel{border:0px;}");
    this->setPixmap(pix);
    pos=po;
    type=ttype;
    this->move(pos.x*20,pos.y*20);
    switch(type)
    {
        case 1:         // food
            lifetime=INFINITY;
            move_direction=0;
            move_speed=0;
            attack=0;
            break;
        case 2:         // walls
            lifetime=INFINITY;
            move_direction=0;
            move_speed=0;
            attack=0;
            break;
        case 3:
            lifetime=20;
            move_direction=direction;
            move_speed=2;
            attack=3;
            break;
        default:
            break;
    }
}


Obstacle::Obstacle(const Obstacle& other)
{
    pos=other.pos;
    lifetime=other.lifetime;
    move_direction=other.move_direction;
    move_speed=other.move_speed;
    type=other.type;           // 1:food
    can_pass=other.can_pass;
    attack=other.attack;
    imgpath=other.imgpath;

    QPixmap pix;
    pix.load(imgpath);
    bool ret =pix.load(imgpath);
    if(!ret)
    {
        qDebug()<<"fail to load!";
        return ;
    }
    this->setFixedSize(20,20);
    pix=pix.scaled(20,20);
    this->setStyleSheet("QLabel{border:0px;}");
    this->setPixmap(pix);
    this->move(pos.x*20,pos.y*20);
}

Obstacle::~Obstacle()
{
    delete ui;
}


void Obstacle::mymove()
{
    Xy_pos to_pos=this->pos;
    switch (this->move_direction) {
        case 1:
            to_pos.y-=move_speed;
            break;
        case 2:
            to_pos.x+=move_speed;
            break;
        case 3:
            to_pos.y+=move_speed;
            break;
        case 4:
            to_pos.x-=move_speed;
            break;
    }
    pos.x=to_pos.x;
    pos.y=to_pos.y;
    this->move(to_pos.x*20,to_pos.y*20);
    lifetime--;
    qDebug()<<"lifetime"<<lifetime;
}

bool Obstacle::disappear()
{
    if(lifetime<=0)return true;
    return false;
}

int Obstacle::get_type()
{
    return type;
}

Xy_pos Obstacle::get_pos()
{
    return pos;
}


int Obstacle::get_attack()
{
    return attack;
}
