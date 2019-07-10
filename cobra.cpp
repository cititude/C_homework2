#include "cobra.h"
#include "ui_cobra.h"

Cobra::Cobra(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Cobra)
{
    ui->setupUi(this);
}

Cobra::~Cobra()
{
    delete ui;
}
