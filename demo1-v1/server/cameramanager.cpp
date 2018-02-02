#include "cameramanager.h"

CameraManager::CameraManager(QJsonObject config,QObject *parent) : QObject(parent)
{
    cameras.clear();
    set_config(config);
}

