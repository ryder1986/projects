SOURCES+=\
$$PWD/tool1.cpp\
$$PWD/filedatabase.cpp\
$$PWD/videosource.cpp\
$$PWD/pd.cpp
HEADERS+=\
$$PWD/tool1.h\
$$PWD/filedatabase.h\
$$PWD/videosource.h\
$$PWD/pd.h
$$PWD/alg.h
unix{
DEFINES +=IS_UNIX
}
win32{
DEFINES +=IS_WIN32
}

INCLUDEPATH+=$$PWD
CONFIG+=c++11
QT+=network


install_files.files+=config.json  hogcascade_pedestrians.xml
install_files.path=$$OUT_PWD/
INSTALLS +=install_files

win32{
OPENCV_PATH=E:\repo-github\libs\third-party\opencv\opencv-vs2013-x86
    INCLUDEPATH +="$$OPENCV_PATH\include"
    LIBS+=-L$$OPENCV_PATH\lib   -lopencv_core249d -lopencv_highgui249d \
        -lopencv_objdetect249d -lopencv_imgproc249d -lopencv_ml249d  -lopencv_video249d
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

win32{
#PROJECT_ROOT="Z:\\"
CVPATH="Z:\libs\third-party\opencv"
CV_PREFIX="\opencv-vs2013-x86"
ALGPATH="Z:\libs\third-party\alg"
ALGPATH="Z:\libs\alg"
#COMMON_LIB_PATH="Z:\res\common\lib-win32"
##DESTDIR=Z:\build
}

unix{
DEFINES +=IS_UNIX
QMAKE_CXXFLAGS+=-w
}

win32{
DEFINES +=IS_WIN32
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

#win32{
#    INCLUDEPATH +="$$CVPATH\\$$CV_PREFIX\include"
#    INCLUDEPATH +="$$ALGPATH/include"
#INCLUDEPATH +="Y:\libs\third-party\opencv\opencv-vs2013-x86\include"
#    message(includepath:$$INCLUDEPATH)
#    CONFIG(debug, debug|release){
#        LIBS+=-L$$CVPATH\\$$CV_PREFIX\lib -lopencv_core249d -lopencv_highgui249d\
#        -lopencv_objdetect249d -lopencv_imgproc249d -lopencv_ml249d  -lopencv_video249d


#        LIBS+=-LY:\libs\third-party\opencv\opencv-vs2013-x86\lib  -lopencv_core249d -lopencv_highgui249d\
#        -lopencv_objdetect249d -lopencv_imgproc249d -lopencv_ml249d  -lopencv_video249d
#    }else{
#        LIBS+=-L$$CVPATH\\$$CV_PREFIX\lib  -lopencv_core249 -lopencv_highgui249 \
#        -lopencv_objdetect249 -lopencv_imgproc249 -lopencv_ml249  -lopencv_video249

#        LIBS+=-LY:\libs\third-party\opencv\opencv-vs2013-x86\lib  -lopencv_core249 -lopencv_highgui249 \
#        -lopencv_objdetect249 -lopencv_imgproc249 -lopencv_ml249  -lopencv_video249
#    }
#}
