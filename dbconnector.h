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
    DBConnector();
//    std::list<std::tuple<int, QString, QString, QString, int, QString, int> > getAllCars();
//    std::list<QString> getAllMarken();
//    std::list<QString> getAllModelle();
//    std::list<QString> getAllFarben();
//    std::map<int,std::pair<QString, QString> > getAllUsers();
//    std::list<std::tuple<int, int, int, int> > getAllSales();
//    std::pair<QString, QString> getUserById(const int id);
//    QString getHashByUsername(const QString username);
//    //std::tuple<int, int, int ,int> getVerkaufById(const int id);
//    bool insertUser(const QString username, const QString password);
//    bool insertCar(const QString marke, const QString modell, const QString farbe, const int preis, const QString kraftstoffart, const QString bild, const int verkaeuferid);
//    int getNewId(const QString table);
//    bool deleteUser(const int idUser);
//    bool deleteCar(const int idAuto);
//    std::list<std::tuple<int, QString, QString, QString, int, QString, int> > searchCar
//    (QString marke, QString modell, QString farbe, int preis, QString kraftstoffart, int verkaeuferid);
      bool checkUser(const QString username, const QString password);
};

#endif // DBCONNECTOR_H
