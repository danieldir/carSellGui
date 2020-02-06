#ifndef CARSELL_H
#define CARSELL_H

#include <QMainWindow>
#include "dbconnector.h"
#include<QListWidgetItem>

namespace Ui {
class Carsell;
}

class Carsell : public QMainWindow
{
    Q_OBJECT

public:
    bool editMode;
    int cId;
    int userId;
    QString cColor;
    QString cCity;
    QString car_description;
    QString cBrand;
    QString cModel;
    QString cFirstReg;
    int cPrice;
    QString labelPrice;
    //int cMileage;
    QString cType;
    explicit Carsell(QWidget *parent = 0);
    ~Carsell();
    QString carCity;
    int carMileage;
    int mile;
    QString cit;
    QString mo;

private slots:
    void on_loginButton_clicked();

    void on_signUpButton_clicked();

    void on_actionExit_triggered();

    void on_actionLogin_triggered();

    void on_actionLogout_triggered();

    void on_toBuyCarPageButton_clicked();

    void on_toSellCarPageButton_clicked();

    void on_toOwnerGalleryCars_clicked();

    void on_actionHome_triggered();

    void on_actionBuy_triggered();

    void on_actionGalery_triggered();

    void on_searchButton_clicked();

    void on_submitRegistrationButton_clicked();

    void on_sellCarButton_clicked();

    void loadSearchFacilities();

    void on_goBack_Button_clicked();

    void on_DeleteButton_clicked();

    void getCarS();

    bool sellCar();

    void on_editButton_clicked();

    void on_carAvailableListWidget_itemClicked(QListWidgetItem *item);

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_addCarImageButton_clicked();

    void on_NotSellButton_clicked();

    void on_SellButton_clicked();

    void on_deleteUserButton_clicked();

private:
    Ui::Carsell *ui;
};

#endif // CARSELL_H
