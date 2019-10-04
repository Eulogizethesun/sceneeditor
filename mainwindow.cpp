#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newgeoobjdialog.h"
#include "geoobj.h"
#include "geoobjlist.h"
#include "pool.h"
#include "exportdialog.h"
#include "dialogtranslate.h"
#include "dialogscale.h"
#include "dialogrotate.h"
#include "dialogaddtexture.h"
#include "dialogdeltexture.h"
#include "dialoglightposition.h"
#include "dialoglightcolor.h"
#include "objmodel.h"
#include "texturelist.h"
#include <list>
#include <vector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->pool = new Pool();
    this->geoObjList = new GeoObjList(this->pool, this->geoObjList, this->ui->listWidget_geoObj);
    ui->setupUi(this);
    //ui->mainGLWidget->geoObjList=this->geoObjList;
    ui->mainGLWidget->listWidget_geoObj=ui->listWidget_geoObj;
    //qglWidget = new QGLWidget;
    //ui->horizontalLayout_main->addWidget(qglWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateGL()
{
    ui->mainGLWidget->updateGL();
}

///////////////////////////////////////////////////

void MainWindow::on_actionNewGeoObj_triggered()
{
    NewGeoObjDialog *dialog = new NewGeoObjDialog();
    // "modal" means that the user can't interact with main window before the new window is closed
    dialog->setModal(true);
    dialog->exec();
    if(dialog->result() == QDialog::Accepted) {
        GeoObj *obj = dialog->getGeoObj();
        this->geoObjList->add(obj);
        this->ui->listWidget_geoObj->addItem(QString::fromStdString(obj->getName()));
        this->updateGL();
    }
}

void MainWindow::on_actionImport_triggered()
{
    //QFileDialog *dialog = new QFlieDialog();
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open OBJ File"), "",
        tr("OBJ file (*.obj);;All Files (*)"));
    if(fileName.isNull())
        return;
    ObjModel* objModel = ReadOBJ(fileName);
    ObjFile *objFile = new ObjFile(objModel);
    this->geoObjList->add(objFile);
    this->ui->listWidget_geoObj->addItem(QString::fromStdString(objFile->getName()));
    this->updateGL();
}

void MainWindow::on_actionExport_triggered()
{
    ExportDialog *export_dialog = new ExportDialog();
    export_dialog->setList(ui->listWidget_geoObj);
    export_dialog->pool=this->pool;
    export_dialog->setModal(true);
    export_dialog->exec();
}

void MainWindow::on_actionRotate_triggered()
{
    int i = ui->listWidget_geoObj->currentRow();
    if(i < 0) {
        showWarningNoItemSelected();
    } else {
        DialogRotate *d = new DialogRotate(this, geoObjList->a[i]);
        d->exec();
    }
}

void MainWindow::on_actionTranslate_triggered()
{
    int i = ui->listWidget_geoObj->currentRow();
    if(i < 0) {
        showWarningNoItemSelected();
    } else {
        DialogTranslate *d = new DialogTranslate(this, geoObjList->a[i]);
        d->exec();
    }
}

void MainWindow::on_actionScale_triggered()
{
    int i = ui->listWidget_geoObj->currentRow();
    if(i < 0) {
        showWarningNoItemSelected();
    } else {
        DialogScale *d = new DialogScale(this, geoObjList->a[i]);
        d->exec();
    }
}

void MainWindow::on_actionAdd_triggered()
{
    int i = ui->listWidget_geoObj->currentRow();
    if(i < 0) {
        showWarningNoItemSelected();
    } else {
        DialogAddTexture *d = new DialogAddTexture(this, geoObjList->a[i], ui->mainGLWidget);
        d->exec();
        /*
        if(d->result() == QDialog::Accepted) {
            float *color = d->get_color();
            char *file = d->get_path();
            texture.add(i, file, color);
        }
        */
    }

}


void MainWindow::on_actionposition_triggered()
{
    Dialoglightposition *d = new Dialoglightposition();
    d->exec();
}

void MainWindow::on_actioncolor_triggered()
{
    Dialoglightcolor *d = new Dialoglightcolor();
    d->exec();
}

void MainWindow::showWarningNoItemSelected()
{
    QMessageBox::warning(
        this,
        tr("Transformation"),
        tr("Please select an object from the list.") );
}

ObjModel* MainWindow::ReadOBJ(QString filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return NULL;
    }
    QStringList list;

    ObjModel* model;
    model = new ObjModel();
    QString split = ' ';

    model->path = filename;
    model->num_Faces = 0;
    model->num_Vertices = 0;
    Vertex *v;
    Face *f;
    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        QString str(line);
        if (str.length() < 2)
            continue;
        if (str[0] == 'v')
        {
            str = str.trimmed();
            list = str.split(split);
            v = this->pool->newVertex(list[1].toDouble(),list[2].toDouble(),list[3].toDouble());
            model->num_Vertices++;
            model->list_Vertices.push_back(v);
        }
        else if (str[0] == 'f')
        {
            str = str.trimmed();
            list = str.split(split);
            std::vector<Vertex*> a;
            for(int i=0;i<list.length()-1;i++)
            {
                a.push_back(model->list_Vertices.value(list[i+1].toInt()-1));
            }
            f=this->pool->newFace(a);
            //f=this->pool->newFace(model->list_Vertices.value(list[1].toInt()-1),model->list_Vertices.value(list[2].toInt()-1),model->list_Vertices.value(list[3].toInt()-1));
            model->num_Faces++;
            model->list_Faces.push_back(f);
        }
    }

    return model;
}

void MainWindow::on_actionScreenShot_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save BMP File"), "",
        tr("BMP file (*.bmp);;All Files (*)"));
        if(fileName.isNull())
            return;
        int width=912;int height=763;//912可行，916会有黑线，913-915出错
        static void * screenData;
        int len = width * height * 3;
        screenData = malloc(len);
        memset(screenData,0,len);
        glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, screenData);
        unsigned char* bitmapData=(unsigned char*)screenData;

        BITMAPFILEHEADER bitmapFileHeader;
        memset(&bitmapFileHeader,0,sizeof(BITMAPFILEHEADER));
        bitmapFileHeader.bfSize = sizeof(BITMAPFILEHEADER);
        bitmapFileHeader.bfType = 0x4d42;	//BM
        bitmapFileHeader.bfOffBits =sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
        BITMAPINFOHEADER bitmapInfoHeader;
        memset(&bitmapInfoHeader,0,sizeof(BITMAPINFOHEADER));
        bitmapInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
        bitmapInfoHeader.biWidth = width;
        bitmapInfoHeader.biHeight = height;
        bitmapInfoHeader.biPlanes = 1;
        bitmapInfoHeader.biBitCount = 24;
        bitmapInfoHeader.biCompression = BI_RGB;
        bitmapInfoHeader.biSizeImage = width * abs(height) * 3;
        FILE * filePtr;
        unsigned char tempRGB;
        int imageIdx;
        for (imageIdx = 0;imageIdx < bitmapInfoHeader.biSizeImage;imageIdx +=3)
        {
            tempRGB = bitmapData[imageIdx];
            bitmapData[imageIdx] = bitmapData[imageIdx + 2];
            bitmapData[imageIdx + 2] = tempRGB;
        }
        std::string str = fileName.toStdString();
        filePtr = fopen(str.c_str(),"wb");
        fwrite(&bitmapFileHeader,sizeof(BITMAPFILEHEADER),1,filePtr);
        fwrite(&bitmapInfoHeader,sizeof(BITMAPINFOHEADER),1,filePtr);
        fwrite(bitmapData,bitmapInfoHeader.biSizeImage,1,filePtr);
        fclose(filePtr);
}

void MainWindow::on_actionRemoveTexture_triggered()
{
    int i = ui->listWidget_geoObj->currentRow();
    if(i < 0) {
        showWarningNoItemSelected();
    } else {
        geoObjList->a[i]->removeTexture();
    }
}

void MainWindow::on_actionRemoveGeoObj_triggered()
{
    int i = ui->listWidget_geoObj->currentRow();
    if(i < 0) {
        showWarningNoItemSelected();
    } else {
        qDeleteAll(ui->listWidget_geoObj->selectedItems());
        geoObjList->a.erase(geoObjList->a.begin() + i);
    }
}
