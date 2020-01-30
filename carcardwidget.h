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
    explicit CarCardWidget(QWidget *parent = 0);
    ~CarCardWidget();


private:
    int carId;
    QString description;
    QString carBrand;
    Ui::CarCardWidget *ui;

};

#endif // CARCARDWIDGET_H
