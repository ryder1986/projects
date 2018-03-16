#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <QTimer>
#include <QMutex>
#include "filedatabase.h"
#include "QJsonObject"
#include "videosource.h"
#include "videoprocessor.h"
#include "processeddatasender.h"
class Camera : public QThread
{
    Q_OBJECT
    typedef struct Camera_config{
        QString url;
        QJsonValue alg;
    }Camera_config_t;
public:
    explicit Camera(QJsonValue config);
    ~Camera()
    {
        stop_cam();
    }

    void modify_alg(QJsonValue cfg)
    {
        cam_cfg.alg=cfg;
        lock.lock();
        delete  processor;
        processor=new PDVideoProcessor(cam_cfg.alg);
        lock.unlock();
    }
    void modify_url(QJsonValue url)
    {
        cam_cfg.url=url.toString();
        lock.lock();
        delete  src;
        src=new VideoSource(cam_cfg.url);
        lock.unlock();
    }
    QJsonValue config()
    {
        return cfg_2_jv();
    }
    void add_watcher(QString ip)
    {
        if(ip_list.contains(ip)){

        }else{
            qDebug()<<"add ip "<<ip;
            ip_list.append(ip);
        }
    }
    void del_watcher(QString ip)
    {
        if(ip_list.contains(ip)){
                ip_list.removeOne(ip);
        }else{
        }
    }
private:
    void start_cam()
    {
        src=new VideoSource(cam_cfg.url);
        processor=new PDVideoProcessor(cam_cfg.alg);
        start();
    }
    void stop_cam()
    {
        delete tmr;
        quit=true;
        this->wait();
        delete src;
        delete processor;
        src=NULL;
        processor=NULL;
    }

    virtual QJsonValue cfg_2_jv()
    {
        QJsonValue jv;
        jv.toObject()["url"]= cam_cfg.url;
        jv.toObject()["alg"]=cam_cfg.alg;
        return jv;

    }
    virtual void jv_2_cfg(QJsonValue cfg)
    {
        cam_cfg.url = cfg.toObject()["url"].toString();
        cam_cfg.alg=cfg.toObject()["alg"];
    }
    void send_out(QByteArray ba)
    {
      //  emit output(ba);
        ProcessedDataSender *s=ProcessedDataSender::get_instance();
        foreach (QString ip, ip_list) {
            QString str(ba);

            prt(info,"send %s to %s",str.toStdString().data(),ip.toStdString().data())
            s->send(ba,QHostAddress(ip));
        }
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

                //prt(info,"get rst %s ",rst.data());
                if(rst.length()>0){
                    ba.clear();
                    ba.append(rst.data());
                  //  emit output(ba);

                send_out(ba);
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
    QList <QString> ip_list;
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
