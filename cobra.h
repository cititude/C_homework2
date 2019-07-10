#ifndef COBRA_H
#define COBRA_H

#include <QWidget>

namespace Ui {
class Cobra;
}

class Cobra : public QWidget
{
    Q_OBJECT

public:
    explicit Cobra(QWidget *parent = nullptr);
    ~Cobra();

private:
    Ui::Cobra *ui;
};

#endif // COBRA_H
