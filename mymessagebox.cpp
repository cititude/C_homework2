#include "mymessagebox.h"

myMessageBox::myMessageBox(QObject *parent)
{

}

void myMessageBox::showEvent(QShowEvent* event) {
    QMessageBox::showEvent(event);
    setFixedSize(640, 480);
}


