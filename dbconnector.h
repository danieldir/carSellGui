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
    static std::list<std::tuple<int, QString, QString, QString, int, QString, int> > getAllCars();
    static std::list<QString> getAllMarken();
    static std::list<QString> getAllModelle();
    static std::list<QString> getAllFarben();
    static std::map<int,std::pair<QString, QString> > getAllUsers();
    static std::list<std::tuple<int, int, int, int> > getAllSales();
    static std::pair<QString, QString> getUserById(const int id);
    static QString getHashByUsername(const QString username);
    //std::tuple<int, int, int ,int> getVerkaufById(const int id);
    static bool insertUser(const QString username, const QString password);
    static bool insertCar(const QString marke, const QString modell, const QString farbe, const int preis, const QString kraftstoffart, const QString bild, const int verkaeuferid);
    static int getNewId(const QString table);
    static bool deleteUser(const int idUser);
    static bool deleteCar(const int idAuto);
    static std::list<std::tuple<int, QString, QString, QString, int, QString, int> > searchCar
    (QString marke, QString modell, QString farbe, int preis, QString kraftstoffart, int verkaeuferid);
};

#endif // DBCONNECTOR_H
