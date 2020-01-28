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
    void setting(QString,QString,QString,int);
    explicit GalleryCardWidget(QWidget *parent = 0);
    ~GalleryCardWidget();

private:
    Ui::GalleryCardWidget *ui;
};

#endif // GALLERYCARDWIDGET_H
