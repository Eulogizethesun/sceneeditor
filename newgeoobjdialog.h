#ifndef NEWGEOOBJDIALOG_H
#define NEWGEOOBJDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include "geoobj.h"

namespace Ui {
class NewGeoObjDialog;
}

class NewGeoObjDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewGeoObjDialog(QWidget *parent = 0);
    ~NewGeoObjDialog();

private slots:
    void on_radioButton_cone_clicked();

    void on_radioButton_cube_clicked();

    void on_radioButton_cylinder_clicked();

    void on_radioButton_prism_clicked();

    void on_radioButton_sphere_clicked();

    void on_radioButton_cuboid_clicked();

    void on_radioButton_pyramid_clicked();

    void on_radioButton_frustum_of_pyramid_clicked();

    void on_radioButton_frustum_of_cone_clicked();

    void checkLineEditValidity();

private:
    Ui::NewGeoObjDialog *ui;
    // dynamic widgets
    QLineEdit *txtSideLen     = nullptr; // cube
    QLineEdit *txtBaseLen     = nullptr; // cuboid, prism, pyramid
    QLineEdit *txtBaseWidth   = nullptr; // cuboid
    QLineEdit *txtHeight      = nullptr; // cuboid, prism, cylinder, pyramid
    QLineEdit *txtNormalX     = nullptr; // cuboid, prism, pyramid
    QLineEdit *txtNormalY     = nullptr; // cuboid, prism, pyramid
    QLineEdit *txtNormalZ     = nullptr; // cuboid, prism, pyramid
    QLineEdit *txtCenterX     = nullptr; // cuboid, sphere, cylinder, prism, pyramid
    QLineEdit *txtCenterY     = nullptr; // cuboid, sphere, cylinder, prism, pyramid
    QLineEdit *txtCenterZ     = nullptr; // cuboid, sphere, cylinder, prism, pyramid
    QLineEdit *txtRadius      = nullptr; // sphere, cylinder
    QLineEdit *txtNumber      = nullptr; // prism, pyramid
    QLineEdit *txtLowerRadius = nullptr; // frustum of cylinder
    QLineEdit *txtUpperRadius = nullptr; // frustum of cylinder
    QLineEdit *txtLowerSideLen = nullptr; // frustum of pymarid
    QLineEdit *txtUpperSideLen = nullptr; // frustum of pymarid

    void clearDynamicWidgets();
    void setLineEditValidators(); // only accept numbers (double)

public:
    GeoObj* getGeoObj();
};

#endif // NEWGEOOBJDIALOG_H
