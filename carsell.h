#ifndef CARSELL_H
#define CARSELL_H

#include <QMainWindow>
#include "dbconnector.h"

namespace Ui {
class Carsell;
}

class Carsell : public QMainWindow
{
    Q_OBJECT

public:
    int userId;
    explicit Carsell(QWidget *parent = 0);
    ~Carsell();

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

    void on_plainTextEdit_textChanged();

    void on_DeleteButton_clicked();

    void getCarS();

    
    void on_editButton_clicked();

    void on_sellCarButton_pressed();

private:
    Ui::Carsell *ui;
};

#endif // CARSELL_H
