#ifndef DBCONNECTOR_H
#define DBCONNECTOR_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <iostream>
#include <map>
#include <QCryptographicHash>

class DBConnector
{
public:
    static void connectToDB();
    static std::tuple<int, QString, QString, QString, int, QString, int, QString, int, QString, bool, QString, bool> getCarById(const int id);
    static std::list<std::tuple<int, QString, QString, QString, int, QString, int, QString, int, QString, bool, QString, bool> > getCarByUserId(const int userId);
    static std::list<QString> getAllMarken();
    static std::list<QString> getAllModelle();
    static std::list<QString> getAllFarben();
    static std::tuple<int, QString, QString> getUserByUsername(const QString username);
    static std::list<std::tuple<int, int, int, int> > getAllSales();
    static std::pair<QString, QString> getUserById(const int id);
    static QString getHashByUsername(const QString username);
    static bool insertUser(const QString username, const QString password);
    static bool insertCar(const QString marke, const QString modell, const QString farbe, const int preis, const QString kraftstoffart, const QString bild,
                          const int verkaeuferid, const QString city, const int mileage, const QString description, const QString firstReg, const bool damaged);
    static int getNewId(const QString table);
    static bool deleteUser(const int idUser);
    static bool deleteCar(const int idAuto);
    static bool setRequestedFromCar(const int CarId, const bool requested);
    static bool getRequestedFromCar(const int CarId);

    static std::list<std::tuple<int, QString, QString, QString, int, QString, QByteArray,int, QString, int, QString, bool, QString, bool> > searchCar
        (QString marke, QString modell, QString farbe, int preis, QString kraftstoffart, QByteArray carByteImage, int verkaeuferid, QString city, int mileage, QString firstReg, bool damaged);
};

#endif // DBCONNECTOR_H
