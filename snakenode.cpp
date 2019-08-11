#include "snakenode.h"
#include <QDebug>
#include <board.h>
snakeNode::snakeNode(QString imgpath,int xx,int yy)
{
    img=imgpath;
    QPixmap pix;
    bool ret=pix.load(img);
    if(!ret)
    {
        qDebug()<<"can not load the image";
        return;
    }
    this->setFixedSize(20,20);
    pix.scaled(20,20);
    this->setStyleSheet("QLabel{border:0px;}");
    this->setPixmap(pix);
    xy_pos.x=xx;
    xy_pos.y=yy;
    this->move(xy_pos.x*20,xy_pos.y*20);
}

snakeNode::snakeNode(const snakeNode& othernode)
{
    img=othernode.img;
    QPixmap pix;
    bool ret=pix.load(img);
    if(!ret)
    {
        qDebug()<<"can not load the image";
        return;
    }
    this->setFixedSize(20,20);
    pix.scaled(20,20);
    this->setStyleSheet("QLabel{border:0px;}");
    this->setPixmap(pix);
    xy_pos=othernode.xy_pos;
    this->move(xy_pos.x*20,xy_pos.y*20);
}
