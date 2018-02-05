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
public:
    explicit Camera(QJsonObject config);
    ~Camera()
    {

    }
    void start_cam()
    {
        src=new VideoSource(cfg);
        processor=new VideoProcessor;
        start();
     //   src->start();
    }
    void stop()
    {
        delete src;
        delete processor;
        src=NULL;
        processor=NULL;
    }

    virtual void set_config(QJsonObject cfg)
    {

    }
    virtual void get_config(QJsonObject cfg)
    {

    }
protected:
    void run()
    {
        while(1){
            prt(info,"runing %s");
            QThread::sleep(1);
        }
    }

signals:

public slots:
private:
    VideoSource *src;
    VideoProcessor *processor;
  //  QJsonObject cfg;
  //  QString url
};
//class FvdCamera:public Cam
#endif // CAMERA_H
