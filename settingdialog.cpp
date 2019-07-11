#include "settingdialog.h"
#include "ui_settingdialog.h"

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
    label1=new QLabel("Difficulty");
    label2=new QLabel("Mode");
    label1->setParent(this);
    label2->setParent(this);
    label1->move(60,80);
    label2->move(60,120);
    label1->show();
    label2->show();
    cbox1=new QComboBox;
    cbox1->addItem("0");
    cbox1->addItem("1");
    cbox1->addItem("2");
    cbox1->addItem("3");
    cbox1->setParent(this);
    cbox1->move(240,80);
    cbox1->show();
    cbox2=new QComboBox;
    cbox2->addItem("Human VS Human");
    cbox2->addItem("Human Vs AI");
    cbox2->setParent(this);
    cbox2->move(240,120);
    cbox2->show();
}

SettingDialog::~SettingDialog()
{
    delete ui;
}
