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
//    void TimerEvent(QTimerEvent* );
//    void mousePressEvent(QMouseEvent*);
private:
    Ui::playscene *ui;
public:
    Snake* python;
    void keyPressEvent(QKeyEvent* );
};

#endif // PLAYSCENE_H
