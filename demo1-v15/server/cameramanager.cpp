#include "cameramanager.h"

CameraManager::CameraManager(QJsonValue cfg,QObject *parent) : QObject(parent)
{
    cameras.clear();
    jv_2_cfg(cfg);
    start_cams();
}

