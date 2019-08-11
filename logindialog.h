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
    static bool logged;
private slots:
    void on_pushButton_2_clicked();     // login button event

    void on_pushButton_clicked();       // logout button event

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
