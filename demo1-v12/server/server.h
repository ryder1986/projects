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

class Server:public QObject
{
    Q_OBJECT
public:

    Server(FileDatabase *db);
    ~Server()
    {
        delete camera_manager;
    }

public slots:
    int handle_client_request(QByteArray request,QByteArray &ret,void *addr)
    {

        QJsonDocument doc=QJsonDocument::fromJson(request);
        QJsonObject obj= doc.object();
        int type=obj["type"].toInt();
        QJsonObject pkg;
        pkg["type"]=type;
        switch(type)
        {
        case Protocol::GET_CONFIG:
        {
            QJsonObject config;
            database->get_config(config);

            pkg["config"]=config;
            //  camera_manager->get_config(config);
        }
            break;
        case Protocol::SET_CONFIG:
        {
            QJsonObject config=obj["config"].toObject();
            database->set_config(config);
            camera_manager->restart(config["profile"].toObject());
            break;
        }

        case Protocol::CAM_OUTPUT_OPEN:
        {
            ClientSession *s=(ClientSession *)addr;
            int idx=obj["cam_index"].toInt()-1;
            connect(camera_manager->cameras[idx],SIGNAL(output(QByteArray)),s,SLOT(handle_alg_out(QByteArray)));
            break;
        }
        case Protocol::CAM_OUTPUT_CLOSE:
        {
            ClientSession *s=(ClientSession *)addr;
            int idx=obj["cam_index"].toInt()-1;
            disconnect(camera_manager->cameras[idx],SIGNAL(output(QByteArray)),s,SLOT(handle_alg_out(QByteArray)));
            break;
        }

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
    QTcpServer *server;//server for reply all clients request ,execute client cmds,like add cam,del cam, reconfigure cam,etc..

    FileDatabase *database;//hold config data;
    CameraManager *camera_manager;//hold cameras
    QList <ClientSession *> clients;//hold sessions

    char recv_buf[Pd::BUFFER_MAX_LENGTH];
    char send_buf[Pd::BUFFER_MAX_LENGTH];
    LocationService service;

};


#endif // SERVER_H
