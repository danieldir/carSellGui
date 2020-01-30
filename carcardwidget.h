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
    void setSetting(QString,QString,QString,int,QString,int,QString);
    QString getCarDescrition();
    QString getCarBrand();
    explicit CarCardWidget(QWidget *parent = 0);
    ~CarCardWidget();


private:
    QString description;
    QString carBrand;
    Ui::CarCardWidget *ui;

};

#endif // CARCARDWIDGET_H
