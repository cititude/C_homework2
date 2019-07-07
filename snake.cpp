#include "snake.h"
#include "ui_snake.h"
#include <QPushButton>
#include <QDebug>
#include <board.h>

Snake::Snake(QWidget *parent,int newid) :
    QWidget(parent),
    ui(new Ui::Snake)
{
    ui->setupUi(this);
    this->setFixedSize(1200,800);
    snakeNode* head=new snakeNode(":/icons/icons/snakenode.JPG");
    board->setvalue(head->xy_pos,id);
    snakeBody.push_front(*head);
    direction=1;
    nnode=1;
    id=newid;
    for(int i=0;i<snakeBody.count();i++)
    {
        snakeBody[i].setParent(this);
    }
}

Snake::~Snake()
{
    delete ui;
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

void Snake::attack()
{

}

Xy_pos Snake::get_next()
{
    int x=snakeBody.front().xy_pos.x;
    int y=snakeBody.front().xy_pos.y;
    switch(direction)
    {
        case 1:
            y-=1;
            break;
        case 2:
            x+=1;
            break;
        case 3:
            y+=1;
            break;
        case 4:
            x-=1;
            break;
    }
    return Xy_pos(x,y);
}
void Snake::move()
{
    if(board->get_impedenceid(get_next())==1)       //food
    {
        lengthen();
        emit board->generate_food();
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
    snakeNode* newhead=new snakeNode(":/icons/icons/snakenode.JPG",next.x,next.y);
    snakeBody.push_front(*newhead);
    snakeBody.front().setParent(this);
    snakeBody.front().show();
    nnode++;
    return;
}



bool Snake::be_dead()
{
    return false;
}
