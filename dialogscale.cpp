#include "dialogscale.h"
#include "ui_dialogscale.h"

DialogScale::DialogScale(QWidget *parent, GeoObj *obj) :
    QDialog(parent),
    ui(new Ui::DialogScale)
{
    ui->setupUi(this);
    this->obj = obj;
    ui->label->setText(QString::fromStdString(obj->getName()));
}

DialogScale::~DialogScale()
{
    delete ui;
}

void DialogScale::on_buttonBox_accepted()
{
    obj->scale(ui->xLineEdit->text().toDouble(),
                   ui->yLineEdit->text().toDouble(),
                   ui->zLineEdit->text().toDouble());
}
