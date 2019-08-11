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
    explicit playscene(QWidget *parent = nullptr,int mod=0,int dif=2);
    ~playscene();
    void paintEvent(QPaintEvent* );
    void check();
private:
    Ui::playscene *ui;
    bool ispause;
    int difficulty;
    int mode;   //mode=1 双人对战 mode=2人机对战
    int score=0;
public:
    WaterSnake* watersnake;
    Boa* boa;
    QList <Obstacle> obstacles;
    void keyPressEvent(QKeyEvent* );
    void restore();
    void bullet_move();
    int get_score();
signals:
    void backtomain();
    void pause();
};

#endif // PLAYSCENE_H
