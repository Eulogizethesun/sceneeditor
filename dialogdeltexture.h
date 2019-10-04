#ifndef DIALOGDELTEXTURE_H
#define DIALOGDELTEXTURE_H

#include <QDialog>
#include "geoobj.h"

namespace Ui {
class DialogDelTexture;
}

class DialogDelTexture : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDelTexture(QWidget *parent = 0, GeoObj *obj = nullptr);
    ~DialogDelTexture();

private:
    Ui::DialogDelTexture *ui;
    GeoObj *obj;
};

#endif // DIALOGDELTEXTURE_H
