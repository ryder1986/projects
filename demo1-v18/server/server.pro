#-------------------------------------------------
#
# Project created by QtCreator 2018-02-01T15:31:02
#
#-------------------------------------------------
include(../misc/misc.pri)
QT       += core

QT       -= gui

TARGET = server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    videoprocessor.cpp \
    server.cpp \
    clientsession.cpp \
    cameramanager.cpp \
    camera.cpp \
    processeddatasender.cpp \
    fvdvideoprocessor.cpp

HEADERS += \
    videoprocessor.h \
    server.h \
    clientsession.h \
    cameramanager.h \
    camera.h \
    processeddatasender.h \
    fvdvideoprocessor.h

INCLUDEPATH += "C:\Program Files\Microsoft SDKs\Windows\v7.1A\Include"
