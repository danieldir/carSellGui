#ifndef CARCARDWIDGET_H
#define CARCARDWIDGET_H

#include <QWidget>
#include "selectedcar.h"

namespace Ui {
class CarCardWidget;
}

class CarCardWidget : public QWidget
{
    Q_OBJECT

public:
    void setSetting(int,QString,QString,QString,int,QString,int,QString);
    QString getCarDescrition();
    QString getCarBrand();
    int getCarId();
    int getCarMileage();
    QString  getCarCity();
    explicit CarCardWidget(QWidget *parent = 0);
    ~CarCardWidget();
    QString carCity;
    int carMileage;


private:
    int carId;
    QString description;
    QString carBrand;
   // QString Car_city;
    Ui::CarCardWidget *ui;

};

#endif // CARCARDWIDGET_H
