#ifndef FINISH_H
#define FINISH_H

#include <QDialog>
#include <QLabel>

namespace Ui {
class Finish;
}

class Finish : public QDialog
{
    Q_OBJECT

public:
    explicit Finish(QWidget *parent = nullptr,QString text="");
    ~Finish();

private:
    Ui::Finish *ui;
    QLabel* qlabel;
};

#endif // FINISH_H
