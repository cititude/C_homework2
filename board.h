#pragma once
#ifndef BOARD_H
#define BOARD_H
#include <QObject>

using namespace std;
const int Width=600;
const int Height=400;
struct Xy_pos
{
    int x;
    int y;
    Xy_pos(int xx=0,int yy=0):x(xx),y(yy){}
    bool operator== (Xy_pos& other)
    {
        if(x==other.x&&y==other.y)return true;
        return false;
    }
    bool on_boarder()
    {
        if(x<0||x>=Width)return true;
        if(y<0||y>=Height)return true;
        return false;
    }
};
// 棋盘，为600*400方格纸
class Board:public QObject
{
    Q_OBJECT
public:
    Board(int w=Width,int h=Height);
    int get_snakeid(Xy_pos pos);
    int get_impedenceid(Xy_pos pos);
    void setvalue(Xy_pos pos,int value);
    int width,height;
    int round=0;            //当前回合数
private:
    int status[65][45];  // 此数组表示棋盘上各个点的状态，使用二进制编码，后2位表示是否属于某个snake，
                           // 3,4位表示是否存在某个障碍物
public slots:
    void generate_food();
    void generate_bricks();
signals:
    void kill(int iid);    // kill snake with id number "iid"
};

#endif // BOARD_H

extern Board* board;    //使用外部变量，作为所有文件共享全局变量
