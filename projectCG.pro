#-------------------------------------------------
#
# Project created by QtCreator 2018-12-29T23:50:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = projectCG
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    newgeoobjdialog.cpp \
    mainglwidget.cpp \
    geoobj.cpp \
    geoobjlist.cpp \
    pool.cpp \
    exportdialog.cpp \
    dialogtranslate.cpp \
    dialogscale.cpp \
    dialogrotate.cpp \
    dialogaddtexture.cpp \
    dialogdeltexture.cpp \
    matrix.cpp \
    dialoglightposition.cpp \
    texturelist.cpp \
    dialoglightcolor.cpp

HEADERS += \
        mainwindow.h \
    newgeoobjdialog.h \
    mainglwidget.h \
    geoobj.h \
    geoobjlist.h \
    pool.h \
    exportdialog.h \
    dialogtranslate.h \
    dialogscale.h \
    dialogrotate.h \
    dialogaddtexture.h \
    dialogdeltexture.h \
    matrix.h \
    dialoglightposition.h \
    texturelist.h \
    dialoglightcolor.h
    objmodel.h

FORMS += \
        mainwindow.ui \
    newgeoobjdialog.ui \
    exportdialog.ui \
    dialogtranslate.ui \
    dialogscale.ui \
    dialogrotate.ui \
    dialogaddtexture.ui \
    dialogdeltexture.ui \
    dialoglightposition.ui \
    dialoglightcolor.ui


# manually added options
#QMAKE_CXXFLAGS += -std=c++11
#msvc:QMAKE_CXXFLAGS += -source-charset:utf-8
QT += opengl

#LIBS += -lglut

win32: LIBS += -L$$PWD/glut/ -lglut32
win32: LIBS += -L$$PWD/glut/ -lglut

INCLUDEPATH += $$PWD/glut
DEPENDPATH += $$PWD/glut

RESOURCES += \
    img/img.qrc
