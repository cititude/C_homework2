#include "obstacle.h"
#include "ui_obstacle.h"

Obstacle::Obstacle(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Obstacle)
{
    ui->setupUi(this);
}

Obstacle::~Obstacle()
{
    delete ui;
}
