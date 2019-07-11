#include "logindialog.h"
#include "ui_logindialog.h"
#include <QFile>
#include <QDebug>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pushButton_2_clicked()
{
    QFile* file=new QFile("C:/Users/hp/Documents/snake_entrymenu/database/data.txt");
    if(!file->open(QIODevice::ReadOnly))
    {
        qDebug()<<"cannot open file";
        this->close();
        return;
    }
    else
    {
        char buf[200];

        while(file->readLine(buf,200))
        {
            if()
        }
        this->close();
    }

}

void LoginDialog::on_pushButton_clicked()
{
    this->close();
}
