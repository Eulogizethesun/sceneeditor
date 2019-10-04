#include "mainwindow.h"
#include <QApplication>
#include <glut.h>
//#include <QTextCodec>
//#include <QtOpenGL>
//#include <QOpenGLWidget>
int main(int argc, char *argv[])
{
    //QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    //QTextCodec::setCodecForTr(codec);
    //QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

