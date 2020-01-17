#include "carsell.h"
#include "ui_carsell.h"
#include <QMessageBox>
#include <map>

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


    auto liste = DBConnector::getAllMarken();
    QString item;
    while(!liste.empty()) {
        item = liste.front();
        liste.pop_front();
        ui->carBrandSearchComboBox->addItem(item);
    }

    liste = DBConnector::getAllModelle();
    while(!liste.empty()) {
        item = liste.front();
        liste.pop_front();
        ui->carModelSearchComboBox->addItem(item);
    }

    liste = DBConnector::getAllFarben();
    while(!liste.empty()) {
        item = liste.front();
        liste.pop_front();
        ui->carColorSearchCombox->addItem(item);
    }

    ui->carPriceSearchLineEdit->setValidator(new QIntValidator(0, 1000000, this));
    ui->CarPriceRegistrationLineEdit->setValidator(new QIntValidator(0, 1000000, this));
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
}

void Carsell::on_toSellCarPageButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void Carsell::on_toOwnerGalleryCars_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void Carsell::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Carsell::on_actionHome_triggered()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void Carsell::on_actionBuy_triggered()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void Carsell::on_actionGalery_triggered()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void Carsell::on_searchButton_clicked()
{
    int sPreis;
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

    auto l = DBConnector::searchCar(sMarke, sModell, sFarbe, sPreis, sKraftstoff, 0);

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
