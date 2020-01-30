#include "selectedcar.h"
#include "ui_selectedcar.h"

selectedCar::selectedCar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::selectedCar)
{
    ui->setupUi(this);
}

selectedCar::~selectedCar()
{
    delete ui;
}



void selectedCar::on_buyButton_clicked()
{

}

void selectedCar::on_cancelButton_clicked()
{
    this->close();
}

void selectedCar::setSetting(QString description, QString brand)
{
    ui->carDescriptionLabel->setText(description);

    this->setWindowTitle(brand);
}
