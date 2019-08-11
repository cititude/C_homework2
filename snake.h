#ifndef SNAKE_H
#define SNAKE_H

#include <QWidget>
#include <QLabel>
#include <QList>
#include<snakenode.h>
#include <board.h>

namespace Ui {
class Snake;
}

class Snake : public QWidget
{
    Q_OBJECT
public:
    void hurt(int v);
    void turnleft();
    void turnright();
    void turnup();
    void turndown();
    void lengthen();
    void move();
    bool be_dead();
    bool directionChanged=false;
    QString imgpath;
    Xy_pos get_next(int round=1);
    void hurtcheck();   //用于执行move过程中撞到障碍物造成的生命值损失
    explicit Snake(QWidget *parent = nullptr,QString img="");
    ~Snake();
    int get_id();
    int get_direction();
    int get_score();

    virtual void keyPressEvent(QKeyEvent* );

protected:
    QList<snakeNode> snakeBody;
    int id;         // id=1 蟒蛇boa id=2 水蛇watersnake
    int hp;
    int direction;  //1:up  2:right  3: down 4: left
    int nnode=0;
    int score;
};

#endif // SNAKE_H
