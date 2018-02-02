#include "camera.h"

Camera::Camera(QJsonObject config,QObject *parent) : QObject(parent)
{
    cfg=config;
    start();
}

