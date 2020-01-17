#include "carsell.h"
#include <QApplication>

int main(int argc, char *argv[])
{
//    DBConnector::connectToDB();

    QApplication a(argc, argv);
    Carsell w;
    w.show();

    //tests
//    auto user = DBConnector::getUserByUsername("Daniel");
//       auto l = dbconnector.getAllMarken();
//       auto l2 = dbconnector.getAllModelle();
//       auto l3 = dbconnector.getAllFarben();
   //    dbconnector.searchCar(NULL, NULL, NULL, 0, "Benzin", 0); //Test: Auto suchen (Null bei String/0 bei int wenn Wert egal)
   //    qDebug() << dbconnector.getNewId("Auto");
   //    qDebug() << dbconnector.insertUser("testuser5", "anders"); //Test: User einfügen
//    qDebug() << "Insert Car: " << DBConnector::insertCar("Tesla", "Model 3", "Rot", 49999, "Elektro", NULL, 3); //Test: Auto einfügen
   //    qDebug() << dbconnector.deleteUser(5); //Test: User löschen
   //    qDebug() << "Delete Car:  << dbconnector.deleteCar(3);
   //    auto l = dbconnector.getAllCars();
   //    auto t = l.front();
   //    qDebug() << std::get<1>(t) << "\t" << std::get<2>(t);
   //    auto p = dbconnector.getUserById(2); //Test: Userid 2 ausgeben


    return a.exec();
}
