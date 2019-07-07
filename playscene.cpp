#include "playscene.h"
#include "ui_playscene.h"
#include <QPushButton>
#include <board.h>
playscene::playscene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::playscene)
{
    ui->setupUi(this);
    setFixedSize(1200,800);
    python=new Snake();
    python->setParent(this);
    QTimer* timer= new QTimer(this);
    timer->start(500);
    python->lengthen();
    connect(timer,&QTimer::timeout,[=](){
        python->move();
    });


}
playscene::~playscene()
{
    delete ui;
}

void playscene::paintEvent(QPaintEvent* )
{
    QPainter painter(this);
    QPixmap map[60][40];
    for(int i=0;i<60;i++)
        for(int j=0;j<40;j++)
        {
            map[i][j].load(":/icons/icons/BoardNode.png");
            painter.drawPixmap(i*20,j*20,20,20,map[i][j]);
        }
}

void playscene::keyPressEvent(QKeyEvent* ev)
{
    switch(ev->key())
    {
    case Qt::Key_Up:
        python->turnup();
        break;
    case Qt::Key_Right:
        python->turnright();
        break;
    case Qt::Key_Down:
        python->turndown();
        break;
    case Qt::Key_Left:
        python->turnleft();
        break;
    }
}
