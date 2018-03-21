#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QThread>
#include <QJsonValue>
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
public:
    Player(QJsonValue cfg){
        jv_2_cfg(cfg);
        src=new VideoSource(cam_cfg.url);
        this->start();
      //  wgt=new PlayerWidget();
      //  emit get_box(wgt);
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
signals:
    void get_box(QWidget *w);
   // void need_update();
private:
    void run()
    {
            while(1){
              QThread::sleep(1);
        //  emit need_update();
              //   wgt->update();
              prt(info,"11111111111111111111111111111");
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
