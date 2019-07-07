#include "difficulty.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Difficulty w;
    w.show();

    return a.exec();
}
