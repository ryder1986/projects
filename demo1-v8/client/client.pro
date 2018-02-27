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
    formcameragra.cpp \
    formdevicedetail.cpp \
    client.cpp \
    videowidget.cpp

HEADERS  += mainwindow.h \
    formcameragra.h \
    formdevicedetail.h \
    client.h \
    videowidget.h

FORMS    += mainwindow.ui \
    formcameragra.ui \
    formdevicedetail.ui
