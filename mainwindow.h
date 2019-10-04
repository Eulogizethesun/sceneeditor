#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QMainWindow>
#include <QFileDialog>
#include <QListWidget>
#include <QMessageBox>
#include "geoobj.h"
#include "geoobjlist.h"
#include "pool.h"
#include "objmodel.h"
#include "texturelist.h"
//#include <QOpenGLWidget>
//#include <QtOpenGL/QGLWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void updateGL();
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
   void on_actionNewGeoObj_triggered();

   void on_actionImport_triggered();
   void on_actionExport_triggered();

   void on_actionTranslate_triggered();

   void on_actionRotate_triggered();

   void on_actionScale_triggered();
   void on_actionAdd_triggered();
   void on_actionposition_triggered();
   void on_actioncolor_triggered();
   ObjModel* ReadOBJ(QString filename);

   void on_actionScreenShot_triggered();

   void on_actionRemoveTexture_triggered();

   void on_actionRemoveGeoObj_triggered();

private:
   void showWarningNoItemSelected();
private:
    //QOpenGLWidget *openglWidget;
    //QGLWidget *qglWidget;
public:
   Ui::MainWindow *ui;
    GeoObjList *geoObjList;
    Pool *pool;
    TextureList texture;
};

#endif // MAINWINDOW_H
