#ifndef BOA_H
#define BOA_H

#include <QWidget>
#include <snake.h>

namespace Ui {
class Boa;
}

class Boa : public Snake
{
    Q_OBJECT

public:
    explicit Boa(QString img="");         //蟒蛇，可以穿过自己的身体
    ~Boa();
    void keyPressEvent(QKeyEvent* );
    void automove();
private:
    Ui::Boa *ui;
};

#endif // BOA_H
