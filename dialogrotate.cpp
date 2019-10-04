#include "dialogrotate.h"
#include "ui_dialogrotate.h"
#include <math.h>
#define PI acos(-1.0)

DialogRotate::DialogRotate(QWidget *parent, GeoObj *obj) :
    QDialog(parent),
    ui(new Ui::DialogRotate)
{
    ui->setupUi(this);
    this->obj = obj;
    ui->label->setText(QString::fromStdString(obj->getName()));
}

DialogRotate::~DialogRotate()
{
    delete ui;
}

void DialogRotate::on_buttonBox_accepted()
{
    obj->rotate(ui->xLineEdit->text().toDouble(),
                ui->yLineEdit->text().toDouble(),
                ui->zLineEdit->text().toDouble(),
                ui->angleDegreesLineEdit->text().toDouble() * PI / 180.0);
}
