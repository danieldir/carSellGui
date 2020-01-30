#include "carsell.h"
#include <QApplication>

int main(int argc, char *argv[])
{
//    DBConnector::connectToDB();

    QApplication a(argc, argv);
    Carsell w;
    w.show();

    //tests
//    DBConnector::searchCar(NULL, NULL, NULL, 0, "", 0, "", 2000); //Test: Auto suchen (Null bei String / 0 bei int wenn Wert egal)
//    qDebug() << "Insert Car: " << DBConnector::insertCar("Aston Martin", "DB9", "Grey", 63000, "Petrol", NULL, 5, "Frankfurt", 42000, "James Bond wan't to sell his car."); //Test: Auto einfügen
//    auto user = DBConnector::getUserByUsername("Daniel");
//    auto l = DBConnector::getCarByUserId(5);
//    auto l1 = DBConnector::getAllMarken();
//    auto l2 = dbconnector.getAllModelle();
//    auto l3 = dbconnector.getAllFarben();
//    bool test = DBConnector::setRequestedFromCar(5, true);
   //    qDebug() << dbconnector.getNewId("Auto");
   //    qDebug() << dbconnector.insertUser("testuser5", "anders"); //Test: User einfügen
   //    qDebug() << dbconnector.deleteUser(5); //Test: User löschen
   //    qDebug() << "Delete Car:  << dbconnector.deleteCar(3);
   //    auto l = dbconnector.getAllCars();
   //    auto t = l.front();
   //    qDebug() << std::get<1>(t) << "\t" << std::get<2>(t);
   //    auto p = dbconnector.getUserById(2); //Test: Userid 2 ausgeben


    return a.exec();
}
