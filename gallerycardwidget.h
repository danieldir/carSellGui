#ifndef GALLERYCARDWIDGET_H
#define GALLERYCARDWIDGET_H

#include <QWidget>

namespace Ui {
class GalleryCardWidget;
}

class GalleryCardWidget : public QWidget
{
    Q_OBJECT

public:
    void setting(int,QString,QString,QString,int);
    int getCarId();
    int cId;
    explicit GalleryCardWidget(QWidget *parent = 0);
    ~GalleryCardWidget();

private:
    Ui::GalleryCardWidget *ui;

};

#endif // GALLERYCARDWIDGET_H
