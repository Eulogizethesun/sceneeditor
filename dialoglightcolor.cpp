#include "dialoglightcolor.h"
#include "ui_dialoglightcolor.h"
#include "mainglwidget.h"

Dialoglightcolor::Dialoglightcolor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialoglightcolor)
{
    ui->setupUi(this);
}

Dialoglightcolor::~Dialoglightcolor()
{
    delete ui;
}

void Dialoglightcolor::on_buttonBox_accepted()
{
    double r1 = ui->xLineEdit->text().toDouble();
    double g1 = ui->yLineEdit->text().toDouble();
    double b1 = ui->zLineEdit->text().toDouble();

    double r2 = ui->xLineEdit_2->text().toDouble();
    double g2 = ui->yLineEdit_2->text().toDouble();
    double b2 = ui->zLineEdit_2->text().toDouble();
    MainGLWidget::ambient_r=r1;
    MainGLWidget::ambient_g=g1;
    MainGLWidget::ambient_b=b1;
    MainGLWidget::diffuse_r=r2;
    MainGLWidget::diffuse_g=g2;
    MainGLWidget::diffise_b=b2;
}
