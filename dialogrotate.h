#ifndef DIALOGROTATE_H
#define DIALOGROTATE_H

#include <QDialog>
#include "geoobj.h"

namespace Ui {
class DialogRotate;
}

class DialogRotate : public QDialog
{
    Q_OBJECT

public:
    explicit DialogRotate(QWidget *parent = 0, GeoObj *obj = nullptr);
    ~DialogRotate();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DialogRotate *ui;
    GeoObj *obj;
};

#endif // DIALOGROTATE_H
