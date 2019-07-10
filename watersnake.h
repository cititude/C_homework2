#ifndef WATERSNAKE_H
#define WATERSNAKE_H

#include <QWidget>
#include <snake.h>
namespace Ui {
class WaterSnake;
}

class WaterSnake : public Snake
{
    Q_OBJECT
public:
    explicit WaterSnake(QString img="");
    ~WaterSnake();
    void keyPressEvent(QKeyEvent* );
private:
    Ui::WaterSnake *ui;
signals:
    void attack();
};

#endif // WATERSNAKE_H
