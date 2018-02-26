#ifndef VIDEOSOURCE_H
#define VIDEOSOURCE_H

#include <QObject>
#include <QThread>
#include <QJsonObject>
#include "tool1.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/objdetect/objdetect.hpp>

using namespace std;
using namespace cv;

class VideoSource : public QThread
{
    Q_OBJECT
public:
    VideoCapture vcap;

    QList <Mat> frame_list;
    int frame_wait_time;
    explicit VideoSource(QJsonObject config);
    VideoSource(QString path)
    {
        url=path;
    }

    void set_config(const QJsonObject config)
    {
        url=config["url"].toString();
    }
    void get_config(QJsonObject &config)
    {

    }
    void get_frame(char *yuv)
    {

    }
    bool get_frame(Mat &frame)
    {
        if(frame_list.size()>5){
            frame=frame_list.first();
            frame_list.pop_front();
            return true;
        }else{
            return false;
        }
    }

private:
    void run()
    {

        vcap=   VideoCapture( url.toStdString().data());
        QString str( url.data());
        if(str.contains("rtsp")||str.contains("http")){
            frame_wait_time=0;
        }else{
            frame_wait_time=40;
        }
        Mat mat_rst;
        int flag_retry=0;
        while(!quit_flg){
            // prt(info,"runing thread %s",url.toStdString().data());
            //QThread::sleep(1);
            //  while(! quit_flag){
            if( vcap.isOpened()){
                flag_retry=0;
                bool rt= vcap.read(mat_rst);
                if(!rt){
                    prt(info,"get frame fail,restart video capture %s", url.toStdString().data()); \
                    vcap.release();  vcap=   VideoCapture( url.toStdString().data());
                }
                if(mat_rst.cols==0){
                    vcap.release();
                    prt(info,"%s get frame error,retrying ... ", url.data());
                    continue;
                    prt(info,"restarting %s      ", url.toStdString().data());
                }else{
                    if(frame_list.size()<10){
                        frame_list.push_back(mat_rst);
                    }
                    if(frame_wait_time)
                        this_thread::sleep_for(chrono::milliseconds( frame_wait_time));
                }
            }else{
                if(flag_retry++<10){
                    this_thread::sleep_for(chrono::milliseconds(100));
                }else{
                    this_thread::sleep_for(chrono::seconds(1));
                }
                vcap=   VideoCapture( url.toStdString().data());
            }
        }
        if( vcap.isOpened())
            vcap.release();
    }

signals:

public slots:
private:
    QString url;
    bool quit_flg;
};

#endif // VIDEOSOURCE_H
