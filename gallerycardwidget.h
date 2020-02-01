#ifndef GALLERYCARDWIDGET_H
#define GALLERYCARDWIDGET_H

#include <QWidget>

namespace Ui {
class GalleryCardWidget;
}

class GalleryCardWidget : public QWidget
{
    Q_OBJECT

public:
    void setting(int, QString, QString, QString, int);
    int getCarId();
    QString getCarModel();
    QString getCarType();
    QString getCarcolor();
    QString getCarcity();
    QString getCarBrand();
    QString getCarDescrition();
    int getCarMileage();
    int getCarPrice();
    int cId;
    QString cColor;
    QString cCity;
    QString car_description;
    QString cBrand;
    QString cModel;
    int cPrice;
    QString labelPrice;
    int cMileage;
    QString cType;
    int mile;
    QString cit;
    QString mo;
    explicit GalleryCardWidget(QWidget *parent = 0);
    ~GalleryCardWidget();

private:
    Ui::GalleryCardWidget *ui;

};

#endif // GALLERYCARDWIDGET_H
