#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include <QObject>
#include <QList>
#include <QDebug>
#include "QJsonArray"
#include "camera.h"

class CameraManager : public QObject
{
    Q_OBJECT
public:
    explicit CameraManager(QJsonObject onfig,QObject *parent = 0);
    void start()
    {
       //cameras.append(new Camera(onfig));

       foreach (QJsonObject o, configs)
       {
            cameras.append(new Camera(o));
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

    void set_config(QJsonObject config)
    {
        QJsonArray cams_config=config["cameras"].toArray();
        foreach (QJsonValue v, cams_config)
        {
            QJsonObject o=v.toObject();
         //   prt(info,o["url"].toString().toStdString().data());

            configs.append(o);
        }

    }
    void get_config(QJsonObject &config)
    {
        QJsonArray array;
        foreach (QJsonObject o,configs) {
            array.append(o);
        }
        config["cameras"]=array;
//        foreach (Camera c, cameras) {
//            QJsonObject o;
//            c.get_config(o);

//        }
    }
    void add_camera(QJsonObject o)
    {
        cameras.append(new Camera(o));
        configs.append(o);
    }
    void del_camera(int index)
    {
        delete cameras[index-1];
        configs.removeAt(index-1);
    }
    void mod_camera(int index,QJsonObject o)
    {

    }
signals:

public slots:
private:
    QList <Camera *>cameras;
    QList  <QJsonObject>configs;
};

#endif // CAMERAMANAGER_H
