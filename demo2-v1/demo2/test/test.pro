#-------------------------------------------------
#
# Project created by QtCreator 2018-03-20T22:42:07
#
#-------------------------------------------------

QT       += core gui
CONFIG +=c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp ../common/tool.cpp

HEADERS  += mainwindow.h ../common/tool.h

FORMS    += mainwindow.ui
unix{
    DEFINES+=IS_UNIX
}
INCLUDEPATH +=../common
