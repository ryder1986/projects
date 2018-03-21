#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include "pd.h"
#include "filedatabase.h"
#include "cameramanager.h"
#include "clientsession.h"
class LocationService : public QObject{
    Q_OBJECT
public:
    LocationService(){
        timer=new QTimer();
        connect(timer,SIGNAL(timeout()),this,SLOT(check_client_msg()));//TODO:maybe replace with readReady signal
        udp_skt = new QUdpSocket();
        udp_skt->bind(Protocol::SERVER_REPORTER_PORT,QUdpSocket::ShareAddress);
    }
    ~LocationService()
    {
        disconnect(timer);
        delete timer;
        delete udp_skt;
    }
    void start()
    {
        timer->start(100);
    }

    void stop()
    {
        timer->stop();
    }

public  slots:
    void check_client_msg()
    {
        QByteArray client_msg;
        char *msg;
        if(udp_skt->hasPendingDatagrams())
        {
            client_msg.resize((udp_skt->pendingDatagramSize()));
            QHostAddress sender;
            quint16 senderPort;
            udp_skt->readDatagram(client_msg.data(),client_msg.size(),&sender,&senderPort);
            prt(info,"get client broadcasted code :%s",msg=client_msg.data());
            if(!strcmp(msg,"pedestrian")){

                //    send_info_to_client();
                send_info_to_client(sender);
            }
            else{
                prt(error,"client code :%s NOT MATCH pedestrian,we will not answer",msg=client_msg.data());
            }
            //   udp_skt->flush();
        }else{
            //prt(debug,"searching client on port %d",Protocol::SERVER_REPORTER_PORT)
        }
    }

    void send_info_to_client()
    {
        QByteArray datagram;
        datagram.clear();
        QList <QNetworkInterface>list_interface=QNetworkInterface::allInterfaces();
        foreach (QNetworkInterface i, list_interface) {
            if(i.name()!="lo"){
                QList<QNetworkAddressEntry> list_entry=i.addressEntries();
                foreach (QNetworkAddressEntry e, list_entry) {
                    if(e.ip().protocol()==QAbstractSocket::IPv4Protocol)
                    {
                        datagram.append(QString(e.ip().toString())).append(QString(",")).\
                                append(QString(e.netmask().toString())).append(QString(",")).append(QString(e.broadcast().toString()));
                    }

                }
            }
        }
#if 1
        //broadcast
        udp_skt->writeDatagram(datagram.data(), datagram.size(),
                               QHostAddress::Broadcast, Protocol::CLIENT_REPORTER_PORT);
#else
        //send to single ip. problem in windows
#endif
    }
    void send_info_to_client(const QHostAddress &addr)
    {
        QByteArray datagram;
        datagram.clear();
        QList <QNetworkInterface>list_interface=QNetworkInterface::allInterfaces();
        foreach (QNetworkInterface i, list_interface) {
            if(i.name()!="lo"){
                QList<QNetworkAddressEntry> list_entry=i.addressEntries();
                foreach (QNetworkAddressEntry e, list_entry) {
                    if(e.ip().protocol()==QAbstractSocket::IPv4Protocol)
                    {
                        datagram.append(QString(e.ip().toString())).append(QString(",")).\
                                append(QString(e.netmask().toString())).append(QString(",")).append(QString(e.broadcast().toString()));
                    }

                }
            }
        }
#if 1
        //     /   qDebug()<<"addr :"<<addr.toString();
        //broadcast
        udp_skt->writeDatagram(datagram.data(), datagram.size(),
                               addr, Protocol::CLIENT_REPORTER_PORT);
#else
        //send to single ip. problem in windows
#endif
    }
private:
    QTimer *timer;
    QUdpSocket *udp_skt;
};
//class Dest:public QObject{
//    struct dst{
//        QString dst_ip;
//        Camera *cam_addr;
//    };
//    Q_OBJECT
//public:
//    Dest(){

//    }
//    void add_dst(QString ip,Camera *cam)
//    {
//        bool flg=false;
//        foreach (struct dst d, list) {
//            if(d.dst_ip==ip){
//                if(cam!=d.cam_addr){
//                    d.cam_addr=cam;
//                }
//                flg=true;
//                break;
//            }
//        }
//        if(!flg){
//            struct dst tmp;
//            tmp.dst_ip=ip;
//            tmp.cam_addr=cam;
//            list.append(tmp);
//        }
//    }
//    void del_dest(QString ip)
//    {

//    }
//public slots:
//    void send_rst()
//    {

//    }
//    void send_2_dest(QByteArray ba)
//    {
//        ProcessedDataSender*sender= ProcessedDataSender::get_instance();
//        sender->send(ba,);
//    }
//private:
//    QList <struct dst> list;
//};
class Server:public QObject
{
    Q_OBJECT
    typedef struct configure{
        QString server_name;
        int dev_id;
        QString sig_ip;
        int sig_port;
        QString ntp_ip;
        int ntp_port;
        QJsonValue cams_cfg;
    }configture_t;
    // Dest dst;
public:

    Server(FileDatabase *db);
    ~Server()
    {
        delete camera_manager;
    }

public slots:
    int handle_client_request(QByteArray request,QByteArray &ret,void *addr)
    {

        ClientSession *cs=(ClientSession *)addr;
        //    int client_index=clients.indexOf((ClientSession *)addr);
        QJsonDocument doc=QJsonDocument::fromJson(request);
        QJsonObject obj= doc.object();
        int type=obj["type"].toInt();

        QJsonObject pkg;
        pkg["type"]=type;

        bool config_changed=false;
        switch(type){
        case Protocol::GET_CONFIG:// if client wants get config, client is ok
            cs->set_valid(true);
            break;
        case Protocol::SET_CONFIG:
        case Protocol::INSERT_CAMERA:
        case Protocol::DELETE_CAMERA:
        case Protocol::MOD_CAMERA_ALG:
        case Protocol::MOD_CAMERA_ATTR:
        default:
            if(cs->is_valid())
                config_changed=true;// if client is valid , change can be made
            break;
        }

        if(config_changed){//if valid change happen, other clients will be invalid
            foreach (ClientSession *session, clients) {
                if(session!=addr)
                    session->set_valid(false);
            }
        }
        if(!cs->is_valid()&&type!=Protocol::GET_CONFIG){// no valid, no update
            QJsonObject obj;
            obj["type"]=Protocol::NEED_UPDATE;
            QJsonDocument doc_ret(obj);
            ret=doc_ret.toJson();//tell client to update
            return 1;
        }

        switch(type){
        case Protocol::GET_CONFIG:
        {
            //            QJsonValue v1;
            //            QJsonValue v2;
            //            cfg_2_jv(v1,v2);
            QJsonObject cfg;
            cfg_2_obj(cfg);
            pkg["config"]=cfg;

            //            cfg["device_name"]=v1;
            //            cfg["cameras"]=v2;
            //            pkg["config"]=cfg;
            break;
        }

        case Protocol::SET_CONFIG:
        {
            //jv_2_cfg(obj["config"]);
            obj_2_cfg(obj["config"].toObject());
            save_cfg();
            camera_manager->restart_cameras(cfg.cams_cfg);
            break;
        }

        case Protocol::CAM_OUTPUT_OPEN:
        {

            int idx=obj["cam_index"].toInt();
            if(idx<=camera_manager->cameras.size())
                camera_manager->cameras[idx-1]->add_watcher(cs->ip());
            //    connect(camera_manager->cameras[idx-1],SIGNAL(output(QByteArray)),s,SLOT(handle_alg_out(QByteArray)));
            //   dst.set_pair(s->ip(),camera_manager->cameras[idx-1]);
            break;
        }
        case Protocol::CAM_OUTPUT_CLOSE:
        {
            int idx=obj["cam_index"].toInt();
            if(idx<=camera_manager->cameras.size())
                camera_manager->cameras[idx-1]->del_watcher(cs->ip());
            //  disconnect(camera_manager->cameras[idx-1],SIGNAL(output(QByteArray)),s,SLOT(handle_alg_out(QByteArray)));
            break;
        }

        case Protocol::MOD_CAMERA_ALG:
        {
            int idx=obj["cam_index"].toInt();
            // QJsonObject alg=obj["alg"].toObject();
            camera_manager->modify_camera(idx,obj["alg"],CameraManager::MODIFY_ALG);
            QJsonValue jv= camera_manager->config();
            // jv_2_cfg(jv);
            cfg.cams_cfg=jv;
            save_cfg();

            break;
        }

            //        case Protocol::MOD_CAMERA_DIRECTION:
            //        {
            //            int idx=obj["cam_index"].toInt();
            //            camera_manager->modify_camera(idx,obj["direction"],CameraManager::MODIFY_DIRECTION);
            //            QJsonValue jv= camera_manager->config();
            //            jv_2_cfg(jv);
            //            save_cfg();

            //            break;
            //        }

        case Protocol::MOD_CAMERA_ATTR:
        {
            int idx=obj["cam_index"].toInt();
            camera_manager->modify_camera(idx,obj["url"],CameraManager::MODIFY_URL);
            QJsonValue jv= camera_manager->config();
            cfg.cams_cfg=jv;
            //  jv_2_cfg(jv);
            save_cfg();
            break;
        }
        case Protocol::INSERT_CAMERA:
        {
            int idx=obj["cam_index"].toInt();
            QJsonValue v=obj["camera"];
            camera_manager->insert_camera(idx,v);
            QJsonValue jv= camera_manager->config();
            cfg.cams_cfg=jv;
            //  QJsonValue jv_name=cfg.server_name;
            //   jv_2_cfg(jv_name,jv);
            save_cfg();
            break;
        }
        case Protocol::DELETE_CAMERA:
        {
            int idx=obj["cam_index"].toInt();
            camera_manager->delete_camera(idx);
            QJsonValue jv=camera_manager->config();
            cfg.cams_cfg=jv;
            save_cfg();
            break;
        }
        case Protocol::HEART:
        {

            break;
        }

        case Protocol::REBOOT:
        {

            break;
        }

        case Protocol::MOD_DEVICE_ATTR:
        {

            break;
        }
            //        case Protocol::NEED_UPDATE:
            //        {

            //            break;
            //        }

        default:break;
        }
        QJsonDocument doc_ret(pkg);
        ret=doc_ret.toJson();
        return 0;
    }

    void handle_connection()
    {
        QTcpSocket *skt = server->nextPendingConnection();
        connect(skt, SIGNAL(disconnected()),skt, SLOT(deleteLater()));
        QString str(skt->peerAddress().toString());
        prt(info,"client %s:%d connected",str.toStdString().data(),skt->peerPort());
        ClientSession *client=new ClientSession(skt);
        connect(client,SIGNAL(socket_error(ClientSession*)),this,SLOT(delete_client(ClientSession*)));
        connect(skt,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));

        connect(client,SIGNAL( client_request(QByteArray,QByteArray&,void *)),this,
                SLOT(handle_client_request(QByteArray,QByteArray&,void *)),Qt::DirectConnection);//important,in case of competition bugs
        clients.append(client);
    }

    void delete_client(ClientSession *c)
    {
        prt(info,"client %s disconnected",c->ip().toStdString().data());
        delete c ;
        clients.removeOne(c);
    }

    void  displayError(QAbstractSocket::SocketError socketError)
    {
        //prt(info,"client %s disconnected",c->ip().toStdString().data());
        //      prt(info,"client error");
        switch (socketError) {
        case QAbstractSocket::RemoteHostClosedError:
            prt(info,"client closed");
            break;
        case QAbstractSocket::HostNotFoundError:
            prt(info,"client error");
            break;
        case QAbstractSocket::ConnectionRefusedError:
            prt(info,"client error");
            break;
        default:
            break;
        }
    }

private:
    void load_cfg()
    {
        QJsonObject obj;
        database->load(obj);
        //        QJsonObject o=obj["config"].toObject();
        //        jv_2_cfg(o["dev_name"],o["cameras"]);
        //jv_2_cfg(obj["config"]);
        obj_2_cfg(obj);
    }

    void save_cfg()
    {
        QJsonObject cfg;

        //        QJsonValue v1;
        //        QJsonValue v2;
        //        cfg_2_jv(v1,v2);
        //        QJsonObject obj;
        //        obj["device_name"]=v1;
        //        obj["cameras"]=v2;
        //        cfg["config"]=obj;


        cfg_2_obj(cfg);
        database->save(cfg);
    }
    //    void jv_2_cfg(QJsonValue config)
    //    {
    //        cfg.server_name=config.toObject()["device_name"].toString();
    //        cfg.cams_cfg=config.toObject()["cameras"];
    //    }

    //    void jv_2_cfg(QJsonValue jv_devname,QJsonValue jv_cams)
    //    {
    //        cfg.server_name=jv_devname.toString();
    //        cfg.cams_cfg=jv_cams.toArray();
    //    }\
    //    void cfg_2_jv(QJsonValue &jv_devname,QJsonValue &jv_cams)
    //    {
    //        QJsonObject obj;
    //        jv_devname=obj["device_name"] = cfg.server_name;
    //        jv_cams=obj["cameras"]=cfg.cams_cfg;

    //    }

    void cfg_2_obj(QJsonObject &obj)
    {

        obj["device_name"]=cfg.server_name;
        obj["deviceID"]=cfg.dev_id;
        obj["signal_machine_ip"]=cfg.sig_ip;
        obj["signal_machine_port"]=cfg.sig_port;
        obj["ntp_ip"]=cfg.ntp_ip;
        obj["ntp_port"]=cfg.ntp_port;
        obj["cameras"]=cfg.cams_cfg;


    }

    void obj_2_cfg(QJsonObject obj)
    {


        cfg.server_name=obj["device_name"].toString();
        cfg.dev_id=obj["deviceID"].toInt();
        cfg.sig_ip=obj["signal_machine_ip"].toString();
        cfg.sig_port= obj["signal_machine_port"].toInt();
        cfg.ntp_ip=obj["ntp_ip"].toString();
        cfg.ntp_port=obj["ntp_port"].toInt();
        cfg.cams_cfg=obj["cameras"];
    }


    QTcpServer *server;//server for reply all clients request ,execute client cmds,like add cam,del cam, reconfigure cam,etc..

    FileDatabase *database;//hold config data;
    CameraManager *camera_manager;//hold cameras
    QList <ClientSession *> clients;//hold sessions
    configture_t cfg;
    char recv_buf[Pd::BUFFER_MAX_LENGTH];
    char send_buf[Pd::BUFFER_MAX_LENGTH];
    LocationService service;

};


#endif // SERVER_H
