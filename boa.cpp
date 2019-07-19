#include "boa.h"
#include "ui_boa.h"
#include <QKeyEvent>
#include <QDebug>
Boa::Boa(QString img) :
    Snake(nullptr,img)
{
    id=1;
}

Boa::~Boa()
{
    delete ui;
}

void Boa::keyPressEvent(QKeyEvent* ev)
{
    switch(ev->key())
    {
    case Qt::Key_W:
        turnup();
        break;
    case Qt::Key_D:
        turnright();
        break;
    case Qt::Key_S:
        turndown();
        break;
    case Qt::Key_A:
        turnleft();
        break;
    }
}

void Boa::automove()
{
    double p=rand()%100/100.0;
    if(board->get_impedenceid(get_next())>=2||p>0.8||board->get_impedenceid(get_next(2))>=2||board->get_snakeid(get_next())>id||board->get_snakeid(get_next(2))>id)
    {
        qDebug()<<"danger";
        int dir=1;
        Xy_pos headpos=snakeBody.front().xy_pos;
        Xy_pos up=Xy_pos(headpos.x,headpos.y-1);
        Xy_pos down=Xy_pos(headpos.x,headpos.y+1);
        Xy_pos right=Xy_pos(headpos.x+1,headpos.y);
        Xy_pos left=Xy_pos(headpos.x-1,headpos.y);
        int a1=1,a2=1,a3=1,a4=1;
        if(board->get_impedenceid(up)>=2||board->get_snakeid(up)>id||direction==3||up.y<0)a1=0;
        if(board->get_impedenceid(right)>=2||board->get_snakeid(right)>id||direction==4||right.x>board->width)a2=0;
        if(board->get_impedenceid(down)>=2||board->get_snakeid(down)>id||direction==1||down.y>board->height)a3=0;
        if(board->get_impedenceid(left)>=2||board->get_snakeid(left)>id||direction==2||left.x<0)a4=0;
        int sum=a1+a2+a3+a4;
        double randf=rand()%50/49.0;
        if(randf<a1/(double)sum)dir=1;
        if(randf>a1/(double)sum&&randf<(a1+a2)/(double)sum)dir=2;
        if(randf>(a1+a2)/(double)sum&&randf<(a1+a2+a3)/(double)sum)dir=3;
        if(randf>(a1+a2+a3)/(double)sum)dir=4;
        qDebug()<<dir;
        switch(dir)
        {
        case 1:
            turnup();
            break;
        case 2:
            turnright();
            break;
        case 3:
            turndown();
            break;
        case 4:
            turnleft();
            break;
        }
    }
}
