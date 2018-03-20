#-------------------------------------------------
#
# Project created by QtCreator 2018-02-01T15:30:49
#
#-------------------------------------------------
include(../misc/misc.pri)
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    formdevicedetail.cpp \
    client.cpp \
    videowidget.cpp \
    formcameradetail.cpp

HEADERS  += mainwindow.h \
    formdevicedetail.h \
    client.h \
    videowidget.h \
    formcameradetail.h

FORMS    += mainwindow.ui \
    formdevicedetail.ui \
    formcameradetail.ui
INCLUDEPATH += "C:\Program Files\Microsoft SDKs\Windows\v7.1A\Include"
