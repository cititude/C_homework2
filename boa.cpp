#include "boa.h"
#include "ui_boa.h"
#include <QKeyEvent>
Boa::Boa(QString img) :
    Snake(nullptr,img)
{
    id=1;
}

Boa::~Boa()
{
    delete ui;
}

void Boa::keyPressEvent(QKeyEvent* ev)
{
    switch(ev->key())
    {
    case Qt::Key_W:
        turnup();
        break;
    case Qt::Key_D:
        turnright();
        break;
    case Qt::Key_S:
        turndown();
        break;
    case Qt::Key_A:
        turnleft();
        break;
    }
}
