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
        MODIFY_URL
    };
    friend class Server;
    explicit CameraManager(QJsonObject config,QObject *parent = 0);
    ~CameraManager()
    {
        stop();
    }

    void get_config(QJsonObject &config)
    {
        config["cameras"]=array;
    }

    void set_config(QJsonObject config)
    {
        stop();
        array=config["cameras"].toArray();
        start();
    }
    void append_camera(QJsonObject cfg)
    {
        insert_camera(cameras.size()+1,cfg);
    }

    void insert_camera(int index,QJsonObject cfg)
    {
        check_index(index);
        cameras.insert(index-1,new Camera(cfg));
    }
    void delete_camera(int index)
    {
        check_index(index);
        cameras.removeAt(index-1);
    }
    void modify_camera(int index,QJsonObject cfg,int mod_type)
    {
        if(index<1|index>cameras.size()){
            prt(error,"index out of rean");
        }
        switch(mod_type){
            case MODIFY_ALG:
                cameras[index-1]->modify_alg(cfg);
                break;
        case MODIFY_URL:
            cameras[index-1]->modify_url(cfg);
            break;
            default:break;

        }
    }

private:
    void check_index(int index)
    {
        if(index<1||index>cameras.size()){
            prt(info,"index out of range");
        }
    }

    void start()
    {
        //cameras.append(new Camera(onfig));

        foreach (QJsonValue v, array)
        {
            cameras.append(new Camera(v.toObject()));
        }
    }
    void stop()
    {
        foreach (Camera *c, cameras)
        {
            delete c;

        }
        cameras.clear();
    }


signals:

public slots:
private:
    QList <Camera *>cameras;
    QJsonArray array;
};

#endif // CAMERAMANAGER_H
