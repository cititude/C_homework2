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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setAttribute(Qt::WA_DeleteOnClose);
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
    //bar->addSeparator();
    QMenu* SettingMenu=bar->addMenu("setting");
    //bar->addSeparator();
    QMenu* HelpMenu=bar->addMenu("help");

    //create menu options
    QAction* GameSetting=SettingMenu->addAction("Game Setting");
    SettingMenu->addSeparator();
    QAction* Logout=SettingMenu->addAction("Logout");
    QAction* Login=SettingMenu->addAction("Login");
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

            //
            login->exec();
        }
    });

    connect(Logout,&QAction::triggered,[=](){
        islogin=false;
        user="";
    });
    settingdia=new SettingDialog;
    connect(GameSetting,&QAction::triggered,[=](){
        settingdia->show();
    });

    QAction* ContinueGameAction=OptionMenu->addAction("Continue");
    QAction* NewGameAction=OptionMenu->addAction("New game");

    //create tool bar
    QToolBar* toolbar=new QToolBar(this);
    addToolBar(Qt::LeftToolBarArea,toolbar);
    toolbar->setFloatable(false);
    toolbar->setMovable(false);

    //create status bar
    QStatusBar* stBar=statusBar();
    setStatusBar(stBar);
    QLabel* qlabel=new QLabel();
    qlabel->setText("author: cititude");
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
