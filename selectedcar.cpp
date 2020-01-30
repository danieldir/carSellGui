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
    DBConnector::setRequestedFromCar(IdCar, true);
    this->close();
}

void selectedCar::on_cancelButton_clicked()
{
    this->close();
}

void selectedCar::setSetting(QString description, QString brand, int id)
{
    ui->carDescriptionLabel->setText(description);
    IdCar = id;
    this->setWindowTitle(brand);
}
