#ifndef CARCARDWIDGET_H
#define CARCARDWIDGET_H

#include <QWidget>

namespace Ui {
class CarCardWidget;
}

class CarCardWidget : public QWidget
{
    Q_OBJECT

public:
    void setSetting(QString,QString,QString,int);
    explicit CarCardWidget(QWidget *parent = 0);
    ~CarCardWidget();


private:
    Ui::CarCardWidget *ui;

};

#endif // CARCARDWIDGET_H
