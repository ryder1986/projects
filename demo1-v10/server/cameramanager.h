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
    void restart(QJsonObject config)
    {
        stop();
        set_config(config);
        start();
    }
private:
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

    void set_config(QJsonObject config)
    {
        array=config["cameras"].toArray();
    }
signals:

public slots:
private:
    QList <Camera *>cameras;
    QJsonArray array;
};

#endif // CAMERAMANAGER_H
