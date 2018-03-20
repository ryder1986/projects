#-------------------------------------------------
#
# Project created by QtCreator 2018-03-19T10:30:39
#
#-------------------------------------------------

QT       += core gui network
CONFIG +=c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client-demo
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
    tool1.cpp \
    serverinfosearcher.cpp \
    pd.cpp \
    client.cpp \
    player.cpp \
    videosource.cpp

HEADERS += \
        mainwindow.h \
    tool1.h \
    serverinfosearcher.h \
    pd.h \
    client.h \
    player.h \
    videosource.h

FORMS += \
        mainwindow.ui
win32{
OPENCV_PATH=E:\repo-github\libs\third-party\opencv\opencv-vs2013-x86
INCLUDEPATH+="C:\Program Files\Microsoft SDKs\Windows\v7.1A\Include"
    INCLUDEPATH +="$$OPENCV_PATH\include"
    LIBS+=-L$$OPENCV_PATH\lib   -lopencv_core249d -lopencv_highgui249d \
        -lopencv_objdetect249d -lopencv_imgproc249d -lopencv_ml249d  -lopencv_video249d


#    LIBS+=-L$$OPENCV_PATH\lib   -lopencv_core249 -lopencv_highgui249 \
#        -lopencv_objdetect249 -lopencv_imgproc249 -lopencv_ml249  -lopencv_video249
 message(includepath->>>>>>:$$INCLUDEPATH)
}


unix{
#PROJECT_ROOT="/root/repo-github"
CVPATH="/root/repo-github/libs/third-party/opencv"
CV_PREFIX="/opencv-linux-x86"
ALGPATH="/root/repo-github/libs/alg"
#COMMON_LIB_PATH="/root/repo-github/res/common/lib-linux32"
##DESTDIR=/root/repo-github/build/
}


unix{
    DEFINES += IS_UNIX
    QMAKE_CXXFLAGS+="-std=c++11"
    INCLUDEPATH +="$$CVPATH/$$CV_PREFIX/include"
    INCLUDEPATH +="$$ALGPATH/include"
    message(alg  in $$ALGPATH/include)
    LIBS+=-L$$CVPATH/$$CV_PREFIX/lib -lopencv_core -lopencv_highgui \
       -lopencv_objdetect -lopencv_imgproc -lopencv_ml   -lopencv_video  -lX11

    QMAKE_LIBS+=-lpthread
}
