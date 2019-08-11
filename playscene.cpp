#include "playscene.h"
#include "ui_playscene.h"
#include <QPushButton>
#include <board.h>
#include <QMessageBox>
#include <mypushbutton.h>
#include <QSound>

inline int min(int a,int b){return a<b?a:b;}
playscene::playscene(QWidget *parent,int newmode,int dif) :
    QMainWindow(parent),
    ui(new Ui::playscene)
{
    ui->setupUi(this);
    // initialize the board
    setFixedSize(1200,800);
    setWindowTitle("SNAKE FIGHTING");
    ispause=0;

    // set mode,difficulty,music
    mode=newmode;
    difficulty=dif;

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
    for(int i=0;i<difficulty*10;i++)board->generate_bricks();
    this->check();
    //安全情况下，对初始化最初蛇长为2
    if(board->get_impedenceid(watersnake->get_next())!=2)watersnake->lengthen();
    if(board->get_impedenceid(boa->get_next())!=2)boa->lengthen();
    if(mode==2)
    {
        for(int k=1;k<=10;k++)
        {
            if(boa->get_next().on_boarder()||boa->get_next(2).on_boarder())break;
            boa->lengthen();
        }
    }
    board->generate_food();
    this->check();
    timer->start(300);
    timer2->start(5000);    //  brick/food generator
    //每隔5000ms，地图中可移动范围缩小，并产生食物
    connect(timer2,&QTimer::timeout,[=]()
    {
        board->round=min(board->round+1,30);
        board->generate_bricks();
        board->generate_food();
    });

    // watersnake attack behavior
    connect(watersnake,&WaterSnake::attack,[=](){
        if(!watersnake->try_attack())return;
        Xy_pos nnext=watersnake->get_next(2);
        Obstacle* bullet=new Obstacle(":/icons/icons/bullet.jpg",nnext,3,watersnake->get_direction());
        obstacles.push_back(*bullet);
        obstacles.back().setParent(this);
        obstacles.back().show();
        board->setvalue(nnext,(3<<2)+board->get_snakeid(nnext));
        return;
    });

    //每隔100ms，蛇移动，判断蛇的状态并更新地图
    connect(timer,&QTimer::timeout,[=](){
        if(mode==2&&!boa->be_dead())boa->automove();
        watersnake->move();
        if(!boa->be_dead())boa->move();
        this->check();
        // check whether game is over
        if(watersnake->be_dead()||boa->be_dead()||(board->round>30&&mode==1))
        {

            if(mode==2&&boa->be_dead()&&!watersnake->be_dead())
            {
                // 游戏继续，不做任何死亡处理
            }
            else
            {
                if(board->round>30)
                {
                    double w_score=watersnake->get_score()*(difficulty*0.7+1);
                    double b_score=boa->get_score()*(difficulty*0.7)+1;
                    if(w_score>b_score)
                    {
                        QMessageBox::warning(this,"Game over","Game over,orange win!",true,true);
                    }
                    else if(fabs(w_score-b_score)<0.001)
                    {
                        QMessageBox::warning(this,"Game over","Game over,tied!",true,true);
                    }
                    else
                    {
                        QMessageBox::warning(this,"Game over","Game over,green win!",true,true);
                    }
                }
                else if(watersnake->be_dead())
                {
                    if(mode==1)QMessageBox::warning(this,"Game over","Game over,green win!",true,true);
                    else
                    {
                        this->score=(int)(board->round*0.3+watersnake->get_score()*(difficulty*0.7+1));
                        QMessageBox::warning(this,"Game over","Game over! Your score is "+QString::number(score),true,true);
                    }
                }
                else QMessageBox::warning(this,"Game over","Game over,orange win!",true,true);
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
        }
    });

    //暂停事件处理
    connect(this,&playscene::pause,[=]()
    {
        if(ispause)
        {
            ispause=0;
            timer->start(300);
            timer2->start(5000);
        }
        else
        {
            ispause=1;
            timer->stop();
            timer2->stop();
        }
    });
}

playscene::~playscene()
{
    delete ui;
}

//绘制地图
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

//键盘事件
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
    }
}

//检查更新地图
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

// 子弹移动并计算杀伤情况
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
            if(board->get_snakeid(next)==1)boa->hurt(3);
            if(board->get_snakeid(nnext)==1)boa->hurt(3);
            if(board->get_snakeid(next)==2)watersnake->hurt(3);
            if(board->get_snakeid(nnext)==2)watersnake->hurt(3);
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

int playscene::get_score(){return score;}
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
