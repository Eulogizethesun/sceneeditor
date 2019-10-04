#include "dialogtranslate.h"
#include "ui_dialogtranslate.h"

DialogTranslate::DialogTranslate(QWidget *parent, GeoObj *obj) :
    QDialog(parent),
    ui(new Ui::DialogTranslate)
{
    this->obj = obj;
    ui->setupUi(this);
    ui->label->setText(QString::fromStdString(obj->getName()));
}

DialogTranslate::~DialogTranslate()
{
    delete ui;
}

void DialogTranslate::on_buttonBox_accepted()
{
    obj->translate(ui->xLineEdit->text().toDouble(),
                   ui->yLineEdit->text().toDouble(),
                   ui->zLineEdit->text().toDouble());
}
