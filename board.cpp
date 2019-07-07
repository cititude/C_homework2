#include "board.h"
#include <cstring>
#include <cstdlib>
#include <ctime>

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
    do
    {
        newpos.x=rand()%width+1;
        newpos.y=rand()%height+1;
    }
    while(get_impedenceid(newpos)==0&&get_snakeid(newpos)==0);

}

Board* board=new Board(60,40);
