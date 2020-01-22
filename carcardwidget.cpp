#include "carcardwidget.h"
#include "ui_carcardwidget.h"
#include "QPixmap"

CarCardWidget::CarCardWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CarCardWidget)
{
    ui->setupUi(this);
    QPixmap carImage("/home/surmesure/Schreibtisch/carNoImage.jpg");
    ui->carImagePixmap->setPixmap(carImage.scaled(400,400,Qt::KeepAspectRatio));
}

CarCardWidget::~CarCardWidget()
{
    delete ui;
}
