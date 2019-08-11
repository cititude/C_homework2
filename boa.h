#ifndef BOA_H
#define BOA_H

#include <QWidget>
#include <snake.h>

namespace Ui {
class Boa;
}
//蟒蛇，可以穿过自己的身体，但不可以发射子弹
class Boa : public Snake
{
    Q_OBJECT

public:
    explicit Boa(QString img="");
    ~Boa();
    void keyPressEvent(QKeyEvent* );
    void automove();
private:
    Ui::Boa *ui;
};

#endif // BOA_H
