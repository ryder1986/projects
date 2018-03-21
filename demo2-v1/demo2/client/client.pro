#-------------------------------------------------
#
# Project created by QtCreator 2018-03-20T22:17:01
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp client.cpp ServerInfoSearcher.cpp

HEADERS  += mainwindow.h client.h ServerInfoSearcher.h

FORMS    += mainwindow.ui
include(../common/common.pri)

