#ifndef SNAKENODE_H
#define SNAKENODE_H
#include <QWidget>
#include <QLabel>
#include <board.h>


class snakeNode:public QLabel
{
    Q_OBJECT
public:
    snakeNode(QString imgpath="",int xx=30,int yy=30);
    snakeNode(const snakeNode& othernode);
    Xy_pos xy_pos;
private:
    QString img;    //background picture
};

#endif // SNAKENODE_H
