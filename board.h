#ifndef BOARD_H
#define BOARD_H
#include <QObject>

struct Xy_pos
{
    int x;
    int y;
    Xy_pos(int xx=0,int yy=0):x(xx),y(yy){}
};

class Board:public QObject
{
    Q_OBJECT
public:
    Board(int w,int h);
    int get_snakeid(Xy_pos pos);
    int get_impedenceid(Xy_pos pos);
    void setvalue(Xy_pos pos,int value);
private:
    int width,height;
    int status[100][100];  // 此数组表示棋盘上各个点的状态，使用二进制编码，后2位表示是否属于某个snake，
                           // 3,4位表示是否存在某个障碍物
public slots:
    void generate_food();
};

#endif // BOARD_H

extern Board* board;
