#-------------------------------------------------
#
# Project created by QtCreator 2018-03-20T22:20:24
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

install_files.files+=config.json  hogcascade_pedestrians.xml
install_files.path=$$OUT_PWD/
INSTALLS +=install_files

