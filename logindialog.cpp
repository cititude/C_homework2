#include "logindialog.h"
#include "ui_logindialog.h"
#include <QFile>
#include <QDebug>
#include <QMessageBox>

int LoginDialog::Score=0;
QString LoginDialog::user="";
bool LoginDialog::logged=false;
LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowTitle("Log in");
    this->setWindowIcon(QIcon(":/icons/icons/background.jpg"));
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

//登录按钮
void LoginDialog::on_pushButton_2_clicked()
{
    QFile* file=new QFile("C:/Users/hp/Documents/snake_entrymenu/database/data.txt");
    bool flag=false;
    if(!file->open(QIODevice::ReadOnly))
    {
        qDebug()<<"cannot open file";
        this->close();
        return;
    }
    else
    {
        char buf[1024];
        QString score;
        QString name;
        while(true)
        {
            qint64 linelength=file->readLine(buf,sizeof(buf));
            if(linelength==-1)break;
            QString info(buf);
            QStringList list=info.split(' ');
            if(list.count()<=2)continue;
            name=list[0];
            QString password=list[1];
            score=list[2];
            if(this->ui->lineEdit->text()==name&&this->ui->lineEdit_2->text()==password)
            {
                flag=true;
                break;
            }
        }
        if(flag==true)
        {
            QMessageBox::information(this,"login successfully","login successfully",true,true);
            this->Score=score.toInt();
            this->user=name;
            this->logged=true;
            file->close();
            this->close();
        }
        else
        {
            QMessageBox::warning(this,"wrong username or password","wrong username or password",true,true);
            //this->close();
            file->close();
        }
    }
}

//注册按钮
void LoginDialog::on_pushButton_clicked()
{
    QFile* file=new QFile("C:/Users/hp/Documents/snake_entrymenu/database/data.txt");
    bool flag=true;
    if(!file->open(QIODevice::ReadOnly))
    {
        qDebug()<<"cannot open file";
        this->close();
        return;
    }
    else
    {
        char buf[1024];
        QStringList list;
        QString name=this->ui->lineEdit->text();
        QString password=this->ui->lineEdit_2->text();
        QString score="0";
        while(true)
        {
            qint64 linelength=file->readLine(buf,sizeof(buf));
            if(linelength==-1)break;
            QString info(buf);
            list=info.split(' ');
            if(list[0]==name)
            {
                flag=false;
                break;
            }
        }
        if(flag==false)
        {
            QMessageBox::warning(this,"user existed","user existed",true,true);
            file->close();
            //this->close();
        }
        else
        {
            file->close();
            QFile* ffile=new QFile("C:/Users/hp/Documents/snake_entrymenu/database/data.txt");
            ffile->open(QIODevice::WriteOnly|QIODevice::Append);
            ffile->write(name.toLatin1(),name.length());
            ffile->putChar(' ');
            ffile->write(password.toLatin1(),password.length());
            ffile->putChar(' ');
            ffile->write(score.toLatin1(),score.length());
            ffile->putChar('\n');
            QMessageBox::information(this,"register successfully","register successfully",true,true);
            ffile->close();
            this->close();
        }
    }
}
