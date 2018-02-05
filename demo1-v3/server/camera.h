#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include "QJsonObject"
#include "videosource.h"
#include "videoprocessor.h"
class Camera : public QObject
{
    Q_OBJECT
public:
    explicit Camera(QJsonObject config,QObject *parent = 0);
    ~Camera()
    {

    }
    void start()
    {
        src=new VideoSource(cfg);
        processor=new VideoProcessor;
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

signals:

public slots:
private:
    VideoSource *src;
    VideoProcessor *processor;
    QJsonObject cfg;
  //  QString url
};
//class FvdCamera:public Cam
#endif // CAMERA_H
