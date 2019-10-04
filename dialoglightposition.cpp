#include "dialoglightposition.h"
#include "ui_dialoglightposition.h"
#include "mainglwidget.h"

Dialoglightposition::Dialoglightposition(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialoglightposition)
{
    ui->setupUi(this);
}

Dialoglightposition::~Dialoglightposition()
{
    delete ui;
}

void Dialoglightposition::on_buttonBox_accepted()
{
    double x = ui->xLineEdit->text().toDouble();
    double y = ui->yLineEdit->text().toDouble();
    double z = ui->zLineEdit->text().toDouble();
    MainGLWidget::positionx=x;
    MainGLWidget::positiony=y;
    MainGLWidget::positionz=z;
}

