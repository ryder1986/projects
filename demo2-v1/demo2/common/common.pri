message($$PWD)
INCLUDEPATH+=$$PWD
HEADERS+=$$PWD/tool.h

SOURCES+=$$PWD/tool.cpp
CONFIG+=c++11
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
