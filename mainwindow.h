#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <settingdialog.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent* );
private:
    Ui::MainWindow *ui;
    SettingDialog* settingdia;
    bool islogin=false;
    QString user;
};

#endif // MAINWINDOW_H
