#ifndef CLIENTSESSION_H
#define CLIENTSESSION_H
#include <QObject>
#include <QTcpSocket>
#include <QTcpSocket>
#include <QHostAddress>
#include <QTimer>

#include "tool1.h"
#include "pd.h"
class ClientSession:public QObject{
    Q_OBJECT
public:
    bool need_sync;
    ClientSession(QTcpSocket *client_skt):skt(client_skt),focus_index(0){
    need_sync=true;
      //  connect(skt,SIGNAL(cl)
//        need_sync=true;
    connect(skt,SIGNAL(readyRead()),this,SLOT(handle_msg()));
    connect(skt,SIGNAL(disconnected()),this,SLOT(deleteLater()));
    connect(skt,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(error_happened()));
//        //   udp_skt=new QUdpSocket();
//        client_addr=skt->peerAddress();

//    //    prt(info,"socket state %d",skt->state());
//        //   timer=new QTimer(this);
//        //  connect(timer,SIGNAL(timeout()),this,SLOT(check_output()));
//        // timer->start(10);
//        //  connect(skt,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(test()));
//        //                connect(skt,SIGNAL(aboutToClose()),this,SLOT(test()));
//        //                connect(skt,SIGNAL(disconnected()),this,SLOT(test()));
    }
    ~ClientSession()
    {
        close_output();
        //    delete timer;
        //   //    disconnect(timer,SIGNAL(timeout()),this,SLOT(send_rst_to_client()));
        // delete udp_skt;
    }

public slots:
    void open_output(int index)
    {
//        CameraManager &mgr=  CameraManager::GetInstance();
//        if(index>0)
//            disconnect(mgr.cameras[index-1],SIGNAL(send_rst(QByteArray)),this,SLOT(handle_alg_out(QByteArray)));
//        focus_index=index;
//        connect(mgr.cameras[focus_index-1],SIGNAL(send_rst(QByteArray)),this,SLOT(handle_alg_out(QByteArray)));
    }
    void close_output()
    {
//        CameraManager &mgr=  CameraManager::GetInstance();
//        if(focus_index>0)
//            disconnect(mgr.cameras[focus_index-1],SIGNAL(send_rst(QByteArray)),this,SLOT(handle_alg_out(QByteArray)));
//        focus_index=0;
    }
    bool camera_focused()
    {
//        if(focus_index>0)
//            return true;
//        if(focus_index<0)
            return false;
    }
    void handle_alg_out(QByteArray out)
    {
//        ProcessedDataSender *sender=ProcessedDataSender::get_instance();
//        sender->send(out,client_addr);
    }

    //    void check_output()
    //    {

    //        ProcessedDataSender *sender=ProcessedDataSender::get_instance();
    //        CameraManager &mgr=  CameraManager::GetInstance();
    //        QByteArray ba;
    //        if(camera_focused()&&focus_index<=mgr.cam_num()){
    //            //prt(info,"checking camera %d",focus_index);
    //            if(mgr.try_get_data(focus_index-1,ba)){
    //                sender->send(ba,client_addr);
    //            }
    //        }else{
    //            if(camera_focused()){
    //                prt(debug,"close camera %d output",focus_index);
    //                close_output();
    //            }
    //        }
    //    }

//    void socket_error()
//    {
//        emit socket_error(this);
//    }
    void error_happened()
    {
          emit socket_error(this);
    }

    void handle_msg(){

        int writes_num=0;
        QByteArray client_buf=skt->readAll();
        prt(debug,"get %d bytes",client_buf.size());
        rcv_buf=client_buf.data();
        int head_len=Protocol::HEAD_LENGTH;
        memcpy(send_buf,rcv_buf,head_len);
        int ret_size=process(rcv_buf,send_buf+head_len,client_buf.size());
        writes_num=skt->write(send_buf,ret_size+head_len);
        prt(debug,"server reply %d bytes",writes_num);
    }
    int process(char *src_buf,char*dst_buf,int size)
    {
        int client_cmd=Protocol::get_operation(src_buf);
        int pkg_len=Protocol::get_length(src_buf);
        int cam_index=Protocol::get_cam_index(src_buf);
        int ret_size=0;
        int rpl;
        switch (client_cmd) {
        case Protocol::ADD_CAMERA:
            emit session_operation(client_cmd,this,pkg_len,0,src_buf+Protocol::HEAD_LENGTH,ret_size);
            break;
        case  Protocol::GET_CONFIG:
            emit session_operation(client_cmd,this,0,0,dst_buf,ret_size);
         //   prt(info,"%d",ret_size);
            break;
        case  Protocol::SET_CONFIG:
            emit session_operation(client_cmd,this,0,0,dst_buf,ret_size);
         //   prt(info,"%d",ret_size);
            break;
        case Protocol::DEL_CAMERA:
            emit session_operation(client_cmd,this,0,cam_index,NULL,ret_size);
            break;
        case Protocol::MOD_CAMERA:
            emit session_operation(client_cmd,this,pkg_len,cam_index,src_buf+Protocol::HEAD_LENGTH,ret_size);
            break;
        case Protocol::CAM_OUTPUT_OPEN:
            break;
        default:
            break;
        }
        return ret_size;
    }
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
