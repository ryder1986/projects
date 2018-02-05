#include "camera.h"

Camera::Camera(QJsonObject config)
{
   // cfg=config;
    set_config(config);
    start_cam();
}

