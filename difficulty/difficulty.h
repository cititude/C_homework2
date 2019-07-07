#ifndef DIFFICULTY_H
#define DIFFICULTY_H

#include <QDialog>
#include <QComboBox>
namespace Ui {
class Difficulty;
}

class Difficulty : public QDialog
{
    Q_OBJECT

public:
    explicit Difficulty(QWidget *parent = nullptr);
    ~Difficulty();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Difficulty *ui;
};

#endif // DIFFICULTY_H
