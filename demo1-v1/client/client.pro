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
    formcameratext.cpp \
    formdevicedetail.cpp \
    formdevicedetree.cpp \
    client.cpp

HEADERS  += mainwindow.h \
    formcameragra.h \
    formcameratext.h \
    formdevicedetail.h \
    formdevicetree.h \
    client.h

FORMS    += mainwindow.ui \
    formcameragra.ui \
    formcameratext.ui \
    formdevicedetail.ui \
    formdevicetree.ui
