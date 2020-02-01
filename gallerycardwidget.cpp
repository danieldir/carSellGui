#include "gallerycardwidget.h"
#include "ui_gallerycardwidget.h"

GalleryCardWidget::GalleryCardWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GalleryCardWidget)
{
    ui->setupUi(this);
    QPixmap galleryImage("://defaultImage.jpg");
    ui->imageLabel->setPixmap(galleryImage.scaled(100,100,Qt::KeepAspectRatio));

}

void GalleryCardWidget::setting(int carId, QString labelBranch, QString labelModel, QString labelType, int Price)

  {
     labelPrice= QString::number(Price);
     QString labelId = QString::number(carId);
     //QString mileage = QString::number(mileage);

     cBrand = labelBranch;
     cModel =labelModel;
     cType= labelType;
     //cCity =city;
    cPrice= Price;

     ui->labelBranch->setText(cBrand);
     ui->labelModel->setText(cModel);
     ui->labelType->setText(cType);
     ui->labelPrice->setText(labelPrice);
     ui->labelId->setText(labelId);
     ui->labelId->setStyleSheet("QLabel  {  color : white; }");
     cId = carId;
     cColor;//= carColor;
     cCity;//= city;
     car_description; //= descript;
  }
int GalleryCardWidget::getCarPrice()
{
    return cPrice;
}

//int GalleryCardWidget::getCarMileage()
//{
//    return cMileage;
//}

int GalleryCardWidget::getCarId()
{
    return cId;
}

//QString GalleryCardWidget::getCarDescrition()
//{
//    return car_description;
//}

QString GalleryCardWidget::getCarBrand()
{
    return cBrand;
}

QString GalleryCardWidget::getCarModel()
{
    return cModel;
}
QString GalleryCardWidget::getCarType()
{
    return cType;
}
QString GalleryCardWidget::getCarcolor()
{
    return cColor;
}
QString GalleryCardWidget::getCarcity()
{
    return cCity;
}


GalleryCardWidget::~GalleryCardWidget()
{
    delete ui;
}
