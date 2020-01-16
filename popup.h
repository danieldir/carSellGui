#ifndef POPUP_H
#define POPUP_H

#include <QDialog>

namespace Ui {
class PopUp;
}

class PopUp : public QDialog
{
    Q_OBJECT

public:
    explicit PopUp(QWidget *parent = 0);
    ~PopUp();

private:
    Ui::PopUp *ui;
};

#endif // POPUP_H
