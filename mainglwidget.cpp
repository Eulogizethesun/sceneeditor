#include "mainglwidget.h"

#include <QtWidgets>
//#include <QtOpenGL>
#include <glut.h>
#include <vector>
#include <mutex>
#include "mainwindow.h"
#include "geoobj.h"
#include "geoobjlist.h"
#include "geoobj.h"
#include <string>
#define Pi 3.1415926
float MainGLWidget::positionx=10;
float MainGLWidget::positiony=0;
float MainGLWidget::positionz=10;
float MainGLWidget::ambient_r=0.3;
float MainGLWidget::ambient_g=0.3;
float MainGLWidget::ambient_b=0.3;
float MainGLWidget::diffuse_r=1;
float MainGLWidget::diffuse_g=1;
float MainGLWidget::diffise_b=1;




MainGLWidget::MainGLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    MainWindow *mainWindow = qobject_cast<MainWindow*>(this->window());
    this->geoObjList = mainWindow->geoObjList;
    this->pool = mainWindow->pool;
    eye[0]=4;eye[1]=4;eye[2]=4;
    world[0]=0;world[1]=0;world[2]=0;
    angle=Pi/4;
    r=4;
    bPersp=false;brotate=false;


    //texture = mainWindow->texture;
    startTimer(10);
}
MainGLWidget::~MainGLWidget()
{
}
void MainGLWidget::timerEvent(QTimerEvent *event)
{
    updateGL();
}

void MainGLWidget::initializeGL()
{
    qglClearColor(Qt::white);
    glFrontFace(GL_CCW); // counterclockwise polygons are front-facing

    // what do these settings mean?
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glDepthFunc( GL_LEQUAL );
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
    glEnable(GL_COLOR_MATERIAL);

    // lighting settings are incorrect
    // everything is black using this setting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    static GLfloat white[4] = { diffuse_r, diffuse_g, diffise_b, 1.0 };
    static GLfloat black[4] = { ambient_r, ambient_g, ambient_b, 1.0 };
    static GLfloat lightPosition[4] = { positionx,positiony,positionz,1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_AMBIENT, black);   //散射光属性
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);   //散射光属性
    //glLightfv(GL_LIGHT0, GL_SPECULAR, white);  //镜面反射光

    /*
    glGenTextures(9, list);
    for (int i = 0; i < 9; ++i) {
        const QString file = "bianzhiwu.bmp";
        QTemporaryDir tempDir;
        tempDir.setAutoRemove(false);
        const QString tempFile = tempDir.path() + "/" + file;
        QFile::copy(":/img/texture/" + file, tempFile);
        texload(i, tempFile.toLocal8Bit().constData());
    }
    */

    int nrTextures = TextureList::nrTex;
    textures.resize(nrTextures);
    for(int i = 0; i < nrTextures; ++i) {
        glGenTextures(1, &textures[i]);
        const QString file = QString::fromStdString(TextureList::tex[i]);
        texload(i, ":/img/texture/" + file);
    }
}
void MainGLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef QT_OPENGL_ES_1
    glOrthof(-2, +2, -2, +2, 1.0, 15.0);
#else
    glOrtho(-2, +2, -2, +2, 1.0, 15.0);
#endif
    glMatrixMode(GL_MODELVIEW);
}

///////////////////////////////////////////////////////////////

void MainGLWidget::paintGL()
{

    GLfloat white[4] = { diffuse_r, diffuse_g, diffise_b, 1.0 };
    GLfloat black[4] = { ambient_r, ambient_g, ambient_b, 1.0 };
    GLfloat lightPosition[4] = { positionx,positiony,positionz,1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_AMBIENT, black);   //散射光属性
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);   //散射光属性
    //glLightfv(GL_LIGHT0, GL_SPECULAR, white);  //镜面反射光
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //draw_try();
    draw();
}
void MainGLWidget::draw_try()
{
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    glRotatef(100 / 16.0, 1.0, 0.0, 0.0);
    glRotatef(200 / 16.0, 0.0, 1.0, 0.0);
    glRotatef(300 / 16.0, 0.0, 0.0, 1.0);
    qglColor(Qt::red);
    glBegin(GL_QUADS);
        glNormal3f(0,0,-1);
        glVertex3f(-1,-1,0);
        glVertex3f(-1,1,0);
        glVertex3f(1,1,0);
        glVertex3f(1,-1,0);
    glEnd();
    qglColor(Qt::blue);
    glBegin(GL_TRIANGLES);
        glNormal3f(0,-1,0.707);
        glVertex3f(-1,-1,0);
        glVertex3f(1,-1,0);
        glVertex3f(0,0,1.2);
    glEnd();
    qglColor(Qt::green);
    glBegin(GL_TRIANGLES);
        glNormal3f(1,0, 0.707);
        glVertex3f(1,-1,0);
        glVertex3f(1,1,0);
        glVertex3f(0,0,1.2);
    glEnd();
    qglColor(Qt::yellow);
    glBegin(GL_TRIANGLES);
        glNormal3f(0,1,0.707);
        glVertex3f(1,1,0);
        glVertex3f(-1,1,0);
        glVertex3f(0,0,1.2);
    glEnd();
    qglColor(Qt::cyan);
    glBegin(GL_TRIANGLES);
        glNormal3f(-1,0,0.707);
        glVertex3f(-1,1,0);
        glVertex3f(-1,-1,0);
        glVertex3f(0,0,1.2);
    glEnd();
}

///////////////////////////////////////////////////////////////

void MainGLWidget::draw()
{
    if(brotate)
    {
        double r=sqrt(eye[0]*eye[0]+eye[1]*eye[1]);
        angle-=Pi/180;
        eye[0]=r*cos(angle);
        eye[1]=r*sin(angle);
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye[0], eye[1], eye[2], // eye
              world[0], world[1], world[2], // look at
            0, 0, 1); // up vector
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    draw_axes();
    //qglColor(Qt::red);

    /*
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); // texture + light
    glBegin(GL_QUADS);
        glTexCoord2i(1,1); glVertex3f(0.500000, -0.500000, 0.000000);
        glTexCoord2i(1,0); glVertex3f( 0.500000, 0.500000, 0.000000);
        glTexCoord2i(0,0); glVertex3f(0.500000, 0.500000, 1.000000);
        glTexCoord2i(0,1); glVertex3f(0.500000, -0.500000, 1.000000);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    */

    std::unique_lock<std::mutex> lock(geoObjList->m);
    for(GeoObj *obj : geoObjList->a) {
        bool hasTexture = (obj->textureId >= 0);
        if(hasTexture) {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, textures[obj->textureId]);
        } else {
            glColor4f(obj->color[0], obj->color[1], obj->color[2], obj->color[3]);
        }
        for(Face *f : obj->fs) {
            draw_face(*f);
        }
        if(hasTexture) {
           glDisable(GL_TEXTURE_2D);
        }
    }
}

void MainGLWidget::draw_axes()
{
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(1.5);
    qglColor(Qt::red);
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(1000, 0, 0);
    glEnd();
    qglColor(Qt::green);
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 1000, 0);
    glEnd();
    qglColor(Qt::blue);
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, 1000);
    glEnd();
    qglColor(Qt::gray);
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(-1000, 0, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, -1000, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, -1000);
    glEnd();
}
void MainGLWidget::draw_face(const Face &f)
{
    int j = 0;
    GLint i=0;
    GLfloat ver[10][3],normal[3],vc1[3],vc2[3];
    GLfloat a,b,c;
    GLfloat r;
    int map[4][2] = { {0,0},{0,1},{1,1},{1,0} };
    glBegin(GL_POLYGON);

    int k = 0;
    for(const Vertex *v : f.a) {
        //glTexCoord2iv(map[j]);
        /*
        glTexCoord2d(f.tx[k], f.ty[k]); ++k;
        if(v->hasNormal) {
            glNormal3f(v->nx, v->ny, v->nz);
        }
        glVertex3f(v->x, v->y, v->z);
        */
        j++;
        ver[i][0]=v->x;
        ver[i][1]=v->y;
        ver[i][2]=v->z;
        i++;
        if(i==5) i=i-1;
    }
    vc1[0]= ver[1][0] - ver[0][0]; vc1[1]= ver[1][1] - ver[0][1]; vc1[2]= ver[1][2] - ver[0][2];
    vc2[0]= ver[2][0] - ver[0][0]; vc2[1]= ver[2][1] - ver[0][1]; vc2[2]= ver[2][2] - ver[0][2];
    a = vc1[1] * vc2[2] - vc2[1] * vc1[2];
    b = vc2[0] * vc1[2] - vc1[0] * vc2[2];
    c = vc1[0] * vc2[1] - vc2[0] * vc1[1];
    r = sqrt( a * a + b* b + c * c);
    normal[0] = a / r; normal[1] = b / r; normal[2] = c / r;

    for(const Vertex *v : f.a) {
        glTexCoord2d(f.tx[k], f.ty[k]); ++k;
        if(v->hasNormal) {
            glNormal3f(v->nx, v->ny, v->nz);
        } else {
            glNormal3f(normal[0], normal[1], normal[2]);
        }
        glVertex3f(v->x, v->y, v->z);
    }

    glEnd();
}

void MainGLWidget::keyPressEvent ( QKeyEvent * k )
{
    if(k->key() == Qt::Key_A)
    {
        double r=sqrt(eye[0]*eye[0]+eye[1]*eye[1]);
        angle-=Pi/18;
        eye[0]=r*cos(angle);
        eye[1]=r*sin(angle);
        this->updateGL();
    }
    else if(k->key() == Qt::Key_D)
    {
        double r=sqrt(eye[0]*eye[0]+eye[1]*eye[1]);
        angle+=Pi/18;
        eye[0]=r*cos(angle);
        eye[1]=r*sin(angle);
        this->updateGL();
    }
    else if(k->key() == Qt::Key_S)
    {
        eye[0]=eye[0]*1.1;
        eye[1]=eye[1]*1.1;
        eye[2]=eye[2]*1.1;
        this->updateGL();
    }
    else if(k->key() == Qt::Key_W)
    {
        eye[0]=eye[0]*0.9;
        eye[1]=eye[1]*0.9;
        eye[2]=eye[2]*0.9;
        this->updateGL();
    }
    else if(k->key() == Qt::Key_Z)
    {
        eye[0]+=0.2;
        world[0]+=0.2;
        this->updateGL();
    }
    else if(k->key() == Qt::Key_X)
    {
        eye[0]-=0.2;
        world[0]-=0.2;
        this->updateGL();
    }
    else if(k->key() == Qt::Key_C)
    {
        eye[1]+=0.2;
        world[1]+=0.2;
        this->updateGL();
    }
    else if(k->key() == Qt::Key_V)
    {
        eye[1]-=0.2;
        world[1]-=0.2;
        this->updateGL();
    }
    else if(k->key() == Qt::Key_R)
    {
        eye[0]=4;eye[1]=4;eye[2]=4;
        world[0]=0;world[1]=0;world[2]=0;
        angle=Pi/4;
        this->updateGL();
    }
    else if(k->key() == Qt::Key_Space)
    {
        brotate=!brotate;
        this->updateGL();
    }
    else if(k->key() == Qt::Key_Left)
    {
        int i = listWidget_geoObj->currentRow();
        if(i<0)
            return;
        GeoObj *obj=geoObjList->a[i];
        obj->translate(0.2,0,0);
        this->updateGL();
    }
    else if(k->key() == Qt::Key_I)
    {
        positionx=positionx-2;
        this->updateGL();
    }
    else if(k->key() == Qt::Key_K)
    {
        positionx=positionx+2;
        this->updateGL();
    }
    else if(k->key() == Qt::Key_J)
    {
        positiony=positiony-2;
        this->updateGL();
    }
    else if(k->key() == Qt::Key_L)
    {
        positiony=positiony+2;
        this->updateGL();
    }
    else if(k->key() == Qt::Key_U)
    {
        positionz=positionz+2;
        this->updateGL();
    }
    else if(k->key() == Qt::Key_O)
    {
        positionz=positionz-2;
        this->updateGL();
    }
    else if(k->key() == Qt::Key_Right)
    {
        int i = listWidget_geoObj->currentRow();
        if(i<0)
            return;
        GeoObj *obj=geoObjList->a[i];
        obj->translate(-0.2,0,0);
        this->updateGL();
    }
    else if(k->key() == Qt::Key_Left)
    {
        int i = listWidget_geoObj->currentRow();
        if(i<0)
            return;
        GeoObj *obj=geoObjList->a[i];
        obj->translate(0.2,0,0);
        this->updateGL();
    }
    else if(k->key() == Qt::Key_Up)
    {
        int i = listWidget_geoObj->currentRow();
        if(i<0)
            return;
        GeoObj *obj=geoObjList->a[i];
        obj->translate(0,-0.2,0);
        this->updateGL();
    }
    else if(k->key() == Qt::Key_Down)
    {
        int i = listWidget_geoObj->currentRow();
        if(i<0)
            return;
        GeoObj *obj=geoObjList->a[i];
        obj->translate(0,0.2,0);
        this->updateGL();
    }
    else if(k->key() == Qt::Key_F)
    {
        if(pool->getnf()==0|pool->getnv()==0)
            return;
        double sx=0,sy=0,sz=0;
        double mx=1;
        for(Vertex v:pool->vs)
        {
            sx+=v.x;
            sy+=v.y;
            sz+=v.z;
        }
        sx/=pool->getnv();sy/=pool->getnv();sz/=pool->getnv();
        double l=0;
        for(Vertex v:pool->vs)
        {
            l=sqrt((v.x-sx)*(v.x-sx)+(v.y-sy)*(v.y-sy)+(v.z-sz)*(v.z-sz));
            mx=(l>mx)?l:mx;
        }
        int pro_n=3;
        eye[0]=sx+mx+pro_n;eye[1]=sy+mx+pro_n;eye[2]=sz+mx+pro_n;
        world[0]=sx;world[1]=sy;world[2]=sz;
        angle=Pi/4;
        this->updateGL();
    }
    else if(k->key() == Qt::Key_P)
    {
        bPersp=!bPersp;
        int width=916;
        int height=763;
        glViewport(0,0,width,height);						// Reset The Current Viewport
        glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
        glLoadIdentity();									// Reset The Projection Matrix
        float whRatio = (GLfloat)width/(GLfloat)height;
        if (bPersp)
        {
            gluPerspective(45,1,1,25);
        }
        else
        glOrtho(-3 ,3, -3, 3,-100,100);
        glMatrixMode(GL_MODELVIEW);
        this->updateGL();

    }
}


/*bool MainGLWidget::draw_cuboid(GeoObj *obj)
{
    Cuboid *p = dynamic_cast<Cuboid*>(obj);
    if(p == nullptr) return false;

    glBegin(GL_QUADS);
    for(int i = 0; i < 6; ++i) {
        for(int j = 0; j < 4; ++j) {
            glVertex3fv(Cuboid::cube_coords[i][j]);
        }
    }
    glEnd();

    return true;
}

bool MainGLWidget::draw_sphere(GeoObj *obj)
{
    Sphere *p = dynamic_cast<Sphere*>(obj);
    if(p == nullptr) return false;
    glPushMatrix();
    glTranslatef(3, 3, 3);
    //glutSolidSphere(1, 10, 10);
    glPopMatrix();
    return true;
}*/


void MainGLWidget::texload(int index, QString fileName)
{
    QImage textureImg = QGLWidget::convertToGLFormat(QImage(fileName));
    glBindTexture(GL_TEXTURE_2D, textures[index]);
    // 指定当前纹理的放大/缩小过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D,
        0, 	    //mipmap层次(通常为，表示最上层)
        GL_RGB,	//我们希望该纹理有红、绿、蓝数据
        textureImg.width(), //纹理宽带，必须是n，若有边框+2
        textureImg.height(), //纹理高度，必须是n，若有边框+2
        0, //边框(0=无边框, 1=有边框)
        GL_RGBA,	//bitmap数据的格式 // use RGBA in QT
        GL_UNSIGNED_BYTE, //每个颜色数据的类型
        textureImg.bits());	//bitmap数据指针
}

int MainGLWidget::getNewTexId(QString fileName)
{
    int id = textures.size();
    textures.push_back(-1);
    glGenTextures(1, &textures[id]);
    texload(id, fileName);
    return id;
}
