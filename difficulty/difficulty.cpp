#include "difficulty.h"
#include "ui_difficulty.h"
#include <QAction>
#include <QMessageBox>
#include <QColor>
#include <QColorDialog>
#include <QFont>
#include <QFontDialog>

Difficulty::Difficulty(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Difficulty)
{
    ui->setupUi(this);
    ui->comboBox->addItem("easy");
    ui->comboBox->addItem("normal");
    ui->comboBox->addItem("hard");
}

Difficulty::~Difficulty()
{
    delete ui;
}

void Difficulty::on_pushButton_clicked()
{

}
