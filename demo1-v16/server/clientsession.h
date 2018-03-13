#ifndef CLIENTSESSION_H
#define CLIENTSESSION_H
#include <QObject>
#include <QTcpSocket>
#include <QTcpSocket>
#include <QHostAddress>
#include <QTimer>
#include "processeddatasender.h"
#include "tool1.h"
#include "pd.h"
class ClientSession:public QObject{
    Q_OBJECT
public:
    bool need_sync;
    ClientSession(QTcpSocket *client_skt):skt(client_skt),focus_index(0){
    need_sync=true;
    focus_index=0;
    connect(skt,SIGNAL(readyRead()),this,SLOT(handle_msg()));
    connect(skt,SIGNAL(disconnected()),this,SLOT(deleteLater()));
    connect(skt,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(error_happened()));
    }
    ~ClientSession()
    {
    }

public slots:
    void handle_alg_out(QByteArray out)
    {
        QString str(out.data());
        prt(info,"sending %s",str.toStdString().data());
        ProcessedDataSender *sender=ProcessedDataSender::get_instance();
        sender->send(out,client_addr);
    }

    void error_happened()
    {
          emit socket_error(this);
    }

    void handle_msg(){

        int writes_num=0;
        QByteArray client_buf=skt->readAll();
        QString str(client_buf);
        qDebug()<<"get msg";


        qDebug()<<str;

        QByteArray rt;
        emit client_request(client_buf,rt,this);
        writes_num=skt->write(rt.data(),rt.size());
        prt(debug,"server reply %d bytes",writes_num);
    }
//    int process(char *src_buf,char*dst_buf,int size)
//    {
//        int client_cmd=Protocol::get_operation(src_buf);
//        int pkg_len=Protocol::get_length(src_buf);
//        int cam_index=Protocol::get_cam_index(src_buf);
//        int ret_size=0;
//        prt(info,"cmd %d",client_cmd);
//        switch (client_cmd) {
//        case Protocol::ADD_CAMERA:
//            emit session_operation(client_cmd,this,pkg_len,0,src_buf+Protocol::HEAD_LENGTH,ret_size);
//            break;
//        case  Protocol::GET_CONFIG:
//            emit session_operation(client_cmd,this,0,0,dst_buf,ret_size);
//         //   prt(info,"%d",ret_size);
//            break;
//        case  Protocol::SET_CONFIG:
//            emit session_operation(client_cmd,this,0,0,src_buf+Protocol::HEAD_LENGTH,ret_size);
//         //   prt(info,"%d",ret_size);
//            break;
//        case Protocol::DEL_CAMERA:
//            emit session_operation(client_cmd,this,0,cam_index,NULL,ret_size);
//            break;
//        case Protocol::MOD_CAMERA:
//            emit session_operation(client_cmd,this,pkg_len,cam_index,src_buf+Protocol::HEAD_LENGTH,ret_size);
//            break;
//        case Protocol::CAM_OUTPUT_OPEN:
//            {
//                prt(info,"focus %d",cam_index);
//                if(cam_index>0&&focus_index!=cam_index){
//                    if(focus_index>0)
//                        emit session_operation(Protocol::CAM_OUTPUT_CLOSE,this,0,focus_index,NULL,ret_size);
//                    focus_index=cam_index;
//                    emit session_operation(client_cmd,this,0,cam_index,NULL,ret_size);
//                }
//                else
//                    focus_index=0;
//            }
//            break;
//        default:
//            break;
//        }
//        return ret_size;
//    }
    void update_client()
    {
//        char bf[Pd::BUFFER_LENGTH];
//        Protocol::encode_msg(bf,Protocol::CMD::NEED_UPDATE);
//        int writes_num=skt->write(bf,Protocol::HEAD_LENGTH);
//        need_sync=true;
    }

    void displayError(QAbstractSocket::SocketError socketError)
    {
        switch (socketError) {
        case QAbstractSocket::RemoteHostClosedError:
            break;
        case QAbstractSocket::HostNotFoundError:
            prt(info,"err");
            break;
        case QAbstractSocket::ConnectionRefusedError:
            prt(info,"err");
            break;
        default:break;

        }
    }
    QString ip()
    {
        return client_addr.toString();
    }

signals :
    int get_server_config(char *buf);
    void socket_error(ClientSession *c);
    int client_request(QByteArray request,QByteArray &ret,void *);
    //    int try_lock_server();
    void session_operation(int req,void *addr, int len,int cam_index,char *buf,int &ret_size);
private:
    char *rcv_buf;
    char send_buf[Pd::BUFFER_LENGTH];
    QTcpSocket *skt;
    //  QUdpSocket *udp_skt;
    QTimer *timer;
    QHostAddress client_addr;
    int focus_index;
    //bool need_sync;
};

#endif // CLIENTSESSION_H
