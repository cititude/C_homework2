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
    QList<snakeNode> snakeBody;

    int id;
    int speed;
    int hp;
    int direction;  //1:up  2:right  3: down 4: left

public:
    int nnode=0;
    void turnleft();
    void turnright();
    void turnup();
    void turndown();
    void attack();
    void lengthen();
    void move();
    bool be_dead();
    Xy_pos get_next();
    void lifecheck();
    explicit Snake(QWidget *parent = nullptr,int newid=1);
    ~Snake();

private:
    Ui::Snake *ui;

};

#endif // SNAKE_H
