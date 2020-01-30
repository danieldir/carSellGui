#ifndef SELECTEDCAR_H
#define SELECTEDCAR_H

#include <QDialog>
#include "dbconnector.h"

namespace Ui {
class selectedCar;
}

class selectedCar : public QDialog
{
    Q_OBJECT

public:
    explicit selectedCar(QWidget *parent = 0);
    ~selectedCar();
    void setSetting(QString decription, QString brand, int id);

private slots:
    void on_buyButton_clicked();
    void on_cancelButton_clicked();

private:
    int IdCar;
    Ui::selectedCar *ui;
};

#endif // SELECTEDCAR_H
