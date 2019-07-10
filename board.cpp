#include "board.h"
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <obstacle.h>
#include <playscene.h>
#include <QDebug>
Board::Board(int w,int h)
{
    width=w;
    height=h;
    memset(status,0,sizeof(status));
}

int Board::get_snakeid(Xy_pos pos)
{
    return status[pos.x][pos.y]&3;
}

int Board::get_impedenceid(Xy_pos pos)
{
    return (status[pos.x][pos.y]&(3<<2))>>2;
}

void Board::setvalue(Xy_pos pos,int value)
{
    status[pos.x][pos.y]=value;
}

void Board::generate_food()
{
    srand(unsigned(time(NULL)));
    Xy_pos newpos;
    int limit=20;
    do
    {
        limit--;
        newpos.x=rand()%width+1;
        newpos.y=rand()%height+1;
    }
    while(!(get_impedenceid(newpos)==0&&get_snakeid(newpos)==0)&&limit>0);
    board->setvalue(newpos,1<<2);
    qDebug()<<"food:"<<newpos.x<<newpos.y;
}

void Board::generate_bricks()
{
    Xy_pos newpos;
    srand(unsigned(time(NULL)));
    if(round==0)
    {
        do
        {
            newpos.x=rand()%width+1;
            newpos.y=rand()%height+1;
        }
        while(!(get_impedenceid(newpos)==0&&get_snakeid(newpos)==0));
        board->setvalue(newpos,2<<2);
        qDebug()<<"bricks:"<<newpos.x<<newpos.y;
    }
    else
    {
        for(int i=0;i<width;i++)
            for(int j=0;j<height;j++)
            {
                if((i-30)*(i-30)+(j-20)*(j-20)>(36-round)*(36-round))
                {                    
                    if(get_snakeid(Xy_pos(i,j))!=0) emit hurt(get_snakeid(Xy_pos(i,j)));
                    board->setvalue(Xy_pos(i,j),2<<2);
                }
            }
    }
}


Board* board=new Board(60,40);
