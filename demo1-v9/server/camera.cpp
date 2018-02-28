#include "camera.h"

Camera::Camera(QJsonObject config)
{
    frame_rate=0;
   // cfg=config;
    quit=false;
    set_config(config);
    start_cam();
    tmr=new QTimer;
    connect (tmr,SIGNAL(timeout()),this,SLOT(handle_time_up()));
    tmr->start(1000);

}

