#include "carsell.h"
#include "ui_carsell.h"
#include <QMessageBox>
#include <map>
#include <QtWidgets>
#include "carcardwidget.h"
#include "gallerycardwidget.h"
#include "QFileDialog"


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

    ui->listEmptyLabel->setStyleSheet("QLabel { background-color : white; color : black; }");

    loadSearchFacilities();

    ui->carPriceSearchLineEdit->setValidator(new QIntValidator(0, 1000000, this));
    ui->carPriceRegistrationLineEdit->setValidator(new QIntValidator(0, 1000000, this));
    ui->carMileageRegistrationLineEdit->setValidator(new QIntValidator(0, 500000, this));

    QPixmap pix(":/img/usedcar.jpg");
    ui->pixfoto->setPixmap(pix);

    QPixmap icon1(":/img/icon1-left.png");
    ui->icon1->setPixmap(icon1);

    QPixmap icon2(":/img/icons8-right.png");
    ui->icon2->setPixmap(icon2);

    QPixmap icon3(":/img/icons8-right.png");
    ui->icon3->setPixmap(icon3);

    QPixmap icon4(":/img/iconCool.png");
    ui->iconcool->setPixmap(icon4);
    

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
        userId = std::get<0>(user);

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
    ui->userNameRegistrationLineEdit->setText("");
    ui->passwordRegistrationLineEdit->setText("");
    ui->repeatPasswordRegistrationLineEdit->setText("");
    ui->registrationUsernameErrorlabel->setVisible(false);
    ui->registrationPasswordErrorlabel->setVisible(false);
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
    //    int k=0;

}

void Carsell::on_toOwnerGalleryCars_clicked()
{
    ui->SellButton->setEnabled(false);
    ui->NotSellButton->setEnabled(false);
    ui->editButton->setEnabled(false);
    ui->DeleteButton->setEnabled(false);
    int i = 0;
    ui->stackedWidget->setCurrentIndex(3);
    if (i == 0)
    {
        getCarS();
    }
}


void Carsell::on_actionHome_triggered()
{
    editMode = false;
    ui->stackedWidget->setCurrentIndex(2);
}

void Carsell::on_actionBuy_triggered()
{
    editMode = false;
    ui->stackedWidget->setCurrentIndex(5);
    loadSearchFacilities();
}

void Carsell::on_actionGalery_triggered()
{
    editMode = false;
    ui->SellButton->setEnabled(false);
    ui->NotSellButton->setEnabled(false);
    ui->editButton->setEnabled(false);
    ui->DeleteButton->setEnabled(false);
    int i = 0;
    ui->stackedWidget->setCurrentIndex(3);
    if (i == 0)
    {
        getCarS();
    }
}

void Carsell::on_searchButton_clicked()
{
    ui->carAvailableListWidget->clear();
    int sPreis = 0, sMileage = 0;
    QString sMarke, sModell, sFarbe, sKraftstoff, sCity;


    sPreis = ui->carPriceSearchLineEdit->text().toInt();
    sMarke = ui->carBrandSearchComboBox->currentText();
    sModell = ui->carModelSearchComboBox->currentText();
    sFarbe = ui->carColorSearchCombox->currentText();
    sKraftstoff = ui->carTypeSearchCombobox->currentText();
    sCity = ui->carPickPointSearchCityLineEdit->text();

    if(ui->carMileRegistrationComboBox->currentText() != "Choose a Max Mileage")
    {
        sMileage = ui->carMileRegistrationComboBox->currentText().toInt();
    }
    if(sMarke == "Choose a Brand")
    {
        sMarke = "";
    }
    if(sModell == "Choose a Model")
    {
        sModell = "";
    }
    if(sFarbe == "Choose a Color")
    {
        sFarbe = "";
    }
    if(sKraftstoff == "Choose a Type")
    {
        sKraftstoff = "";
    }


    qDebug() << sMarke << "\t" << sModell << "\t" << sFarbe << "\t" << sPreis << "\t" << sKraftstoff << "\t" << sCity << "\t" << sMileage;
    auto searchedCars = DBConnector::searchCar(sMarke, sModell, sFarbe, sPreis, sKraftstoff, userId, sCity, sMileage);
    std::tuple<int, QString, QString, QString, int, QString, int, QString, int, QString, bool> sCar;

    while (!searchedCars.empty())
    {
        sCar = searchedCars.front();
        searchedCars.pop_front();

        if(std::get<10>(sCar) == false) {
            CarCardWidget *carCard = new CarCardWidget();
            QListWidgetItem *item = new QListWidgetItem;
            carCard->setSetting(std::get<0>(sCar), std::get<1>(sCar), std::get<2>(sCar), std::get<5>(sCar), std::get<4>(sCar), std::get<7>(sCar), std::get<8>(sCar), std::get<9>(sCar));
            item->setSizeHint(QSize(300,380));

            ui->carAvailableListWidget->setViewMode(QListWidget::IconMode);
            ui->carAvailableListWidget->addItem(item);
            ui->carAvailableListWidget->setItemWidget(item, carCard);
        }
    }
}

void Carsell::on_submitRegistrationButton_clicked()
{
    QString username, password;
    ui->registrationUsernameErrorlabel->setVisible(false);
    ui->registrationPasswordErrorlabel->setVisible(false);
    if(ui->userNameRegistrationLineEdit->text() != ""){
        if(ui->passwordRegistrationLineEdit->text() == ui->repeatPasswordRegistrationLineEdit->text()) {
            username = ui->userNameRegistrationLineEdit->text();
            password = ui->passwordRegistrationLineEdit->text();

            auto duplicate = DBConnector::getUserByUsername(username);
            if(std::get<1>(duplicate) != username) {

                bool insert = DBConnector::insertUser(username, password);
                if(insert) {
                    qDebug() << "User sign up finish";
                    QMessageBox::information(this,"Sign Up", "User sign up finish");
                    ui->stackedWidget->setCurrentIndex(0);
                } else {
                    qDebug() << "insertUser() -> failed!";
                    QMessageBox::information(this,"Sign Up Error", "User sign up failed");
                }
            } else {
                qDebug() << "username is already taken";
                ui->registrationUsernameErrorlabel->setText("The username is already taken");
                ui->registrationUsernameErrorlabel->setVisible(true);
            }

        } else {
            qDebug() << "password != repeatPassword";
            ui->registrationPasswordErrorlabel->setVisible(true);
        }
    } else {
        qDebug() << "username is NULL";
        ui->registrationUsernameErrorlabel->setText("You need to fill in Username");
        ui->registrationUsernameErrorlabel->setVisible(true);
    }


}

void Carsell::on_sellCarButton_clicked()
{
    //    int sPreis, sMileage;
    QString sMarke
            //            , sModell, sFarbe, sKraftstoff, sCity, sDescription, cutDesc
            ;

    bool inserted = sellCar();
    if(inserted){
        QString sMarke = "Choose a Brand";
        QString sFarbe= "Choose a Color";
        QString sKraftstoff= "Choose a Type";

        ui->carBrandRegistrationComboBox->setCurrentText(sMarke);
        ui->carColorRegistrationCombo->setCurrentText(sFarbe);
        ui->carTypeRegistrationCombo->setCurrentText(sKraftstoff);

        //    if(sMarke== "Choose a Brand"){
        sMarke = "";
        //        }

        //    if(sFarbe == "Choose a Color") {
        sFarbe = "";
        //    }
        //    if(sKraftstoff == "Choose a Type") {
        sKraftstoff = "";
        //    }

        ui->carMileageRegistrationLineEdit->clear();
        ui->carPriceRegistrationLineEdit->clear();
        ui->carPickPointRegistrationCityLineEdit->clear();
        ui->carModelRegistrationLineEdit->clear();
        ui->plainTextEdit->clear();

        //  QMessageBox::information(this,"Sell Car", "Angabe wurde bestätigen");

        ui->stackedWidget->setCurrentIndex(2);

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


void Carsell::on_DeleteButton_clicked()
{
    QListWidgetItem *it = ui->listWidget->takeItem(ui->listWidget->currentRow());
    bool worked = DBConnector::deleteCar(cId);

    if(worked) {
        delete it;

        ui->messageLabel->setText("Car deleted");
    } else {

        ui->messageLabel->setText("Car not deleted");
        qDebug() << "Car not deleted";
    }
}


void Carsell::on_editButton_clicked()
{
    editMode = true;
    //    QListWidgetItem *it = ui->listWidget->takeItem(ui->listWidget->currentRow());

    ui->stackedWidget->setCurrentIndex(4);
    auto editCar = DBConnector::getCarById(cId);
    //std::tuple<int, QString, QString, QString, int, QString,        int,         QString, int,   QString,     bool>
    //         (carId, marke,  modell,   farbe, preis, kraftstoffart, verkaeuferid, city, mileage, description, requested);
    cBrand = std::get<1>(editCar);
    cModel = std::get<2>(editCar);
    cColor = std::get<3>(editCar);
    cPrice = std::get<4>(editCar);
    cType = std::get<5>(editCar);
    cit = std::get<7>(editCar);
    mile = std::get<8>(editCar);
    mo = std::get<9>(editCar);

    //     int j=0;
    //     if(j==0){
    ui->carBrandRegistrationComboBox->setCurrentText(cBrand);
    ui->carModelRegistrationLineEdit->setText(cModel);
    ui->carTypeRegistrationCombo->setCurrentText(cType);
    ui->carColorRegistrationCombo->setCurrentText(cColor);
    ui->carPriceRegistrationLineEdit->setText(QString::number(cPrice));
    ui->carPickPointRegistrationCityLineEdit->setText(cit);
    ui->carMileageRegistrationLineEdit->setText(QString::number(mile));
    ui->plainTextEdit->setPlainText(mo);




    //    bool work = DBConnector::insertCar(cBrand, cModel, cColor, cPrice, cType, NULL, userId, cCity, NULL, NULL);
    //    if(work) {
    //        ui->messageLabel->setText("Car edited");
    //    } else {

    //        ui->messageLabel->setText("Car not edited");
    //        qDebug() << "Car not edited";
    //    }
    //   }

    //    bool worked = DBConnector::deleteCar(cId);
    //    if(worked) {
    //        delete it;
    //       }

}

void Carsell::getCarS()
{
    ui->listWidget->clear();
    ui->listEmptyLabel->setVisible(false);
    auto getCarByUserIds = DBConnector::getCarByUserId(userId);

    std::tuple<int, QString, QString, QString, int, QString, int, QString, int, QString, bool> sl;
    if(getCarByUserIds.empty()) {
        ui->listEmptyLabel->setVisible(true);
    }
    while (!getCarByUserIds.empty())
    {
        sl = getCarByUserIds.front();
        getCarByUserIds.pop_front();

        GalleryCardWidget *galleryCard = new GalleryCardWidget();
        QListWidgetItem *item = new QListWidgetItem;
        galleryCard->setting(std::get<0>(sl), std::get<1>(sl), std::get<2>(sl), std::get<5>(sl), std::get<4>(sl));
        qDebug() << std::get<1>(sl);
        item->setSizeHint(QSize(80,80));
        ui->listWidget->setViewMode(QListWidget::ListMode);
        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item, galleryCard);
    }

}



bool Carsell::sellCar()
{
    int sPreis, sMileage;
    QString sMarke, sModell, sFarbe, sKraftstoff, sCity, sDescription, cutDesc;
    sPreis = ui->carPriceRegistrationLineEdit->text().toInt();
    sMarke = ui->carBrandRegistrationComboBox->currentText();
    sModell = ui->carModelRegistrationLineEdit->text();
    sFarbe = ui->carColorRegistrationCombo->currentText();
    sKraftstoff = ui->carTypeRegistrationCombo->currentText();
    sCity = ui->carPickPointRegistrationCityLineEdit->text();
    sMileage = ui->carMileageRegistrationLineEdit->text().toInt();
    sDescription = ui->plainTextEdit->toPlainText();


    if(sMarke == "Choose a Brand") {
        qDebug() << "No Brand chosed";
        QMessageBox::information(this,"Error", "No Brand chosed");

    } else if(sModell == "") {
        qDebug() << "No Model entered";
        QMessageBox::information(this,"Error", "No Model entered");
    } else if(sKraftstoff == "Choose a Type") {
        qDebug() << "No Type chosed";
        QMessageBox::information(this,"Error", "No Type chosed");
    } else if(sFarbe == "Choose a Color") {
        qDebug() << "No Color chosed";
        QMessageBox::information(this,"Error", "No Color chosed");
    } else if(sMileage == 0) {
        qDebug() << "No Mileage entered";
        QMessageBox::information(this,"Error", "No Mileage entered");
    } else if(sCity == "") {
        qDebug() << "No City entered";
        QMessageBox::information(this,"Error", "No City entered");
    } else if(sPreis == 0) {
        qDebug() << "No Price entered";
        QMessageBox::information(this,"Error", "No Price entered");
    } else if(sDescription == "") {
        qDebug() << "No Description entered";
        QMessageBox::information(this,"Error", "No Description entered");
    } else {
        qDebug() << sMarke << "\t" << sModell << "\t" << sFarbe << "\t" << sPreis << "\t" << sKraftstoff<< "\t" << userId<< "\t" << sCity << "\t" << sMileage << "\t" << sDescription;
        bool insert = DBConnector::insertCar(sMarke, sModell, sFarbe, sPreis, sKraftstoff, NULL, userId, sCity, sMileage, sDescription);
        if(insert) {
            qDebug() << "Car uploaded";
            QMessageBox::information(this,"Car uploaded", "Your car is now online.");
            if(editMode) {
                QListWidgetItem *it = ui->listWidget->takeItem(ui->listWidget->currentRow());
                bool worked = DBConnector::deleteCar(cId);
                if(worked) {
                    delete it;
                }
                editMode = false;
            }
            return true;
        } else {
            qDebug() << "Upload failed";
            QMessageBox::information(this,"Upload error", "Database connection failure.");
        }
    }
    return false;
}

void Carsell::on_carAvailableListWidget_itemClicked(QListWidgetItem *item)
{
    CarCardWidget *wid = qobject_cast<CarCardWidget*>(ui->carAvailableListWidget->itemWidget(item));
    QString mo = wid->getCarDescrition();
    QString mi = wid->getCarBrand();
    //    int mile = wid->getCarMileage();
    QString cit = wid->getCarCity();
    int mu = wid->getCarId();
    selectedCar *car = new selectedCar();
    car->setSetting(mo,mi,mu);
    car->exec();
}

void Carsell::on_listWidget_itemClicked(QListWidgetItem *item)
{
    ui->messageLabel->setText("");
    GalleryCardWidget *wid = qobject_cast<GalleryCardWidget*>(ui->listWidget->itemWidget(item));
    cId = wid->getCarId();
    cPrice= wid->getCarPrice();
    cModel= wid->getCarModel();
    cBrand= wid->getCarBrand();
    cType= wid->getCarType();
    //QString mo = wid->getCarDescrition();
    //int mile = wid->getCarMileage();
    // QString cit= wid->getCarcity();
    bool requested = DBConnector::getRequestedFromCar(cId);
    if(requested) {
        ui->SellButton->setEnabled(true);
        ui->NotSellButton->setEnabled(true);
    }else {
        ui->SellButton->setEnabled(false);
        ui->NotSellButton->setEnabled(false);
    }


    ui->editButton->setEnabled(true);
    ui->DeleteButton->setEnabled(true);
}

void Carsell::on_addCarImageButton_clicked()
{
    auto fileImage = QFileDialog::getOpenFileName(this,tr("Choose Image"), "/home/", tr("Image Files (*.png *.jpg *.bmp)"));
    if(!fileImage.isEmpty())
    {
        QImage imag ;
        bool valid = imag.load(fileImage);
        if(valid)
        {
            imag = imag.scaledToWidth(ui->carImagePixmap->width(), Qt::SmoothTransformation);
            ui->carImagePixmap->setPixmap(QPixmap::fromImage(imag));
        }

    }
    else
    {

    }

}

void Carsell::on_NotSellButton_clicked()
{
    DBConnector::setRequestedFromCar(cId, false);
    ui->SellButton->setEnabled(false);
    ui->NotSellButton->setEnabled(false);
    ui->messageLabel->setText("Car not sold");
}

void Carsell::on_SellButton_clicked()
{
    QListWidgetItem *it = ui->listWidget->takeItem(ui->listWidget->currentRow());
    bool worked = DBConnector::deleteCar(cId);

    if(worked) {
        delete it;

        ui->messageLabel->setText("Car sold");
    } else {

        ui->messageLabel->setText("Car not sold");
        qDebug() << "Car not deleted";
    }
}

void Carsell::on_deleteUserButton_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Delete User Account", "Are you sure you want to delete your account? All your cars will deleted too.",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        qDebug() << "Yes was clicked";
        bool deleteCar, deleteUser;
        auto userCars = DBConnector::getCarByUserId(userId);
        std::tuple<int, QString, QString, QString, int, QString, int, QString, int, QString, bool> userCar;

        while (!userCars.empty())
        {
            userCar = userCars.front();
            userCars.pop_front();

            deleteCar = DBConnector::deleteCar(std::get<0>(userCar));
            if(deleteCar) {
                qDebug() << std::get<0>(userCar) << " deleted!";
            }
        }

        deleteUser = DBConnector::deleteUser(userId);
        if(deleteUser) {
            qDebug() << "User deleted!";
        }

        ui->stackedWidget->setCurrentIndex(0);

    } else {
        qDebug() << "Yes was *not* clicked";
    }



}
