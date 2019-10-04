#ifndef DIALOGADDTEXTURE_H
#define DIALOGADDTEXTURE_H

#include <QDialog>
#include "geoobj.h"
#include <string>
#include"mainwindow.h"
#include"mainglwidget.h"

namespace Ui {
class DialogAddTexture;
}

class DialogAddTexture : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddTexture(QWidget *parent = 0, GeoObj *obj = nullptr, MainGLWidget *mainGlWidget = nullptr);
    ~DialogAddTexture();

public:
    float *get_color();
    char *get_path();

private slots:
    void on_radioButton_color_clicked();
    void on_radioButton_texture_clicked();
    void on_radioButton_pre_clicked();
    void on_radioButton_set_clicked();
    void on_pushButton_path_clicked();

    void on_buttonBox_accepted();

private:
    Ui::DialogAddTexture *ui;
    GeoObj *obj;
    MainGLWidget *mainGlWidget;
};

#endif // DIALOGADDTEXTURE_H
