#ifndef DIALOGTRANSLATE_H
#define DIALOGTRANSLATE_H

#include <QDialog>
#include "geoobj.h"

namespace Ui {
class DialogTranslate;
}

class DialogTranslate : public QDialog
{
    Q_OBJECT

public:
    explicit DialogTranslate(QWidget *parent = 0, GeoObj *obj = nullptr);
    ~DialogTranslate();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DialogTranslate *ui;
    GeoObj *obj;
};

#endif // DIALOGTRANSLATE_H
