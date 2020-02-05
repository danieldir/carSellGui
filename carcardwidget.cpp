#include "carcardwidget.h"
#include "ui_carcardwidget.h"
#include "QPixmap"
#include "selectedcar.h"

CarCardWidget::CarCardWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CarCardWidget)
{
    ui->setupUi(this);


}

void CarCardWidget::setSetting(int car_id,QByteArray byteImage, QString car_brand, QString car_modell, QString car_type, int price, QString car_city, int mileage, QString car_description)
{
    QString car_price = QString::number(price);
    QString car_mileage = QString::number(mileage);
    QPixmap carImage = QPixmap();
    QPixmap defaultImage("://defaultImage.jpg");
    description = car_description;
    carBrand = car_brand;
    carId = car_id;
    carCity= car_city;
    carMileage= mileage;
    carImage.loadFromData(byteImage);
    if(byteImage != "" ) // display default Image if the current car don't get Image
    {
        ui->carImagePixmap->setPixmap(carImage.scaled(300,400,Qt::KeepAspectRatio));
    }
    else
    {
        ui->carImagePixmap->setPixmap(defaultImage.scaled(300,400,Qt::KeepAspectRatio));
    }
    ui->carBrandLabel->setText(carBrand);
    ui->CarModelLabel->setText(car_modell);
    ui->carTypeLabel->setText(car_type);
    ui->carPriceLabel->setText(car_price);
    ui->carLocationLabel->setText(carCity);

    //Labels einfügen
    //ui->carMileageLabel->setText(car_mileage);
    //Insert Description here!
}

int CarCardWidget::getCarMileage()
{
    return carMileage;
}
QString CarCardWidget::getCarDescrition()
{
    return description;
}

QString CarCardWidget::getCarBrand()
{
    return carBrand;
}
QString CarCardWidget::getCarCity()
{
    return carCity;
}

int CarCardWidget::getCarId() {
    return carId;
}

CarCardWidget::~CarCardWidget()
{
    delete ui;
}
