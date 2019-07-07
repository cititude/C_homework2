#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include<QPushButton>
class myPushbutton:public QPushButton
{
    Q_OBJECT
public:
    myPushbutton(QString path);
    QString imgPath;
};

#endif // MYPUSHBUTTON_H
