#include "carsell.h"
#include "ui_carsell.h"
#include <QMessageBox>
#include <map>
#include <QtWidgets>
#include "carcardwidget.h"
#include "gallerycardwidget.h"
#include "QFileDialog"
#include <regex>


Carsell::Carsell(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Carsell)
{
    DBConnector::connectToDB();
    ui->setupUi(this);

    // default Resource Images
    QPixmap defaultImage("://defaultImage.jpg");
    QPixmap pix(":/img/usedcar.jpg");
    QPixmap carsellBackground(":/img/backgroung.jpg");
    QPixmap carsellLogo(":/img/Carsell.png");


    // default Parameter on Carsell Launch
    ui->actionLogout->setEnabled(false);
    ui->actionBuy->setEnabled(false);
    ui->actionSell->setEnabled(false);
    ui->actionDelete_Account->setEnabled(false);
    ui->actionGalery->setEnabled(false);
    ui->actionHome->setEnabled(false);
    ui->carImagePixmap->setPixmap(defaultImage.scaled(300,400,Qt::KeepAspectRatio));
    ui->carPriceSearchLineEdit->setValidator(new QIntValidator(0, 1000000, this));
    ui->carPriceRegistrationLineEdit->setValidator(new QIntValidator(0, 1000000, this));
    ui->carMileageRegistrationLineEdit->setValidator(new QIntValidator(0, 500000, this));
    ui->pixfoto->setPixmap(pix);
    ui->logoImage->setPixmap(carsellLogo.scaled(200,90,Qt::KeepAspectRatio));
    ui->backgroundCarsell->setPixmap(carsellBackground.scaled(1300,1248,Qt::KeepAspectRatio));

    //defaul Design Colors
    ui->listEmptyLabel->setStyleSheet("QLabel { background-color : white; color : black; }");
    ui->listEmptyLabel->setStyleSheet("QLabel { background-color : white; color : black; }");
    ui->carBrandRegistrationComboBox->setStyleSheet("QComboBox{ background-color : white; color : black; }");
    ui->carColorRegistrationCombo->setStyleSheet("QComboBox{ background-color : white; color : black; }");
    ui->carTypeRegistrationCombo->setStyleSheet("QComboBox { background-color : white; color : black; }");
    ui->carBrandSearchComboBox->setStyleSheet("QComboBox{ background-color : white; color : black; }");
    ui->carColorSearchCombox->setStyleSheet("QComboBox{ background-color : white; color : black; }");
    ui->carModelSearchComboBox->setStyleSheet("QComboBox { background-color : white; color : black; }");
    ui->carTypeSearchCombobox->setStyleSheet("QComboBox{ background-color : white; color : black; }");
    ui->carMileRegistrationComboBox->setStyleSheet("QComboBox{ background-color : white; color : black; }");
    ui->userNameRegistrationLineEdit->setStyleSheet("QLineEdit {padding: 1px; border-style: solid;border: 2px solid gray; border-radius: 8px; background: white; }");
    ui->passwordRegistrationLineEdit->setStyleSheet("QLineEdit {padding: 1px; border-style: solid;border: 2px solid gray; border-radius: 8px; background: white; }");
    ui->repeatPasswordRegistrationLineEdit->setStyleSheet("QLineEdit {padding: 1px; border-style: solid;border: 2px solid gray; border-radius: 8px; background: white; }");
    ui->label_9->setStyleSheet("QLabel{background-color: rgb(186, 189, 182);font-weight: bold; font-size: 15px; }");
    ui->label_10->setStyleSheet("QLabel{background-color: rgb(186, 189, 182);font-weight: bold; font-size: 15px; }");
    ui->label_11->setStyleSheet("QLabel{background-color: rgb(186, 189, 182);font-weight: bold; font-size: 15px; }");
    ui->label_13->setStyleSheet("QLabel{ background-color: rgb(186, 189, 182); font: 75 26pt URW Bookman L; }");

    loadSearchFacilities();


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
        ui->actionHome->setEnabled(true);
        ui->actionLogin->setEnabled(false);
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

void Carsell::on_actionSell_triggered()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void Carsell::on_actionAbout_Carsell_triggered()
{
    QMessageBox::about(this,"Carsell","Carsell V1.03 First Release on 2020/03/01");
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

void Carsell::on_actionHelps_triggered()
{
    QMessageBox::information(this,"Help","find Help on our webPage Carsell.com/Helps","Thanks");
}


void Carsell::on_searchButton_clicked()
{
    ui->carAvailableListWidget->clear();
    bool sDamaged;
    int sPreis = 0, sMileage = 0;
    QString sMarke, sModell, sFarbe, sKraftstoff, sCity, sFirstReg;
    QByteArray sCarImage;
    std::string stdFirstReg;

    sPreis = ui->carPriceSearchLineEdit->text().toInt();
    sMarke = ui->carBrandSearchComboBox->currentText();
    sModell = ui->carModelSearchComboBox->currentText();
    sFarbe = ui->carColorSearchCombox->currentText();
    sKraftstoff = ui->carTypeSearchCombobox->currentText();
    sCity = ui->carPickPointSearchCityLineEdit->text();
    sFirstReg = ui->carFirstRegLineEdit->text();
    stdFirstReg = sFirstReg.toStdString();
    bool regexMatch;
    const std::regex sellCarFirstReg("(19[5-9][0-9]|20([01][0-9]|20))-(0[1-9]|1[0-2])-(0[1-9]|[12][0-9]|3[01])");
    if(sFirstReg =="--"){
        regexMatch = true;
    } else {
        regexMatch = std::regex_match(stdFirstReg, sellCarFirstReg);
        qDebug() << "Regex Match: " << regexMatch;
    }
    if(ui->damagedCheckBox->isChecked()) {
        sDamaged = true;
    } else {
        sDamaged = false;
    }

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

    if(regexMatch) {
        qDebug() << sMarke << "\t" << sModell << "\t" << sFarbe << "\t" << sPreis << "\t" << sKraftstoff << "\t" << sCity << "\t" << sMileage << "\t" << sFirstReg << "\t" << sDamaged;
        auto searchedCars = DBConnector::searchCar(sMarke, sModell, sFarbe, sPreis, sKraftstoff,sCarImage, userId, sCity, sMileage, sFirstReg, sDamaged);
        std::tuple<int, QString, QString, QString, int, QString,QByteArray, int, QString, int, QString, bool, QString, bool> sCar;

        while (!searchedCars.empty())
        {
            sCar = searchedCars.front();
            searchedCars.pop_front();

            if(std::get<11>(sCar) == false) {
                CarCardWidget *carCard = new CarCardWidget();
                QListWidgetItem *item = new QListWidgetItem;
                carCard->setSetting(std::get<0>(sCar), std::get<6>(sCar), std::get<1>(sCar), std::get<2>(sCar), std::get<5>(sCar), std::get<4>(sCar), std::get<8>(sCar), std::get<9>(sCar), std::get<10>(sCar));
                item->setSizeHint(QSize(300,380));

                ui->carAvailableListWidget->setViewMode(QListWidget::IconMode);
                ui->carAvailableListWidget->addItem(item);
                ui->carAvailableListWidget->setItemWidget(item, carCard);
            }
        }

    } else {

        qDebug() << "First Registration unrealistic";
        QMessageBox::information(this,"Error", "First registration is unrealistic");
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
        ui->carFirstRegistrationLineEdit->clear();
        ui->carImagePixmap->clear();

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

    ui->stackedWidget->setCurrentIndex(4);
    auto editCar = DBConnector::getCarById(cId);

    cBrand = std::get<1>(editCar);
    cModel = std::get<2>(editCar);
    cColor = std::get<3>(editCar);
    cPrice = std::get<4>(editCar);
    cType = std::get<5>(editCar);
    cit = std::get<7>(editCar);
    mile = std::get<8>(editCar);
    mo = std::get<9>(editCar);
    cFirstReg = std::get<11>(editCar);


    ui->carBrandRegistrationComboBox->setCurrentText(cBrand);
    ui->carModelRegistrationLineEdit->setText(cModel);
    ui->carTypeRegistrationCombo->setCurrentText(cType);
    ui->carColorRegistrationCombo->setCurrentText(cColor);
    ui->carPriceRegistrationLineEdit->setText(QString::number(cPrice));
    ui->carPickPointRegistrationCityLineEdit->setText(cit);
    ui->carMileageRegistrationLineEdit->setText(QString::number(mile));
    ui->plainTextEdit->setPlainText(mo);
    ui->carFirstRegistrationLineEdit->setText(cFirstReg);


}

void Carsell::getCarS()
{
    ui->listWidget->clear();
    ui->listEmptyLabel->setVisible(false);
    auto getCarByUserIds = DBConnector::getCarByUserId(userId);

    std::tuple<int, QString, QString, QString, int, QString, int, QString, int, QString, bool, QString, bool, QByteArray> sl;
    if(getCarByUserIds.empty()) {
        ui->listEmptyLabel->setVisible(true);
    }
    while (!getCarByUserIds.empty())
    {
        sl = getCarByUserIds.front();
        getCarByUserIds.pop_front();

        GalleryCardWidget *galleryCard = new GalleryCardWidget();
        QListWidgetItem *item = new QListWidgetItem;
        galleryCard->setting(std::get<0>(sl), std::get<1>(sl), std::get<2>(sl), std::get<5>(sl), std::get<4>(sl), std::get<13>(sl));
        qDebug() << std::get<1>(sl);
        item->setSizeHint(QSize(80,80));
        ui->listWidget->setViewMode(QListWidget::ListMode);
        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item, galleryCard);
    }

}

bool Carsell::sellCar()
{
    bool sDamaged;
    int sPreis, sMileage;
    QString sMarke, sModell, sFarbe, sKraftstoff, sCity, sDescription, sFirstReg;
    const QPixmap *currentImage;
    QByteArray bytes;
    bool regexMatch;
    std::string stdFirstReg;

    currentImage = ui->carImagePixmap->pixmap();
    sPreis = ui->carPriceRegistrationLineEdit->text().toInt();
    sMarke = ui->carBrandRegistrationComboBox->currentText();
    sModell = ui->carModelRegistrationLineEdit->text();
    sFarbe = ui->carColorRegistrationCombo->currentText();
    sKraftstoff = ui->carTypeRegistrationCombo->currentText();
    sCity = ui->carPickPointRegistrationCityLineEdit->text();
    sMileage = ui->carMileageRegistrationLineEdit->text().toInt();
    sDescription = ui->plainTextEdit->toPlainText();
    sFirstReg = ui->carFirstRegistrationLineEdit->text();
    stdFirstReg = sFirstReg.toStdString();


    //convert Image To Byte
    QBuffer buffer(&bytes);
    buffer.open(QIODevice::WriteOnly);
    currentImage->save(&buffer, "JPG");

    const std::regex sellCarFirstReg("(19[5-9][0-9]|20([01][0-9]|20))-(0[1-9]|1[0-2])-(0[1-9]|[12][0-9]|3[01])");
    if(sFirstReg =="--"){
        regexMatch = true;
    } else {
        regexMatch = std::regex_match(stdFirstReg, sellCarFirstReg);
        qDebug() << "Regex Match: " << regexMatch;
    }
    if(ui->damagedRadioButton->isChecked()) {
        sDamaged = true;
    } else {
        sDamaged = false;
    }
    //Error messages
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
    } else if(sFirstReg == "--") {
        qDebug() << "No First Registration entered";
        QMessageBox::information(this,"Error", "First registration not entered");
    } else if(!regexMatch) {
        qDebug() << "First Registration unrealistic";
        QMessageBox::information(this,"Error", "First registration is unrealistic");
    } else
    {
        qDebug() << sMarke << "\t" << sModell << "\t" << sFarbe << "\t" << sPreis << "\t" << sKraftstoff<< "\t" << userId<< "\t" << sCity << "\t" << sMileage << "\t" << sDescription << "\t" << sFirstReg << "\t" << sDamaged;
        bool insert = DBConnector::insertCar(sMarke, sModell, sFarbe, sPreis, sKraftstoff, bytes, userId, sCity, sMileage, sDescription, sFirstReg, sDamaged);
        if(insert)
        {
            qDebug() << "Car uploaded";
            QMessageBox::information(this,"Car uploaded", "Your car is now online.");
            if(editMode)
            {
                QListWidgetItem *it = ui->listWidget->takeItem(ui->listWidget->currentRow());
                bool worked = DBConnector::deleteCar(cId);
                if(worked)
                {
                    delete it;
                }
                editMode = false;
            }
            return true;
        }
        else
        {
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
    auto fileImage = QFileDialog::getOpenFileName(this,tr("Choose Image"), "/home/", tr("Image Files (*.jpg)"));
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
        return;
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
        std::tuple<int, QString, QString, QString, int, QString, int, QString, int, QString, bool, QString, bool, QByteArray> userCar;

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
