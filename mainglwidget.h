#ifndef MAINGLWIDGET_H
#define MAINGLWIDGET_H

#include <QtOpenGL/QGLWidget>
#include <glut.h>
#include "geoobj.h"
#include "geoobjlist.h"
#include "texturelist.h"
#include "pool.h"
#include<vector>

/*
 * Reference:
 * https://doc.qt.io/archives/3.3/qglwidget.html
 */

class GeoObjList;

class MainGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    QListWidget *listWidget_geoObj;
    explicit MainGLWidget(QWidget *parent = 0);
    ~MainGLWidget();
    static float positionx;
    static float positiony;
    static float positionz;
    static float ambient_r;
    static float ambient_g;
    static float ambient_b;
    static float diffuse_r;
    static float diffuse_g;
    static float diffise_b;


protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

public slots:

signals:

private:
    void draw_try();
    void draw();
    void draw_axes();
    void draw_face(const Face &f);
    void keyPressEvent ( QKeyEvent * k );
    void timerEvent(QTimerEvent* event);
    //bool draw_cuboid(GeoObj *obj);
    //bool draw_sphere(GeoObj *obj);
    GeoObjList *geoObjList;
    Pool *pool;
    std::vector<GLuint> textures;
    double eye[3];
    double world[3];
    double angle;
    double r;
    bool bPersp;
    bool brotate;
public:
    //unsigned char *LoadBitmapFile(const char *filename, BITMAPINFOHEADER *bitmapInfoHeader);
    void texload(int index, QString fileName);
    int getNewTexId(QString fileName);
};

#endif // MAINGLWIDGET_H
