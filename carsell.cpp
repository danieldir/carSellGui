#include "carsell.h"
#include "ui_carsell.h"
#include <QMessageBox>
#include <map>
#include <QtWidgets>
#include "carcardwidget.h"


Carsell::Carsell(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Carsell)
{
    DBConnector::connectToDB();
    ui->setupUi(this);
    ui->actionLogout->setEnabled(false);
    ui->actionBuy->setEnabled(false);
    ui->actionSell->setEnabled(false);
    ui->actionDelete_Account->setEnabled(false);
    ui->actionGalery->setEnabled(false);
    ui->actionParameter->setEnabled(false);
    ui->actionHome->setEnabled(false);
    ui->carListGridLayout->setColumnStretch(2,10);
    ui->carListGridLayout->setRowStretch(2,10);


    loadSearchFacilities();

    ui->carPriceSearchLineEdit->setValidator(new QIntValidator(0, 1000000, this));
    ui->carPriceRegistrationLineEdit->setValidator(new QIntValidator(0, 1000000, this));

    QPixmap pix("/home/jovine/Projekt/usedcar.jpg");
    ui->pixfoto->setPixmap(pix);

    QPixmap icon1("/home/jovine/Projekt/icon1.png");
    ui->icon1->setPixmap(icon1);

    QPixmap icon2("/home/jovine/Projekt/icon2.png");
    ui->icon2->setPixmap(icon2);

    QPixmap icon3("/home/jovine/Projekt/icon2.png");
    ui->icon3->setPixmap(icon3);

    QPixmap icon4("/home/jovine/Projekt/iconcool.png");
    ui->labelIcon->setPixmap(icon4);


}

Carsell::~Carsell()
{
    delete ui;
}


void Carsell::on_loginButton_clicked()
{
    QString
            username = ui->userNameLineEdit->text(),
            password = ui->passwordLineEdit->text();

    auto user = DBConnector::getUserByUsername(username);
    QString password_hash = QCryptographicHash::hash(
                QByteArray::fromStdString(password.toStdString()),
                QCryptographicHash::RealSha3_256).toBase64();

    if(std::get<2>(user) == password_hash) {
        ui->userNameLineEdit->setText("");
        ui->passwordLineEdit->setText("");
        ui->userSalutation->setText("Welcome " + username);
        ui->stackedWidget->setCurrentIndex(2);

        // Activation of Menu Tools and Tabbar Button
        ui->actionLogout->setEnabled(true);
        ui->actionBuy->setEnabled(true);
        ui->actionSell->setEnabled(true);
        ui->actionDelete_Account->setEnabled(true);
        ui->actionGalery->setEnabled(true);
        ui->actionParameter->setEnabled(true);
        ui->actionHome->setEnabled(true);
        ui->actionLogin->setEnabled(false);
        ui->actionSignUp->setEnabled(false);
    }
    else if( username.isEmpty() )
    {
        ui->identificationStatusLabel->setText("Please Enter your Username");
    }
    else if( password.isEmpty() )
    {
        ui->identificationStatusLabel->setText("Please Enter your Password");
    }
    else
    {
        ui->identificationStatusLabel->setText("Username or Password Incorrect please try again !");

    }
}

void Carsell::on_signUpButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Carsell::on_actionExit_triggered()
{
    this->close();
}

void Carsell::on_actionLogin_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Carsell::on_actionLogout_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Carsell::on_toBuyCarPageButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    loadSearchFacilities();
}

void Carsell::on_toSellCarPageButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void Carsell::on_toOwnerGalleryCars_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}



void Carsell::on_actionHome_triggered()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void Carsell::on_actionBuy_triggered()
{
    ui->stackedWidget->setCurrentIndex(5);
    loadSearchFacilities();
}

void Carsell::on_actionGalery_triggered()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void Carsell::on_searchButton_clicked()
{
    int sPreis = 0;
    QString sMarke, sModell, sFarbe, sKraftstoff;
    sPreis = ui->carPriceSearchLineEdit->text().toInt();
    sMarke = ui->carBrandSearchComboBox->currentText();
    sModell = ui->carModelSearchComboBox->currentText();
    sFarbe = ui->carColorSearchCombox->currentText();
    sKraftstoff = ui->carTypeSearchCombobox->currentText();
    if(sMarke == "Choose a Brand") {
        sMarke = "";
    }
    if(sModell == "Choose a Model") {
        sModell = "";
    }
    if(sFarbe == "Choose a Color") {
        sFarbe = "";
    }
    if(sKraftstoff == "Choose a Type") {
        sKraftstoff = "";
    }
    qDebug() << sMarke << "\t" << sModell << "\t" << sFarbe << "\t" << sPreis << "\t" << sKraftstoff;
    auto searchedCars = DBConnector::searchCar(sMarke, sModell, sFarbe, sPreis, sKraftstoff, 0);
    //    int searchedCarsSize = searchedCars.size();

         // to do : print card in a scrollbar and use a loop to print all available car
         ui->carListGridLayout->addWidget(new CarCardWidget);

}

void Carsell::on_submitRegistrationButton_clicked()
{
    QString username, password;
    if(ui->userNameRegistrationLineEdit->text() != ""){
        if(ui->passwordRegistrationLineEdit->text() == ui->repeatPasswordRegistrationLineEdit->text()) {
            username = ui->userNameRegistrationLineEdit->text();
            password = ui->passwordRegistrationLineEdit->text();
            bool insert = DBConnector::insertUser(username, password);
            if(insert) {
                qDebug() << "User sign up finish";
                ui->stackedWidget->setCurrentIndex(0);
            } else {
                qDebug() << "insertUser() -> failed!";
            }
        } else {
            qDebug() << "password != repeatPassword"; //TODO: Label für User einfügen damit User sieht was der Fehler ist
        }
    } else {
        qDebug() << "username is NULL"; //TODO: Label einfügen
    }



}

void Carsell::on_sellCarButton_clicked()
{
    int sPreis;
    QString sMarke, sModell, sFarbe, sKraftstoff;
    sPreis = ui->carPriceRegistrationLineEdit->text().toInt();
    sMarke = ui->carBrandRegistrationComboBox->currentText();
    sModell = ui->carModelRegistrationLineEdit->text();
    sFarbe = ui->carColorRegistrationCombo->currentText();
    sKraftstoff = ui->carTypeRegistrationCombo->currentText();

    if(sMarke == "Choose a Brand") {
        qDebug() << "No Brand chosed";
    } else if(sModell == "") {
        qDebug() << "No Model entered";
    } else if(sFarbe == "Choose a Color") {
        qDebug() << "No Color chosed";
    } else if(sKraftstoff == "Choose a Type") {
        qDebug() << "No Type chosed";
    } else if(sPreis == 0) {
        qDebug() << "No Price entered";
    } else {
        qDebug() << sMarke << "\t" << sModell << "\t" << sFarbe << "\t" << sPreis << "\t" << sKraftstoff;
        bool insert = DBConnector::insertCar(sMarke, sModell, sFarbe, sPreis, sKraftstoff, NULL, 5);
        if(insert) {
            qDebug() << "Car uploaded";
        } else {
            qDebug() << "Upload failed";
        }
    }
}






void Carsell::loadSearchFacilities()
{
    auto liste = DBConnector::getAllMarken();
    QString item;
    ui->carBrandSearchComboBox->clear();
    ui->carBrandSearchComboBox->addItem("Choose a Brand");
    while(!liste.empty()) {
        item = liste.front();
        liste.pop_front();
        ui->carBrandSearchComboBox->addItem(item);
    }

    liste = DBConnector::getAllModelle();
    ui->carModelSearchComboBox->clear();
    ui->carModelSearchComboBox->addItem("Choose a Model");
    while(!liste.empty()) {
        item = liste.front();
        liste.pop_front();
        ui->carModelSearchComboBox->addItem(item);
    }

    liste = DBConnector::getAllFarben();
    ui->carColorSearchCombox->clear();
    ui->carColorSearchCombox->addItem("Choose a Color");
    while(!liste.empty()) {
        item = liste.front();
        liste.pop_front();
        ui->carColorSearchCombox->addItem(item);
    }
}

void Carsell::on_goBack_Button_clicked()
{
   ui->stackedWidget->setCurrentIndex(0);
}
