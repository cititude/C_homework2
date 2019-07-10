#include "snake.h"
#include "ui_snake.h"
#include <QPushButton>
#include <QDebug>
#include <board.h>

Snake::Snake(QWidget *parent,QString img,int newid) :
    QWidget(parent),
    ui(new Ui::Snake)
{
//    srand((unsigned) time(NULL));
    ui->setupUi(this);
    this->setFixedSize(1200,800);
    snakeNode* head=new snakeNode(img,rand()%50+2,rand()%33+2);
    board->setvalue(head->xy_pos,id);
    snakeBody.push_front(*head);
    direction=1;
    speed=1;
    nnode=1;
    id=1;               // 仅供测试
    hp=10;
    isAI=false;
    imgpath=img;
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
        if(board->get_impedenceid(get_next())==1)       //find food
        {
            lengthen();
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
    lifecheck();
    if(hp<=0)return true;
    return false;
}

void Snake::hurt(int v)
{
    hp-=v;
}
