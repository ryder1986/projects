#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QThread>
#include <QJsonValue>
#include <QTimer>
#include <QJsonObject>
#include <videosource.h>
#include "tool.h"
#include "playerwidget.h"
class Player : public QThread
{

    typedef struct Camera_config{
        QString url;
        int direction;
        int camera_id;
        QString user_name;
        QString password;
        QString camera_ip;
        int camera_port;
        QJsonValue alg;

    }Camera_config_t;
    Camera_config_t cam_cfg;
    QImage img1;
    int frame_rate;
       Q_OBJECT
public:
    Player(QJsonValue cfg){
        frame_rate=0;
        jv_2_cfg(cfg);
        src=new VideoSource(cam_cfg.url);
        wgt=NULL;
        QTimer *t=new QTimer();
        connect(t,SIGNAL(timeout()),this,SLOT(check_rate()));
        t->start(1000);
    }

    ~Player()
    {
        delete wgt;
        delete src;
    }
    QWidget **get_widget()
    {
        return (   QWidget **)&wgt;
    }
public slots:
    void check_rate()
    {
        //frame_rate++;
        prt(info,"frame rate :%d ",frame_rate);
        frame_rate=0;
    }

signals:
private:
    void run()
    {
        Mat bgr_frame;
        Mat rgb_frame;
        this->setObjectName("play_thread");
        while(1){

            if(src->get_frame(bgr_frame)){
                src->get_frame(bgr_frame);
                cvtColor(bgr_frame,rgb_frame,CV_BGR2RGB);
                img1=QImage((const uchar*)(rgb_frame.data),
                            rgb_frame.cols,rgb_frame.rows,
                            QImage::Format_RGB888);
                if(wgt){
                    wgt->set_image(img1);
                    wgt->update();
                    frame_rate++;
                }
            }else{
                this->usleep(10);
            }
        }
    }
    virtual QJsonValue cfg_2_jv()
    {
        QJsonValue jv;
        jv.toObject()["url"]= cam_cfg.url;
        jv.toObject()["direction"]=cam_cfg.direction;
        jv.toObject()["camera_id"]= cam_cfg.camera_id;
        jv.toObject()["user_name"]= cam_cfg.user_name;
        jv.toObject()["password"]= cam_cfg.password;
        jv.toObject()["camera_ip"]= cam_cfg.camera_ip;
        jv.toObject()["camera_port"]= cam_cfg.camera_port;
        jv.toObject()["alg"]=cam_cfg.alg;

        return jv;

    }
    virtual void jv_2_cfg(QJsonValue cfg)
    {
        cam_cfg.url = cfg.toObject()["url"].toString();
        cam_cfg.direction=cfg.toObject()["direction"].toInt();
        cam_cfg.camera_id=cfg.toObject()["camera_id"].toInt();
        cam_cfg.user_name=cfg.toObject()["user_name"].toString();
        cam_cfg.password=cfg.toObject()["password"].toString();
        cam_cfg.camera_ip=cfg.toObject()["camera_ip"].toString();
        cam_cfg.camera_port=cfg.toObject()["camera_port"].toInt();
        cam_cfg.alg=cfg.toObject()["alg"];
    }

    VideoSource *src;
    PlayerWidget *wgt;
};

#endif // PLAYER_H
