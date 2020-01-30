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

void GalleryCardWidget::setting( QString labelBranch, QString labelModel, QString labelType, int Price)
  {
     QString labelPrice = QString::number(Price);
     ui->labelBranch->setText(labelBranch);
     ui->labelModel->setText(labelModel);
     ui->labelType->setText(labelType);
     ui->labelPrice->setText(labelPrice);
  }

GalleryCardWidget::~GalleryCardWidget()
{
    delete ui;
}