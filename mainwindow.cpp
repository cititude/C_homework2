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
    //bar->addSeparator();
    QMenu* SettingMenu=bar->addMenu("setting");
    //bar->addSeparator();
    QMenu* HelpMenu=bar->addMenu("help");

    //create menu options
    QAction* FightModeAction=SettingMenu->addAction("Fighting Mode");
    SettingMenu->addSeparator();
    QAction* DifficultyAction=SettingMenu->addAction("Difficulty");
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
    playscene* newplayscene=new playscene(this);
    connect(startbutton,&myPushbutton::clicked,[=](){
        this->hide();
        newplayscene->show();
    });
    connect(NewGameAction,&QAction::triggered,[=]()
    {
        this->hide();
        newplayscene->show();
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
