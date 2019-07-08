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
    board->generate_food();
    this->check();
    connect(timer,&QTimer::timeout,[=](){
        python->move();
        this->check();
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

void playscene::check()
{
    for(int i=0;i<board->width;i++)
        for(int j=0;j<board->height;j++)
        {
            Xy_pos tmp=Xy_pos(i,j);
            if(board->get_impedenceid(tmp)==1)
            {
                bool find=false;
                for(int k=0;k<obstacles.size();k++)
                {

                    if(obstacles[k].get_pos()==tmp)
                    {
                        find=true;
                    }
                }
                if(!find)
                {
                    Obstacle* food=new Obstacle(":/icons/icons/food.JPG",tmp,1);
                    obstacles.push_back(*food);
                    obstacles.back().setParent(this);
                    obstacles.back().show();
                }
            }
            if(board->get_impedenceid(tmp)==0)
            {
                for(int k=0;k<obstacles.size();k++)
                {
                    if(obstacles[k].get_pos()==tmp)
                    {
                        obstacles[k].hide();
                    }
                }
            }
        }
}
