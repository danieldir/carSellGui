#include "gallerycardwidget.h"
#include "ui_gallerycardwidget.h"

GalleryCardWidget::GalleryCardWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GalleryCardWidget)
{
    ui->setupUi(this);
    QPixmap galleryImage("://defaultImage.jpg");
    ui->imageLabel->setPixmap(galleryImage.scaled(80,80,Qt::KeepAspectRatio));

}

void GalleryCardWidget::setting(int carId, QString labelBranch, QString labelModel, QString labelType, int Price, QByteArray byteImage)

  {
     labelPrice= QString::number(Price);
     QString labelId = QString::number(carId);
     //QString mileage = QString::number(mileage);

     QPixmap carImage = QPixmap();
     QPixmap defaultImage("://defaultImage.jpg");

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

     carImage.loadFromData(byteImage);
     if(byteImage != "" ) // display default Image if the current car don't get Image
     {
         ui->imageLabel->setPixmap(carImage.scaled(140,200,Qt::KeepAspectRatio));
     }
     else
     {
         ui->imageLabel->setPixmap(defaultImage.scaled(140,200,Qt::KeepAspectRatio));
     }
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
