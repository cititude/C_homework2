#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <QTimerEvent>
#include <QDebug>
#include <QMouseEvent>
#include <QKeyEvent>
#include <board.h>
#include <obstacle.h>
#include <QList>
#include <watersnake.h>
#include <boa.h>
namespace Ui {
class playscene;
}

class playscene : public QMainWindow
{
    Q_OBJECT

public:
    explicit playscene(QWidget *parent = nullptr,int mode=0);
    ~playscene();
    void paintEvent(QPaintEvent* );
    void check();
//    void TimerEvent(QTimerEvent* );
//    void mousePressEvent(QMouseEvent*);
private:
    Ui::playscene *ui;
    bool ispause;
    int mode;
public:
    WaterSnake* watersnake;
    Boa* boa;
    QList <Obstacle> obstacles;
    void keyPressEvent(QKeyEvent* );
    void restore();
    void bullet_move();
signals:
    void backtomain();
    void pause();
};

#endif // PLAYSCENE_H
