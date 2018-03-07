#include "server.h"

Server::Server(FileDatabase *db):database(db),camera_manager(NULL)
{
//    QJsonObject config;
//    QJsonObject camera_profile;
//    database->load(config);
//    cfg.server_name=config["device_name"].toString();
//    cfg.profile=config["profile"].toObject();
//    camera_profile=config.value("profile").toObject();

    load_cfg();

    camera_manager=new CameraManager(cfg.profile);
   // camera_manager->start();

    bool ret=false;
    server=new QTcpServer();
    ret=server->listen(QHostAddress::Any,Protocol::SERVER_PORT);
    if(ret){
        prt(info,"Server listen on port %d success!",Protocol::SERVER_PORT);
    } else {
        prt(fatal,"Server listen on port %d failed!",Protocol::SERVER_PORT);
        exit(1);
    }
    connect(server, &QTcpServer::newConnection, this, &Server::handle_connection);
    service.start();
}

