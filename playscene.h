#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <QPainter>
#include <snake.h>
#include <QTimer>
#include <QTimerEvent>
#include <QDebug>
#include <QMouseEvent>
#include <QKeyEvent>
#include <board.h>
#include <obstacle.h>
#include <QList>

namespace Ui {
class playscene;
}

class playscene : public QMainWindow
{
    Q_OBJECT

public:
    explicit playscene(QWidget *parent = nullptr);
    ~playscene();
    void paintEvent(QPaintEvent* );
    void check();
//    void TimerEvent(QTimerEvent* );
//    void mousePressEvent(QMouseEvent*);
private:
    Ui::playscene *ui;
    bool ispause;
public:
    Snake* python;
    QList <Obstacle> obstacles;
    void keyPressEvent(QKeyEvent* );
    void restore();
signals:
    void backtomain();
    void pause();
};

#endif // PLAYSCENE_H
