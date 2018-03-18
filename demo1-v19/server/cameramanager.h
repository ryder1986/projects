#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include <QObject>
#include <QList>
#include <QDebug>
#include "QJsonArray"
#include "camera.h"
#include "pd.h"
class CameraManager : public QObject
{
    Q_OBJECT
public:
    enum{
        MODIFY_ALG,
        MODIFY_URL,
        MODIFY_DIRECTION
    };
    friend class Server;
    explicit CameraManager(QJsonValue config,QObject *parent = 0);
    ~CameraManager()
    {
        stop_cams();
    }
    QJsonValue config()
    {
        return cfg_2_jv();
    }
    void restart_cameras(QJsonValue cfg)
    {
        jv_2_cfg(cfg);//set config
        stop_cams();//stop all cameras
        start_cams();//start all cameras with new config
    }

    void append_camera(QJsonObject cfg)
    {
        insert_camera(cameras.size()+1,cfg);
    }

    void insert_camera(int index,QJsonValue cfg)
    {

     if(index>cameras.size()+1 || index<0){
           prt(fatal,"index %d out of range",index);
     }else{
            prt(fatal,"insert cam  %d  ",index);
            cameras.insert(index,new Camera(cfg));
            cam_cfgs.insert(index,cfg);
     }
    }

//    void insert_camera(int index,QJsonObject cfg)
//    {
//        // check_index(index);
//        if(check_index(index)){
//            cameras.insert(index,new Camera(cfg));
//            cam_cfgs.insert(index,cfg);
//        }
//    }
    void delete_camera(int index)
    {
        //   check_index(index);
        if(check_op_index(index)){
               prt(fatal,"del cam  %d  ",index);
            delete cameras[index-1];
            cameras.removeAt(index-1);
            cam_cfgs.removeAt(index-1);
        }else{

        }
    }
    void modify_camera(int index,QJsonValue v,int mod_type)
    {
        if(index<1|index>cameras.size()){
            prt(error,"index out of rean");
        }
        switch(mod_type){
        case MODIFY_ALG:
            cameras[index-1]->modify_alg(v);
            break;
        case MODIFY_URL:
            cameras[index-1]->modify_url(v);
            break;
        case MODIFY_DIRECTION:
            cameras[index-1]->modify_direction(v);
            break;
        default:break;

        }
        cam_cfgs[index-1]=cameras[index-1]->config();
    }


private:
    void start_cams()
    {
        foreach (QJsonValue v, cam_cfgs)
        {
            cameras.append(new Camera(v));
        }
    }

    void stop_cams()
    {
        prt(info,"cam size %d",cameras.size());
        foreach (Camera *c, cameras)
        {
            delete c;
            prt(info,"cam size %d",cameras.size());
        }
        cameras.clear();
        prt(info,"cam size %d",cameras.size());
    }

    bool check_op_index(int index)
    {
        if(cameras.size()==0)
            return false;
        if(index<1||index>cameras.size()){
            prt(fatal,"index %d out of range(1-%d)",index,cameras.size());
            return false;
        }
        return true;
    }

    //trans config to json value
    QJsonValue cfg_2_jv()
    {
        QJsonValue vl;
        QJsonArray a;
        foreach (QJsonValue v, cam_cfgs) {
            a.append(v);
        }
        vl=a;
        return vl;
    }

    void jv_2_cfg(QJsonValue jv)
    {
        cam_cfgs.clear();
        foreach (QJsonValue v, jv.toArray())
        {
            cam_cfgs.append(v);
        }
    }

signals:
public slots:
private:
    QList <Camera *>cameras;
    QList <QJsonValue> cam_cfgs;
};

#endif // CAMERAMANAGER_H
