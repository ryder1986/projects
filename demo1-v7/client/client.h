#ifndef CLIENT_H
#define CLIENT_H
#include <QObject>
#include <QtNetwork>
#include <tool1.h>
#include "pd.h"
class Client : public QObject
{
    Q_OBJECT
public:
    char buf[2000];
    Client()
    {
        server_ip.clear();
        tcp_socket=new QTcpSocket();
        in.setDevice(tcp_socket);
        in.setVersion(QDataStream::Qt_1_0);
        connect(tcp_socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));
        connect(tcp_socket,SIGNAL(readyRead()),this,SLOT(handle_server_msg()),Qt::DirectConnection);
    }

    void get_config()
    {

        int request_length=Protocol::encode_configuration_request(buf);//encoder buffer
        bool ret= send(buf,request_length);//talk to server
        if(!ret){
            prt(info,"fail send");
        }
        //    return rst.remove(0,Protocol::HEAD_LENGTH);//TODO:get the ret value;
    }
    void set_config(QByteArray cfg)
    {

        int request_length=Protocol::encode(buf, Protocol::SET_CONFIG,0);//encoder buffer
        bool ret= send(buf,request_length);//talk to server
        if(!ret){
            prt(info,"fail send");
        }
    }
    void focus_camera(int cam_index)
    {
        int request_length=Protocol::encode(buf,Protocol::CAM_OUTPUT_OPEN,cam_index);//encoder buffer
        bool ret= send(buf,request_length);//talk to server
        if(!ret){
            prt(info,"fail send");
        }
    }

    void add_camera(QByteArray camera_config)
    {

    }
    void del_camera(int index)
    {

    }
    void mod_camera(QByteArray new_camera_config,int index)
    {

    }

public slots:
    void handle_connected()
    {
        prt(info,"connected");
    }

    void handle_server_msg()
    {

        lock.lock();
        ret_ba=tcp_socket->readAll();
        QJsonDocument doc=QJsonDocument::fromJson(ret_ba);
        QJsonObject obj=doc.object();
        prt(info,"get %d bytes ",ret_ba.size());
        if(ret_ba.size()>0)
            need_read=true;
        lock.unlock();
        //        prt(info,"state %d",tcp_socket->state());
        int op=obj["type"].toInt();
        switch(op)
        {
        case Protocol::GET_CONFIG:
          //  emit get_config_done(true,ret_ba);
            break;
        default:break;
        }
        //        if(ret_ba.size()>0)
        //            emit server_msg(ret_ba.remove(0,Protocol::HEAD_LENGTH),Protocol::get_operation(ret_ba.data()));
    }

    void connect_to_server(QString ip)
    {
        if(ip.size()){
            //  prt(info,"state %d ",tcp_socket->state());
            if(tcp_socket->state()==QAbstractSocket::ConnectedState)
                tcp_socket->disconnectFromHost();
            //     prt(info,"new ip %s connect (%d)",server_ip.toStdString().data(),tcp_socket->state());
            if(ip==server_ip){
                prt(info,"reconnecting %s",server_ip.toStdString().data());
                tcp_socket->connectToHost(server_ip,Protocol::SERVER_PORT);
            }else{
                prt(info,"connecting %s",ip.toStdString().data());
                server_ip=ip;
                tcp_socket->connectToHost(server_ip,Protocol::SERVER_PORT);
            }

        }else{
        }
    }
    void  displayError(QAbstractSocket::SocketError socketError)
    {
        prt(info,"err when connecting to server");
        switch (socketError) {
        case QAbstractSocket::RemoteHostClosedError:
            break;
        case QAbstractSocket::HostNotFoundError:
            qDebug()<<"1";
            break;
        case QAbstractSocket::ConnectionRefusedError:
            qDebug()<<"1";
            break;
        default:
            qDebug()<<"1";
        }
    }
signals:
    void get_config_done(bool,QByteArray buffer);
private:
    bool  send(char *buf,int len)
    {
        bool ret=false;
        int write_bytes=0;

        write_bytes=tcp_socket->write(buf,len);
        if(write_bytes!=len){
            prt(info,"send %d bytes in state %d , %d bytes left",write_bytes,tcp_socket->state(),len-write_bytes);
        }else{
            ret=true;
        }
        return ret;
    }
    QString server_ip;
    QTcpSocket *tcp_socket;
    QDataStream in;
    mutex lock;
    QByteArray ret_ba;
    bool need_read;

};

#endif // CLIENT_H
