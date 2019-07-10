#ifndef COBRA_H
#define COBRA_H

#include <snake.h>

namespace Ui {
class Cobra;
}

class Cobra : public Snake      //眼镜蛇，
{
    Q_OBJECT

public:
    explicit Cobra();
    ~Cobra();

private:
    Ui::Cobra *ui;
};

#endif // COBRA_H
