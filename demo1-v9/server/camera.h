#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <QTimer>
#include "filedatabase.h"
#include "QJsonObject"
#include "videosource.h"
#include "videoprocessor.h"
class Camera : public QThread
{
    Q_OBJECT
    typedef struct Camera_config{
        QString url;
        QJsonObject alg;
    }Camera_config_t;
public:
    explicit Camera(QJsonObject config);
    ~Camera()
    {
        stop();
    }
    void start_cam()
    {
        src=new VideoSource(cam_cfg.url);
        processor=new PDVideoProcessor;
        start();
     //   src->start();
    }
    void stop()
    {
        delete tmr;
        quit=true;
        this->wait();
        delete src;
        delete processor;
        src=NULL;
        processor=NULL;
    }

    virtual void set_config(QJsonObject cfg)
    {
        cam_cfg.url = cfg["url"].toString();
        cam_cfg.alg=cfg["alg"].toObject();
    }
    virtual void get_config(QJsonObject cfg)
    {

    }
protected:
    void run()
    {
        int i=0;
        QByteArray ba;
        src->start();
        Mat frame;
        while(!quit){
         //   prt(info,"runing %s",cam_cfg.url.toStdString().data());
            QThread::msleep(100);


            ba.clear();
            char t='1';

            ba.append(t+i++%9);
            emit output(ba);

            if(src->get_frame(frame)){
                frame_rate++;
                //prt(info,"get a frame");
            }else{
                //prt(info,"get no frame");
            }

//            processor->process();
        }
    }

signals:
    void output(QByteArray ba);
public slots:
    void handle_time_up()
    {
        prt(info,"%s framerate:%d",cam_cfg.url.toStdString().data(),frame_rate);
        frame_rate=0;
    }

private:
    int frame_rate;
    QTimer *tmr;
    VideoSource *src;
    VideoProcessor *processor;
    Camera_config_t cam_cfg;
    bool quit;
  //  QJsonObject cfg;
  //  QString url
};
//class FvdCamera:public Cam
#endif // CAMERA_H
