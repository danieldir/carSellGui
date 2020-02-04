#include "dbconnector.h"
void DBConnector::connectToDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("remotemysql.com");
    db.setPort(3306);
    db.setDatabaseName("pztczcJad0");
    db.setUserName("pztczcJad0");
    db.setPassword("F522g2piJ5");
    if(db.open()) {
        std::cout << "DB connected!" << std::endl;
    } else {
        std::cout << "DB not connected!" << std::endl;
    }

}

std::tuple<int, QString, QString, QString, int, QString, int, QString, int, QString, bool, QString, bool> DBConnector::getCarById(const int id) {
    bool requested, damaged;
    int carId, preis, verkaeuferid, mileage;
    QString marke, modell, farbe, kraftstoffart, city, description, firstReg;
    QSqlQuery query;
    std::tuple<int, QString, QString, QString, int, QString, int, QString, int, QString, bool, QString, bool> car;
    query.prepare("SELECT * FROM Auto WHERE idAuto = :autoId");
    query.bindValue(":autoId", id);
    query.exec();
    query.next();

    if(query.size() == 0) {
        qDebug() << "Car not found";
        return std::tuple<int, QString, QString, QString, int, QString, int, QString, int, QString, bool, QString, bool>();
    }
    carId = query.value(0).toInt();
    marke = query.value(1).toString();
    modell = query.value(2).toString();
    farbe = query.value(3).toString();
    preis = query.value(4).toInt();
    kraftstoffart = query.value(5).toString();
    verkaeuferid = query.value(7).toInt();
    city = query.value(8).toString();
    mileage = query.value(9).toInt();
    description = query.value(10).toString();
    requested = query.value(11).toBool();
    firstReg = query.value(12).toString();
    damaged = query.value(13).toBool();
    qDebug() << carId << "\t" << marke << "\t" << modell << "\t" << farbe << "\t" << preis << "\t" << kraftstoffart << "\t" << verkaeuferid << "\t" << city << "\t" << mileage << "\t" << description << "\t" << requested << "\t" << firstReg << "\t" << damaged;

    return std::tuple<int, QString, QString, QString, int, QString, int, QString, int, QString, bool, QString, bool>(carId, marke, modell, farbe, preis, kraftstoffart, verkaeuferid, city, mileage, description, requested, firstReg, damaged);
}

std::list<std::tuple<int, QString, QString, QString, int, QString, int, QString, int, QString, bool, QString, bool> > DBConnector::getCarByUserId(const int userId) {
    bool requested, damaged;
    int id, preis, verkaeuferid, mileage;
    QString marke, modell, farbe, kraftstoffart, city, description, firstReg;
    QSqlQuery query;
    std::list<std::tuple<int, QString, QString, QString, int, QString, int, QString, int, QString, bool, QString, bool> > l;
    query.prepare("SELECT * FROM Auto WHERE Verkaeufer = :userId");
    query.bindValue(":userId", userId);
    query.exec();
    while(query.next()) {
        id = query.value(0).toInt();
        marke = query.value(1).toString();
        modell = query.value(2).toString();
        farbe = query.value(3).toString();
        preis = query.value(4).toInt();
        kraftstoffart = query.value(5).toString();
        verkaeuferid = query.value(7).toInt();
        city = query.value(8).toString();
        mileage = query.value(9).toInt();
        description = query.value(10).toString();
        requested = query.value(11).toBool();
        firstReg = query.value(12).toString();
        damaged = query.value(13).toBool();
        qDebug() << id << "\t" << marke << "\t" << modell << "\t" << farbe << "\t" << preis << "\t" << kraftstoffart << "\t" << verkaeuferid << "\t" << city << "\t" << mileage << "\t" << description << "\t" << requested << "\t" << firstReg << "\t" << damaged;
        l.push_back(std::tuple<int, QString, QString, QString, int, QString, int, QString, int, QString, bool, QString, bool>(id, marke, modell, farbe, preis, kraftstoffart, verkaeuferid, city, mileage, description, requested, firstReg, damaged));
    }
    if(l.empty()) {      
        qDebug() << "No Cars for this userId found";
    }
    return l;
}

std::list<QString> DBConnector::getAllMarken() {
    QString marke;
    QSqlQuery query;
    std::list<QString> l;
    query.exec("SELECT DISTINCT Marke FROM Auto");
    while(query.next()) {
        marke = query.value(0).toString();
        //        qDebug() << marke;
        l.push_back(marke);
    }
    l.sort();
    return l;
}

std::list<QString> DBConnector::getAllModelle() {
    QString modell;
    QSqlQuery query;
    std::list<QString> l;
    query.exec("SELECT DISTINCT Modell FROM Auto");
    while(query.next()) {
        modell = query.value(0).toString();
        //        qDebug() << modell;
        l.push_back(modell);
    }
    l.sort();
    return l;
}

std::list<QString> DBConnector::getAllFarben() {
    QString farbe;
    QSqlQuery query;
    std::list<QString> l;
    query.exec("SELECT DISTINCT Farbe FROM Auto");
    while(query.next()) {
        farbe = query.value(0).toString();
        //        qDebug() << farbe;
        l.push_back(farbe);
    }
    l.sort();
    return l;
}
std::tuple<int, QString, QString> DBConnector::getUserByUsername(const QString username){
    int id;
    QString hash;
    QSqlQuery query;
    query.prepare("SELECT * FROM User WHERE Username = :username");
    query.bindValue(":username", username);
    query.exec();
    query.next();
    if(query.size() == 0) {
        qDebug() << "User don't found";
        return std::tuple<int, QString, QString> ();
    }
    id = query.value(0).toInt();
    hash = query.value(2).toString();
    return std::tuple<int, QString, QString> (id, username, hash);



}

std::list<std::tuple<int, int, int, int> > DBConnector::getAllSales() {
    int idVerkauf, autoid, verkaeufer, kaeufer;
    QSqlQuery query;
    std::list<std::tuple<int, int, int, int> > l;
    query.exec("SELECT * FROM Verkauf");
    while(query.next()) {
        idVerkauf = query.value(0).toInt();
        autoid = query.value(1).toInt();
        verkaeufer = query.value(2).toInt();
        kaeufer = query.value(3).toInt();
        qDebug() << idVerkauf << "\t" << autoid << "\t" << verkaeufer << "\t" << kaeufer;
        l.push_back(std::tuple<int, int, int, int>(idVerkauf, autoid, verkaeufer, kaeufer));
    }
    return l;
}

std::pair<QString, QString> DBConnector::getUserById(const int id) {
    QString username, hash;
    QSqlQuery query;
    query.prepare("select * from User where idUser = :idinput");
    query.bindValue(":idinput", id);
    query.exec();
    query.next();
    if(query.isNull(id)) {
        qDebug() << "No User with this id!";
        return std::pair<QString, QString> ();
    }
    username = query.value(1).toString();
    hash = query.value(2).toString();
    qDebug() << username << hash;
    return std::pair<QString, QString> (username, hash);
}

QString DBConnector::getHashByUsername(const QString username) {
    QSqlQuery query;
    query.prepare("select * from User where idUser = :usernameinput");
    query.bindValue(":usernameinput", username);
    query.exec();
    query.next();
    if(query.isNull(username)) {
        return NULL;
    }
    return query.value(2).toString();
}

bool DBConnector::insertUser(const QString username, const QString password) {
    QSqlQuery query;
    int id = getNewId("User");

    QString password_hash = QCryptographicHash::hash(
                QByteArray::fromStdString(password.toStdString()),
                QCryptographicHash::RealSha3_256).toBase64();

    query.prepare("INSERT INTO User (idUser, Username, passwort_hash) "
                  "VALUES (:idinput, :usernameinput, :hashinput)");
    query.bindValue(":idinput", id);
    query.bindValue(":usernameinput", username);
    query.bindValue(":hashinput", password_hash);
    return query.exec();
}

bool DBConnector::insertCar(const QString marke, const QString modell, const QString farbe, const int preis, const QString kraftstoffart,
                            const QString bild, const int verkaeuferid, const QString city, const int mileage, const QString description, const QString firstReg, const bool damaged) {
    QSqlQuery query;
    int id = getNewId("Auto");

    query.prepare("INSERT INTO Auto (idAuto, Marke, Modell, Farbe, Preis, Kraftstoffart, Bild, Verkaeufer, City, Mileage, Description, requested, firstRegistration, damaged)"
                  "VALUES (:id, :marke, :modell, :farbe, :preis, :kraftstoff, :bild, :verkaeufer, :city, :mileage, :description, 0, :firstReg, :damaged)");
    query.bindValue(":id", id);
    query.bindValue(":marke", marke);
    query.bindValue(":modell", modell);
    query.bindValue(":farbe", farbe);
    query.bindValue(":preis", preis);
    query.bindValue(":kraftstoff", kraftstoffart);
    query.bindValue(":bild", bild);
    query.bindValue(":verkaeufer", verkaeuferid);
    query.bindValue(":city", city);
    query.bindValue(":mileage", mileage);
    query.bindValue(":description", description);
    query.bindValue(":firstReg", firstReg);
    query.bindValue(":damaged", damaged);
    return query.exec();
}

int DBConnector::getNewId(const QString table) {
    int id;
    QSqlQuery query;

    if(table == "User")
        query.prepare("SELECT MAX(idUser) FROM User");
    else if(table == "Auto")
        query.prepare("SELECT MAX(idAuto) FROM Auto");
    else
        qDebug() << "Tabelle nicht gefunden";

    query.exec();
    while(query.next())
        id = query.value(0).toInt();
    return ++id;
}

bool DBConnector::deleteUser(const int idUser) {
    QSqlQuery query;
    query.prepare("DELETE FROM User WHERE idUser = :id");
    query.bindValue(":id", idUser);
    return query.exec();
}

bool DBConnector::deleteCar(const int idAuto) {
    QSqlQuery query;
    query.prepare("DELETE FROM Auto WHERE idAuto = :id");
    query.bindValue(":id", idAuto);
    return query.exec();
}


bool DBConnector::setRequestedFromCar(const int CarId, const bool requested) {
    int requestedInt;
    QSqlQuery query;
    if(requested) {
        requestedInt = 1;
    } else {
        requestedInt = 0;
    }
    query.prepare("UPDATE `Auto` SET `requested` = :req WHERE `Auto`.`idAuto` = :id");
    query.bindValue(":id", CarId);
    query.bindValue(":req", requestedInt);
    return query.exec();
}

bool DBConnector::getRequestedFromCar(const int CarId) {
    QSqlQuery query;
    query.prepare("SELECT requested FROM Auto WHERE idAuto = :id");
    query.bindValue(":id", CarId);
    query.exec();
    query.next();
    int req = query.value(0).toInt();
    return req;
}

std::list<std::tuple<int, QString, QString, QString, int, QString, int, QString, int, QString, bool, QString, bool> > DBConnector::searchCar
(QString marke, QString modell, QString farbe, int preis, QString kraftstoffart, int verkaeuferid,  QString city, int mileage, QString firstReg, bool damaged)
{
    int id = 0;
    QString description;
    bool requested = false;
    QString queryString = "SELECT * FROM Auto WHERE ";
    QSqlQuery query;
    std::list<std::tuple<int, QString, QString, QString, int, QString, int, QString, int, QString, bool, QString, bool> > l;

    qDebug() << id << "\t" << marke << "\t" << modell << "\t" << farbe << "\t" << preis << "\t" << kraftstoffart << "\t" << verkaeuferid << "\t" << city << "\t" << mileage << "\t" << description << "\t" << requested << "\t" << firstReg << "\t" << damaged;

    if(marke == NULL) {
        queryString.append("Marke = Marke ");
    } else {
        queryString.append("Marke = :marke ");
    }

    if(modell == NULL) {
        queryString.append("AND Modell = Modell ");
    } else {
        queryString.append("AND Modell = :modell ");
    }

    if(farbe == NULL) {
        queryString.append("AND Farbe = Farbe ");
    } else {
        queryString.append("AND Farbe = :farbe ");
    }

    if(preis != 0) {
        queryString.append("AND Preis BETWEEN 0 AND :preis ");
    }

    if(kraftstoffart == NULL) {
        queryString.append("AND Kraftstoffart = Kraftstoffart ");
    } else {
        queryString.append("AND Kraftstoffart = :kraftstoff ");
    }

    if(verkaeuferid == 0) {
        queryString.append("AND Verkaeufer = Verkaeufer ");
    } else {
        queryString.append("AND Verkaeufer <> :verkaeufer ");
    }

    if(city != NULL) {
        queryString.append("AND City = :city ");
    }

    if(mileage != 0) {
        queryString.append("AND Mileage BETWEEN 0 AND :mileage ");
    }

    if(firstReg != "--") {
        queryString.append("AND firstRegistration >= :firstReg");
    }

    if(!damaged) {
        queryString.append("AND NOT damaged");
    }

    query.prepare(queryString);
    query.bindValue(":marke", marke);
    query.bindValue(":modell", modell);
    query.bindValue(":farbe", farbe);
    query.bindValue(":preis", preis);
    query.bindValue(":kraftstoff", kraftstoffart);
    query.bindValue(":verkaeufer", verkaeuferid);
    query.bindValue(":city", city);
    query.bindValue(":mileage", mileage);
    query.bindValue(":firstReg", firstReg);
    query.exec();

    while(query.next())
    {
        id = query.value(0).toInt();
        marke = query.value(1).toString();
        modell = query.value(2).toString();
        farbe = query.value(3).toString();
        preis = query.value(4).toInt();
        kraftstoffart = query.value(5).toString();
        verkaeuferid = query.value(7).toInt();
        city = query.value(8).toString();
        mileage = query.value(9).toInt();
        description = query.value(10).toString();
        requested = query.value(11).toBool();
        firstReg = query.value(12).toString();
        damaged = query.value(13).toBool();
        qDebug() << id << "\t" << marke << "\t" << modell << "\t" << farbe << "\t" << preis << "\t" << kraftstoffart << "\t" << verkaeuferid << "\t" << city << "\t" << mileage << "\t" << description << "\t" << requested << "\t" << firstReg << "\t" << damaged;
        l.push_back(std::tuple<int, QString, QString, QString, int, QString, int, QString, int, QString, bool, QString, bool>(id, marke, modell, farbe, preis, kraftstoffart, verkaeuferid, city, mileage, description, requested, firstReg, damaged));
    }
    if(l.empty()) {
        qDebug() << "No Cars found";
    }
    return l;
}
