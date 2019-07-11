#include "snake.h"
#include "ui_snake.h"
#include <QPushButton>
#include <QDebug>
#include <board.h>
#include <cstdlib>
Snake::Snake(QWidget *parent,QString img) :
    QWidget(parent)
{
//    srand((unsigned) time(NULL));
    this->setFixedSize(1200,800);
    snakeNode* head=new snakeNode(img,rand()%50+2,rand()%33+2);
    board->setvalue(head->xy_pos,id);
    snakeBody.push_front(*head);
    direction=1;
    speed=1;
    nnode=1;
    id=1;
    hp=10;
    isAI=false;
    imgpath=img;
    score=0;
    for(int i=0;i<snakeBody.count();i++)
    {
        snakeBody[i].setParent(this);
    }
    connect(board,&Board::hurt,this,[=](int iid){
        if(iid==id)
        {
            qDebug()<<"bricks";
            hp-=200;
        }
    });

}

Snake::~Snake()
{

}

void Snake::turnleft()
{
    if(direction==2)return;
    direction=4;
}

void Snake::turnright()
{
    if(direction==4)return;
    direction=2;
}
void Snake::turnup()
{
    if(direction==3)return;
    direction=1;
}
void Snake::turndown()
{
    if(direction==1)return;
    direction=3;
}

void Snake::keyPressEvent(QKeyEvent* ){qDebug()<<"dd";}
Xy_pos Snake::get_next(int round)
{
    int x=snakeBody.front().xy_pos.x;
    int y=snakeBody.front().xy_pos.y;
    switch(direction)
    {
        case 1:
            y-=round;
            break;
        case 2:
            x+=round;
            break;
        case 3:
            y+=round;
            break;
        case 4:
            x-=round;
            break;
    }
    return Xy_pos(x,y);
}

int Snake::get_id(){return id;}
int Snake::get_direction(){return direction;}
void Snake::move()
{
    lifecheck();
    if(board->get_impedenceid(get_next())==1)       //find food
    {
        lengthen();
        score++;
        board->generate_food();
        //emit board->generate_food();
        return;
    }
    lengthen();
    snakeBody.back().setVisible(false);
    board->setvalue(snakeBody.back().xy_pos,0);
    if(!snakeBody.isEmpty())snakeBody.pop_back();
    nnode--;
}


void Snake::lengthen()
{
    Xy_pos next=get_next();
    board->setvalue(next,id);
    snakeNode* newhead=new snakeNode(imgpath,next.x,next.y);
    snakeBody.push_front(*newhead);
    snakeBody.front().setParent(this);
    snakeBody.front().show();
    nnode++;
    return;
}


void Snake::lifecheck()
{
    // bump in snake
    if(board->get_snakeid(get_next())!=0)
    {
        if(board->get_snakeid(get_next())!=id)
        {
            hp-=200;
            qDebug()<<"eat another snake";
        }
        else if(id!=1)
        {
            hp-=200;
            qDebug()<<"eat itself";
        }
    }

    // out of boarder
    if(get_next().x<0||get_next().x>=board->width||get_next().y<0||get_next().y>=board->height)
    {
        hp-=200;
        qDebug()<<"boarder";
    }

    // bump in brick
    if(board->get_impedenceid(get_next())==2)
    {
        hp-=200;
        qDebug()<<"brick";
    }
}


bool Snake::be_dead()
{
    if(hp<=0)return true;
    return false;
}

void Snake::hurt(int v)
{
    hp-=v;
}

int Snake::get_score()
{
    return score;
}
