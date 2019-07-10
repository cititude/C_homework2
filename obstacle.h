#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QWidget>
#include <QLabel>
#include <board.h>
#include <QList>

namespace Ui {
class Obstacle;
}

class Obstacle : public QLabel
{
    Q_OBJECT

public:
    explicit Obstacle(QString path,Xy_pos po,int ttype,int direction=0);
    Obstacle(const Obstacle& other);
    ~Obstacle();
    void mymove();
    bool disappear();
    int get_type();
    Xy_pos get_pos();
    int get_attack();
private:
    Ui::Obstacle *ui;
    Xy_pos pos;
    int lifetime;
    int move_direction;
    int move_speed;
    int type;           // 1:food
    bool can_pass;
    int attack;
    QString imgpath;
};

#endif // OBSTACLE_H

