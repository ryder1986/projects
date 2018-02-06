#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
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

    }
    void start_cam()
    {
        src=new VideoSource(cam_cfg.url);
        processor=new VideoProcessor;
        start();
     //   src->start();
    }
    void stop()
    {
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
        while(1){
         //   prt(info,"runing %s",cam_cfg.url.toStdString().data());
            QThread::msleep(100);


            ba.clear();
            char t='1';

            ba.append(t+i++%9);
            emit output(ba);
        }
    }

signals:
    void output(QByteArray ba);
public slots:
private:
    VideoSource *src;
    VideoProcessor *processor;
    Camera_config_t cam_cfg;
    bool quit;
  //  QJsonObject cfg;
  //  QString url
};
//class FvdCamera:public Cam
#endif // CAMERA_H
