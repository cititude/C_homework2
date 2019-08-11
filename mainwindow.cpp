#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QToolBar>
#include <QPushButton>
#include <QTime>
#include <QLabel>
#include <QDockWidget>
#include <QTextEdit>
#include<QPainter>
#include<QPalette>
#include<mypushbutton.h>
#include<playscene.h>
#include <board.h>
#include <QSound>
#include <QMessageBox>
#include <logindialog.h>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //create menubar
    ui->setupUi(this);
    setFixedSize(1200,800);

    this->setWindowTitle("SNAKE FIGHTING");
    QIcon menuicon(":/icons/icons/menu.jpg");
    this->setWindowIcon(menuicon);
    resize(600,400);
    QMenuBar *bar =menuBar();
    setMenuBar(bar);

    //create menu
    QMenu* OptionMenu=bar->addMenu("options");
    bar->addSeparator();
    QMenu* SettingMenu=bar->addMenu("setting");
    bar->addSeparator();
    QMenu* HelpMenu=bar->addMenu("help");
    QAction* helpc=HelpMenu->addAction("help(Chinese)");
    connect(helpc,&QAction::triggered,[=](){
       QMessageBox::information(this,"help",QString::fromLocal8Bit("      本游戏共有两种模式，分别为双人对战模式与人机对战模式，且可以通过调整难度（difficulty）改变地图中的障碍物的个数，可以在设置（setting）菜单中选择所需要的对战模式（fighting mode）。\n"
                                "        游戏中共有两种不同类型的蛇，其中橙色的蛇通过键盘的上下左右键控制其运动方向，橙色的蛇的蛇头不能够与自身身体相碰，否则会立刻死亡。可以通过按下空格键控制橙色的蛇发射子弹，被子弹击中将会损减部分生命值,被击中3次后死亡。绿色的蛇通过键盘的wasd键控制其运动方向，其蛇头可以与自身的蛇身相碰，甚至可以穿过自己的身体，但不能够发射子弹攻击对方。两只蛇的蛇头均不能够碰到对方的蛇身或障碍物（黑色方块）。\n"
                                "        游戏中按键P可以暂停游戏，再次按P键可以继续游戏。\n"
                                "        在双人对战模式中，用户的目的是在存活的时间更久，若在30回合时仍未有角色死亡，则比较积分。在人机对战模式中，用户的目的是积分尽可能高。积分计算方式为：坚持的回合数*0.03+所吃食物数*(难度系数*0.7+1)。\n"
                                "        用户可以选择setting菜单中的login命令进行注册登陆，登陆后的最高分数据会予以保存。当然，用户也可以选择不注册登陆直接开始游戏。\n"
                                "        祝您游戏愉快！"),true,true);
    });
    //create menu options
    QAction* GameSetting=SettingMenu->addAction("Game Setting");
    SettingMenu->addSeparator();
    QAction* Logout=SettingMenu->addAction("Logout");
    QAction* Login=SettingMenu->addAction("Login");


    //user information
    QLabel* login_warning=new QLabel("Warning: You haven't log in.");
    QFont labelft;
    labelft.setPointSize(20);
    labelft.setFamily("行楷");
    QPalette labelpa;
    labelpa.setColor(QPalette::WindowText,Qt::red);
    login_warning->move(600,150);
    login_warning->setParent(this);
    login_warning->setFont(labelft);
    login_warning->setPalette(labelpa);
    login_warning->show();

    //login dialog
    connect(Login,&QAction::triggered,[=]()
    {
        if(islogin)
        {
            QMessageBox::information(this,"information","You have logged in!",true,true);
        }
        else
        {
            LoginDialog* login=new LoginDialog();
            login->exec();
            if(LoginDialog::logged==true)
            {
                islogin=true;
                score=LoginDialog::Score;
                user=LoginDialog::user;
                login_warning->setText("Highest Score: "+QString::number(score));
            }
        }
    });

    connect(Logout,&QAction::triggered,[=](){
        islogin=false;
        user="";
        score=0;
        LoginDialog::Score=0;
        LoginDialog::user="";
        LoginDialog::logged=false;
        QMessageBox::information(this,"logout successfully","logout successfully",true,true);
        login_warning->setText("Warning: You haven't log in.");
    });
    settingdia=new SettingDialog;
    connect(GameSetting,&QAction::triggered,[=](){
        settingdia->show();
    });

    QAction* NewGameAction=OptionMenu->addAction("New game");
    QAction* Quit=OptionMenu->addAction("quit");
    connect(Quit,&QAction::triggered,[=](){
        this->close();
    });
    //create tool bar
    QToolBar* toolbar=new QToolBar(this);
    addToolBar(Qt::LeftToolBarArea,toolbar);
    toolbar->setFloatable(false);
    toolbar->setMovable(false);

    //create status bar
    QStatusBar* stBar=statusBar();
    setStatusBar(stBar);
    QLabel* qlabel=new QLabel();
    qlabel->setText("author: Can Chang");
    stBar->addPermanentWidget(qlabel);

    //create title
    QLabel* title=new QLabel();
    title->setParent(this);
    title->setText("Snake Fighting");
    QFont* ft=new QFont();
    ft->setPointSize(30);
    ft->setFamily("行楷");
    ft->setItalic(true);
    title->setFont(*ft);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::blue);
    title->setPalette(pa);
    title->move(600,-100);

    // create start button
    myPushbutton* startbutton=new myPushbutton(":/icons/icons/startbutton.png");
    startbutton->setParent(this);
    startbutton->move(700,200);

    //create playscene
    connect(startbutton,&myPushbutton::clicked,[=](){
        int difficulty=settingdia->cbox1->currentText().toInt();
        int mode=settingdia->cbox2->currentIndex()+1;
        playscene* newplayscene=new playscene(this,mode,difficulty);
        this->hide();
        newplayscene->show();
        connect(newplayscene,&playscene::backtomain,this,[=]()
        {
            this->show();
            score=max(score,newplayscene->get_score());
            if(islogin&&mode==2)login_warning->setText("Highest Score: "+QString::number(score));
            if(islogin)save_info();
            newplayscene->close();
        });
    });
    connect(NewGameAction,&QAction::triggered,[=]()
    {
        int difficulty=settingdia->cbox1->currentText().toInt();
        int mode=settingdia->cbox2->currentIndex()+1;
        playscene* newplayscene=new playscene(this,mode,difficulty);
        this->hide();
        newplayscene->show();
        connect(newplayscene,&playscene::backtomain,this,[=]()
        {
            this->show();
            score=max(score,newplayscene->get_score());
            if(islogin&&mode==2)login_warning->setText("Highest Score: "+QString::number(score));
            if(islogin)save_info();
            newplayscene->close();
        });
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent* )
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/icons/icons/background.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

//将用户最高分存入文档
void MainWindow::save_info()
{
    QFile* fileread=new QFile("C:/Users/hp/Documents/snake_entrymenu/database/data.txt");
    QFile* filetmpwrite=new QFile("C:/Users/hp/Documents/snake_entrymenu/database/tmp.txt");
    if(!fileread->open(QIODevice::ReadOnly))
    {
        qDebug()<<"cannot open file";
        return;
    }
    else
    {
        if(!filetmpwrite->open(QIODevice::ReadWrite))
        {
            qDebug()<<"cannot open file";
            fileread->close();
            return;
        }
        char buf[1024];
        while(true)
        {
            memset(buf,0,sizeof(buf));
            qint64 linelength=fileread->readLine(buf,sizeof(buf));
            if(linelength==-1)break;
            QString info(buf);
            qDebug()<<info;
            QStringList list=info.split(' ');
            if(list.count()<=2)continue;
            if(user==list[0])
            {
                filetmpwrite->write(list[0].toLatin1(),list[0].length());
                filetmpwrite->putChar(' ');
                filetmpwrite->write(list[1].toLatin1(),list[1].length());
                filetmpwrite->putChar(' ');
                filetmpwrite->write(QString::number(score).toLatin1(),QString::number(score).length());
                filetmpwrite->putChar('\n');
                continue;
            }
            filetmpwrite->write(buf,linelength);
        }
        fileread->close();
        filetmpwrite->close();
        QFile* filewrite=new QFile("C:/Users/hp/Documents/snake_entrymenu/database/data.txt");
        QFile* filetmpread=new QFile("C:/Users/hp/Documents/snake_entrymenu/database/tmp.txt");
        if(!filewrite->open(QIODevice::WriteOnly)){qDebug()<<"file open error"; return;}
        if(!filetmpread->open(QIODevice::ReadOnly)){qDebug()<<"file open error"; return;}
        while(true)
        {
            memset(buf,0,sizeof(buf));
            qint64 linelength=filetmpread->readLine(buf,sizeof(buf));
            if(linelength==-1)break;
            QString info(buf);
            qDebug()<<info;
            QStringList list=info.split(' ');
            if(list.count()<=2)continue;
            filewrite->write(buf,linelength);
        }
        filewrite->close();
        filetmpread->close();
        return;
    }
}
