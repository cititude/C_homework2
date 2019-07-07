#include "mypushbutton.h"
#include <QPixmap>
#include <QDebug>
#include <board.h>
myPushbutton::myPushbutton(QString path)
{
    this->imgPath=path;
    QPixmap pix;
    bool ret =pix.load(path);
    if(!ret)
    {
        qDebug()<<"fail to load!";
        return ;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
}
