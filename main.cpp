#include "carsell.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Carsell w;
    w.show();

    return a.exec();
}
