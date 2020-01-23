#include "carcardwidget.h"
#include "ui_carcardwidget.h"
#include "QPixmap"

CarCardWidget::CarCardWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CarCardWidget)
{
    ui->setupUi(this);
    QPixmap carImage("://defaultImage.jpg");
    ui->carImagePixmap->setPixmap(carImage.scaled(300,400,Qt::KeepAspectRatio));
}

void CarCardWidget::setSetting(QString car_brand, QString car_modell, QString car_type, int price)
{
    QString car_price = QString::number(price);

    ui->carBrandLabel->setText(car_brand);
    ui->CarModelLabel->setText(car_modell);
    ui->carTypeLabel->setText(car_type);
    ui->carPriceLabel->setText(car_price);
}

CarCardWidget::~CarCardWidget()
{
    delete ui;
}
