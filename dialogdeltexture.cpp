#include "dialogdeltexture.h"
#include "ui_dialogdeltexture.h"

DialogDelTexture::DialogDelTexture(QWidget *parent, GeoObj *obj) :
    QDialog(parent),
    ui(new Ui::DialogDelTexture)
{
    ui->setupUi(this);
}

DialogDelTexture::~DialogDelTexture()
{
    delete ui;
}
