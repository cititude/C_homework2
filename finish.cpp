#include "finish.h"
#include "ui_finish.h"

Finish::Finish(QWidget *parent,QString text) :
    QDialog(parent),
    ui(new Ui::Finish)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(100,100));
    qlabel->setText(text);
    qlabel->setFixedSize(QSize(30,30));
    qlabel->move((this->width()-qlabel->width())/2,(this->height()-qlabel->height())/2);
}

Finish::~Finish()
{
    delete ui;
}
