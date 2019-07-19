#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();
    static int Score;
    static QString user;
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
