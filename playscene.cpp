#include "playscene.h"
#include "ui_playscene.h"
#include <QPushButton>
#include <board.h>
#include <QMessageBox>
#include <mypushbutton.h>

inline int min(int a,int b){return a<b?a:b;}
playscene::playscene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::playscene)
{
    ui->setupUi(this);
    setFixedSize(1200,800);
    ispause=0;
    python=new Snake();
    python->setParent(this);
    QTimer* timer= new QTimer(this);
    QTimer* timer2=new QTimer(this);    //brick-generator
    for(int i=0;i<10;i++)board->generate_bricks();
    this->check();
    timer->start(100);
    python->lengthen();
    board->generate_food();
    this->check();
    timer2->start(5000);
    connect(timer2,&QTimer::timeout,[=]()
    {
        board->round=min(board->round+1,30);
        board->generate_bricks();
        board->generate_food();
    });
    connect(timer,&QTimer::timeout,[=](){
        python->move();
        this->check();
        connect(this,&playscene::pause,[=]()
        {
            if(ispause)
            {
                ispause=0;
                timer->start(100);
                timer2->start(5000);
            }
            else
            {
                ispause=1;
                timer->stop();
                timer2->stop();
            }
        });
        if(python->be_dead())
        {
            qDebug()<<"dead";
            QMessageBox::warning(this,"Game over","Game over",true,true);
            timer->stop();
            timer2->stop();
            myPushbutton* backbtn=new myPushbutton(":/icons/icons/BackButton.png");
            backbtn->setParent(this);
            backbtn->move(1100,700);
            backbtn->show();
            connect(backbtn,&myPushbutton::clicked,[=](){
                this->restore();
                emit this->backtomain();
            });
        }
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
    case Qt::Key_P:
        emit this->pause();
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
            if(board->get_impedenceid(tmp)==2)
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
                    Obstacle* food=new Obstacle(":/icons/icons/brick.JPG",tmp,1);
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

void playscene::restore()
{
    for(int i=0;i<board->width;i++)
        for(int j=0;j<board->height;j++)
        {
            board->setvalue(Xy_pos(i,j),0);
        }
    check();
}
