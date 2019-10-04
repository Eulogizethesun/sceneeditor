#include "dialogaddtexture.h"
#include "ui_dialogaddtexture.h"
#include <QPixmap>

DialogAddTexture::DialogAddTexture(QWidget *parent, GeoObj *obj, MainGLWidget *mainGlWidget) :
    QDialog(parent),
    ui(new Ui::DialogAddTexture)
{
    ui->setupUi(this);
    this->obj = obj;
    this->mainGlWidget = mainGlWidget;
    ui->label->setText(QString::fromStdString(obj->getName()));
    ui->label_r->setEnabled(false);
    ui->label_g->setEnabled(false);
    ui->label_b->setEnabled(false);
    ui->label_a->setEnabled(false);
    ui->lineEdit_r->setEnabled(false);
    ui->lineEdit_g->setEnabled(false);
    ui->lineEdit_b->setEnabled(false);
    ui->lineEdit_a->setEnabled(false);
    ui->radioButton_pre->setEnabled(false);
    ui->radioButton_set->setEnabled(false);
    ui->comboBox->setEnabled(false);
    ui->lineEdit_path->setEnabled(false);
    ui->pushButton_path->setEnabled(false);
}



void DialogAddTexture::on_radioButton_color_clicked(){
    ui->label_r->setEnabled(true);
    ui->label_g->setEnabled(true);
    ui->label_b->setEnabled(true);
    ui->label_a->setEnabled(true);
    ui->lineEdit_r->setEnabled(true);
    ui->lineEdit_g->setEnabled(true);
    ui->lineEdit_b->setEnabled(true);
    ui->lineEdit_a->setEnabled(true);
    ui->radioButton_pre->setEnabled(false);
    ui->radioButton_set->setEnabled(false);
    ui->comboBox->setEnabled(false);
    ui->lineEdit_path->setEnabled(false);
    ui->pushButton_path->setEnabled(false);
}

void DialogAddTexture::on_radioButton_texture_clicked(){
    ui->label_r->setEnabled(false);
    ui->label_g->setEnabled(false);
    ui->label_b->setEnabled(false);
    ui->label_a->setEnabled(false);
    ui->lineEdit_r->setEnabled(false);
    ui->lineEdit_g->setEnabled(false);
    ui->lineEdit_b->setEnabled(false);
    ui->lineEdit_a->setEnabled(false);
    ui->radioButton_pre->setEnabled(true);
    ui->radioButton_set->setEnabled(true);
    ui->comboBox->setEnabled(false);
    ui->lineEdit_path->setEnabled(false);
    ui->pushButton_path->setEnabled(false);
}

void DialogAddTexture::on_radioButton_pre_clicked(){
    ui->comboBox->setEnabled(true);
    ui->lineEdit_path->setEnabled(false);
    ui->pushButton_path->setEnabled(false);
}
void DialogAddTexture::on_radioButton_set_clicked(){
    ui->comboBox->setEnabled(false);
    ui->lineEdit_path->setEnabled(true);
    ui->pushButton_path->setEnabled(true);
}

void DialogAddTexture::on_pushButton_path_clicked(){
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Texture Bmp"), "",
        tr("BMP file (*.bmp);;All Files (*)"));
    if (!fileName.isNull())
    {
        ui->lineEdit_path->setText(fileName);
    }
    else
    {
        //点的是取消
    }
}


float *DialogAddTexture::get_color(){
    float *color = new float[4];
    if (ui->radioButton_color->isChecked()){
        float r = ui->lineEdit_r->text().toFloat();
        float g = ui->lineEdit_g->text().toFloat();
        float b = ui->lineEdit_b->text().toFloat();
        float a = ui->lineEdit_a->text().toFloat();
        // rgba 颜色设置
        color[0] = r;
        color[1] = g;
        color[2] = b;
        color[3] = a;
    }
    return color;
}
char *DialogAddTexture::get_path(){
    char *file = new char[10000];
    if (ui->radioButton_pre->isChecked()) {
        int index = ui->comboBox->currentIndex();
        // 预设纹理设置
        switch (index) {
        case 0:{
            std::strcpy(file,":/img/texture/bianzhiwu.bmp");
            break;
        }
        case 1:{
            std::strcpy(file,":/img/texture/huabu.bmp");
            break;
        }
        case 2:{
            std::strcpy(file,":/img/texture/huagangyan.bmp");
            break;
        }
        case 3:{
            std::strcpy(file,":/img/texture/shensemu.bmp");
            break;
        }
        case 4:{
            std::strcpy(file,":/img/texture/shuidi.bmp");
            break;
        }
        case 5:{
            std::strcpy(file,":/img/texture/xiewenbu.bmp");
            break;
        }
        case 6:{
            std::strcpy(file,":/img/texture/xinzhi.bmp");
            break;
        }
        case 7:{
            std::strcpy(file,":/img/texture/zaishengzhi.bmp");
            break;
        }
        case 8:{
            std::strcpy(file,":/img/texture/zhidai.bmp");
            break;
        }
        }
    }else{
        // 自定义纹理设置
        QString  str = ui->lineEdit_path->text();
        QByteArray ba = str.toLatin1(); // must
        file=ba.data();
    }
    return file;
}

DialogAddTexture::~DialogAddTexture()
{
    delete ui;
}

void DialogAddTexture::on_buttonBox_accepted()
{
    if (ui->radioButton_color->isChecked()){
        float r = ui->lineEdit_r->text().toFloat();
        float g = ui->lineEdit_g->text().toFloat();
        float b = ui->lineEdit_b->text().toFloat();
        float a = ui->lineEdit_a->text().toFloat();
        obj->setColor(r, g, b, a);
    } else if(ui->radioButton_pre->isChecked()) {
        int id = ui->comboBox->currentIndex();
        obj->setTextureId(id);
    } else { // 自定义纹理设置
        QString fileName = ui->lineEdit_path->text();
        int textureId = mainGlWidget->getNewTexId(fileName);
        obj->setTextureId(textureId);
    }
}
