#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QComboBox>

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = nullptr);
    ~SettingDialog();
     QLabel* label1;
     QLabel* label2;
     QComboBox* cbox1;
     QComboBox* cbox2;
     Ui::SettingDialog *ui;
};

#endif // SETTINGDIALOG_H
