#include "camera.h"

Camera::Camera(QJsonValue jv)
{
    frame_rate=0;
    quit=false;

    jv_2_cfg(jv);
    start_cam();
    tmr=new QTimer;
    connect (tmr,SIGNAL(timeout()),this,SLOT(handle_time_up()));
    tmr->start(1000);

}

