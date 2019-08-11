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
    void mymove();  // bullet move
    bool disappear();
    int get_type();     // 1:food 2:brick 3:bullet
    Xy_pos get_pos();
    int get_attack();
private:
    Ui::Obstacle *ui;
    Xy_pos pos;
    int lifetime;
    int move_direction;
    int move_speed;
    int type;            // 1:food 2:brick 3:bullet
    int attack;         //  hurt of obstacle to snake( default value:3)
    QString imgpath;
};

#endif // OBSTACLE_H

