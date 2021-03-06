#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <QTimer>
#include <QMutex>
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

    void modify_alg(QJsonObject cfg)
    {
        cam_cfg.alg=cfg;
        lock.lock();
        delete  processor;
        processor=new PDVideoProcessor(cam_cfg.alg);
        lock.unlock();
    }
    void modify_url(QJsonObject cfg)
    {
        cam_cfg.url= cfg["url"].toString();
        lock.lock();
        delete  src;
        src=new VideoSource(cam_cfg.url);
        lock.unlock();
    }

private:
    void start_cam()
    {
        src=new VideoSource(cam_cfg.url);
        processor=new PDVideoProcessor(cam_cfg.alg);
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
    virtual void get_config(QJsonObject &cfg)
    {
        cfg["url"]=cam_cfg.url;
        cfg["alg"]=cam_cfg.alg;
    }

protected:
    void run()
    {
        int i=0;
        QByteArray ba;
        //   src->start();
        Mat frame;
        threadid=(int)QThread::currentThread();
        string rst;
        while(!quit){
            //   prt(info,"runing %s",cam_cfg.url.toStdString().data());
            //   QThread::msleep(100);


            //            ba.clear();
            //            char t='1';

            //            ba.append(t+i++%9);
            //            emit output(ba);
            lock.lock();
            if(src->get_frame(frame)){
                frame_rate++;
                rst=processor->process(frame);

                prt(info,"get rst %s ",rst.data());
                if(rst.length()>0){
                    ba.clear();
                    ba.append(rst.data());
                    emit output(ba);
                }
            }else{
                //prt(info,"get no frame");
            }
            lock.unlock();

        }
        QThread::msleep(10);
    }

signals:
    void output(QByteArray ba);
public slots:
    void handle_time_up()
    {
        prt(info,"%s framerate:%d,(id:%x)",cam_cfg.url.toStdString().data(),frame_rate,threadid);

        frame_rate=0;
    }

private:
    int frame_rate;
    int threadid;
    QTimer *tmr;
    VideoSource *src;
    VideoProcessor *processor;
    Camera_config_t cam_cfg;
    bool quit;
    QMutex lock;
    //  auto frame=1;
    //  QJsonObject cfg;
    //  QString url
};
//class FvdCamera:public Cam
#endif // CAMERA_H
