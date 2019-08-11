#include "snake.h"
#include "ui_snake.h"
#include <QPushButton>
#include <QDebug>
#include <board.h>
#include <cstdlib>
Snake::Snake(QWidget *parent,QString img) :
    QWidget(parent)
{
    this->setFixedSize(1200,800);
    Xy_pos head_pos;
    do
    {
        head_pos.x=rand()%50+5;
        head_pos.y=rand()%30+5;
        Xy_pos nextpos={head_pos.x,head_pos.y-1};
        if(board->get_impedenceid(head_pos)==0&&board->get_snakeid(head_pos)==0&&board->get_impedenceid(nextpos)==0&&board->get_snakeid(nextpos)==0)break;
    }while(true);
    snakeNode* head=new snakeNode(img,head_pos.x,head_pos.y);
    board->setvalue(head->xy_pos,id);
    snakeBody.push_front(*head);
    direction=1;
    nnode=1;
    id=1;
    hp=10;
    imgpath=img;
    score=0;
    directionChanged=false;
    for(int i=0;i<snakeBody.count();i++)
    {
        snakeBody[i].setParent(this);
    }
    connect(board,&Board::kill,this,[=](int iid){
        if(iid==id)
        {
            //bump in bricks
            hp-=200;
        }
    });

}

Snake::~Snake()
{

}

void Snake::turnleft()
{
    if(directionChanged)return;
    if(direction==2)return;
    direction=4;
    directionChanged=true;
}

void Snake::turnright()
{
    if(directionChanged)return;
    if(direction==4)return;
    direction=2;
    directionChanged=true;
}
void Snake::turnup()
{
    if(directionChanged)return;
    if(direction==3)return;
    direction=1;
    directionChanged=true;
}
void Snake::turndown()
{
    if(directionChanged)return;
    if(direction==1)return;
    direction=3;
    directionChanged=true;
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
    hurtcheck();
    if(hp<=0)return;
    if(board->get_impedenceid(get_next())==1)       //find food
    {
        lengthen();
        score++;
        board->generate_food();
        return;
    }
    lengthen();
    snakeBody.back().setVisible(false);
    board->setvalue(snakeBody.back().xy_pos,0);
    if(!snakeBody.isEmpty())snakeBody.pop_back();
    nnode--;
    directionChanged=false;
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


void Snake::hurtcheck()
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
