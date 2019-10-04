#ifndef DIALOGSCALE_H
#define DIALOGSCALE_H

#include <QDialog>
#include "geoobj.h"

namespace Ui {
class DialogScale;
}

class DialogScale : public QDialog
{
    Q_OBJECT

public:
    explicit DialogScale(QWidget *parent = 0, GeoObj *obj = nullptr);
    ~DialogScale();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DialogScale *ui;
    GeoObj *obj;
};

#endif // DIALOGSCALE_H
