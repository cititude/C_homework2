﻿#include "watersnake.h"
#include "ui_watersnake.h"
#include <QKeyEvent>
#include <QDebug>
WaterSnake::WaterSnake(QString img) :
    Snake (nullptr,img)
{
    id=2;
    nbullet=10;
}

WaterSnake::~WaterSnake()
{
    delete ui;
}

void WaterSnake::keyPressEvent(QKeyEvent* ev)
{
    switch(ev->key())
    {
    case Qt::Key_Up:
        turnup();
        break;
    case Qt::Key_Right:
        turnright();
        break;
    case Qt::Key_Down:
        turndown();
        break;
    case Qt::Key_Left:
        turnleft();
        break;
    case Qt::Key_Space:
        emit attack();
        break;
    }
}

bool WaterSnake::try_attack()
{
    if(nbullet<=0)return false;
    nbullet--;
    return true;
}
