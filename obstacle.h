#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QWidget>

namespace Ui {
class Obstacle;
}

class Obstacle : public QWidget
{
    Q_OBJECT

public:
    explicit Obstacle(QWidget *parent = nullptr);
    ~Obstacle();

private:
    Ui::Obstacle *ui;
};

#endif // OBSTACLE_H
