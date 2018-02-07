#include "camera.h"

Camera::Camera(QJsonObject config)
{
   // cfg=config;
    quit=false;
    set_config(config);
    start_cam();
}

