#include "playscene.h"
#include "ui_playscene.h"
#include <QPushButton>
#include <board.h>
#include <QMessageBox>
#include <mypushbutton.h>

inline int min(int a,int b){return a<b?a:b;}
playscene::playscene(QWidget *parent,int newmode) :
    QMainWindow(parent),
    ui(new Ui::playscene)
{
    ui->setupUi(this);
    // initialize the board
    for(int i=0;i<board->width;i++)
        for(int j=0;j<board->height;j++)
        {
            qDebug()<<board->get_impedenceid(Xy_pos(i,j));
        }
    setFixedSize(1200,800);
    ispause=0;

    // set mode
    mode=newmode;

    //set watersnake
    watersnake=new WaterSnake(":/icons/icons/snakenode.JPG");
    watersnake->setParent(this);

    boa=new Boa(":/icons/icons/snakenode2.JPG");
    boa->setParent(this);
    //set main timer
    QTimer* timer= new QTimer(this);

    //brick-generator
    QTimer* timer2=new QTimer(this);

    //initialize bricks food, and snake
    for(int i=0;i<10;i++)board->generate_bricks();
    this->check();
    timer->start(100);
    watersnake->lengthen();
    boa->lengthen();
    board->generate_food();
    this->check();

    //brick/food generator
    timer2->start(5000);
    connect(timer2,&QTimer::timeout,[=]()
    {
        board->round=min(board->round+1,30);
        board->generate_bricks();
        board->generate_food();
    });

    // watersnake attack behavior
    connect(watersnake,&WaterSnake::attack,[=](){
        Xy_pos nnext=watersnake->get_next(2);
        Obstacle* bullet=new Obstacle(":/icons/icons/bullet.jpg",nnext,3,watersnake->get_direction());
        obstacles.push_back(*bullet);
        obstacles.back().setParent(this);
        obstacles.back().show();
        board->setvalue(nnext,(3<<2)+board->get_snakeid(nnext));
        return;
    });

    //
    connect(timer,&QTimer::timeout,[=](){
        watersnake->move();
        boa->move();
        this->check();
        connect(this,&playscene::pause,[=]()
        {
            if(ispause)
            {
                ispause=0;
                timer->start(500);
                timer2->start(5000);
            }
            else
            {
                ispause=1;
                timer->stop();
                timer2->stop();
            }
        });
        if(watersnake->be_dead()||boa->be_dead())
        {
            if(watersnake->be_dead())QMessageBox::warning(this,"Game over","Game over,boa win!",true,true);
            else QMessageBox::warning(this,"Game over","Game over,watersnake win!",true,true);
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
    case Qt::Key_P:
        emit this->pause();
        break;
    case Qt::Key_Up:
        watersnake->turnup();
        break;
    case Qt::Key_Right:
        watersnake->turnright();
        break;
    case Qt::Key_Down:
        watersnake->turndown();
        break;
    case Qt::Key_Left:
        watersnake->turnleft();
        break;
    case Qt::Key_Space:
        emit watersnake->attack();
        break;
    case Qt::Key_W:
        boa->turnup();
        break;
    case Qt::Key_D:
        boa->turnright();
        break;
    case Qt::Key_S:
        boa->turndown();
        break;
    case Qt::Key_A:
        boa->turnleft();
        break;
    default:break;
    }
}

void playscene::check()
{
    for(int i=0;i<board->width;i++)
        for(int j=0;j<board->height;j++)
        {
            Xy_pos tmp=Xy_pos(i,j);
            if(board->get_impedenceid(tmp)==1)  //find food
            {
                bool find=false;
                for(int k=0;k<obstacles.size();k++)
                {
                    if(obstacles[k].get_pos()==tmp&&obstacles[k].get_type()==1) //food is shown
                    {
                        find=true;
                        obstacles[k].show();
                        break;
                    }
                }
                if(!find)                           // food isn't shown
                {
                    Obstacle* food=new Obstacle(":/icons/icons/food.JPG",tmp,1);
                    obstacles.push_back(*food);
                    food=nullptr;
                    obstacles.back().setParent(this);
                    obstacles.back().show();
                }
            }
            if(board->get_impedenceid(tmp)==2)  //  find brick
            {
                bool find=false;
                for(int k=0;k<obstacles.size();k++)
                {
                    if(obstacles[k].get_pos()==tmp&&obstacles[k].get_type()==2) //brick is shown
                    {
                        find=true;
                        obstacles[k].show();
                        break;
                    }
                }
                if(!find)                           //brick isn't shown
                {
                    Obstacle* brick=new Obstacle(":/icons/icons/brick.JPG",tmp,2);
                    obstacles.push_back(*brick);
                    brick=nullptr;
                    obstacles.back().setParent(this);
                    obstacles.back().show();
                }
            }
            if(board->get_impedenceid(tmp)==0)      // find nothing
            {
                for(int k=0;k<obstacles.size();k++)
                {
                    if(obstacles[k].get_pos()==tmp) // if something shown, hide it
                    {
                        obstacles[k].hide();
                        //obstacles.removeAt(k);
                    }
                }
            }
            if(board->get_impedenceid(tmp)==3)
            {
                for(int k=0;k<obstacles.size();k++)
                {
                    if(obstacles[k].get_pos()==tmp)
                    {
                        if(obstacles[k].disappear())
                        {
                            obstacles[k].hide();
                            board->setvalue(tmp,0);
                        }
                        else obstacles[k].show();
                    }
                }
            }
        }
    this->bullet_move();
}

void playscene::bullet_move()
{
    for(int k=0;k<obstacles.size();k++)
    {
        if(obstacles[k].get_type()==3&&!obstacles[k].disappear())
        {
            //qDebug()<<"bullet"<<obstacles[k].get_pos().x<<obstacles[k].get_pos().y;
            Xy_pos cur=obstacles[k].get_pos();
            obstacles[k].mymove();
            Xy_pos nnext=obstacles[k].get_pos();
            Xy_pos next=Xy_pos((cur.x+nnext.x)>>1,(cur.y+nnext.y)>>1);
            //qDebug()<<"bullet"<<obstacles[k].get_pos().x<<obstacles[k].get_pos().y;
            board->setvalue(cur,board->get_snakeid(cur));
            if(board->get_snakeid(next)==1)watersnake->hurt(3);
            if(board->get_snakeid(nnext)==1)watersnake->hurt(3);
            if(board->get_impedenceid(next)!=0)
            {
                for(int t=0;t<obstacles.size();t++)if(obstacles[t].get_pos()==next)obstacles[t].hide();
            }
            if(board->get_impedenceid(nnext)!=0)
            {
                for(int t=0;t<obstacles.size();t++)if(obstacles[t].get_pos()==nnext)obstacles[t].hide();
            }
            board->setvalue(nnext,board->get_snakeid(nnext)+(3<<2));
            obstacles[k].show();
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
    for(int i=0;i<obstacles.size();i++)
    {
        obstacles[i].hide();
    }
    board->round=0;
}
