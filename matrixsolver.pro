#-------------------------------------------------
#
# Project created by QtCreator 2013-11-20T18:21:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = matrixsolver
TEMPLATE = app
linux-g++{
INCLUDEPATH += /usr/include/eigen3
}

#macx Don't have OS X, although Victor does
#win32(distribute eigen with sources?)
win32{
INCLUDEPATH += "C:/Program Files/Eigen/include/eigen3"
CONFIG += console
}
SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
