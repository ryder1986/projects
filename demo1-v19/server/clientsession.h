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
    QByteArray tmp_msg;
    Q_OBJECT
public:
    bool need_sync;
    ClientSession(QTcpSocket *client_skt):skt(client_skt),focus_index(0){
        tmp_msg.clear();
        need_sync=true;
        focus_index=0;
        connect(skt,SIGNAL(readyRead()),this,SLOT(handle_msg()));
        connect(skt,SIGNAL(disconnected()),this,SLOT(deleteLater()));
        connect(skt,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(error_happened()));
        client_addr=skt->peerAddress();
    }
    ~ClientSession()
    {
    }
    void set_valid(bool valid)
    {
        need_sync=!valid;

        if(!valid){
            QByteArray rt;
            rt.clear();
            QJsonObject obj;
            obj["type"]=Protocol::NEED_UPDATE;
            QJsonDocument doc(obj);
            rt=doc.toJson();
            skt->write(rt,rt.size());
        }
    }

    bool is_valid()
    {
        return !need_sync;
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
    //    int count_objs(QByteArray ba)
    //    {
    //         char *tmp=ba.data();
    //         int sz=ba.size();
    //         int b=0;
    //         for(int i=0;i<sz;i++){
    //             if(tmp[i]=="{"){
    //                 b++;
    //             }
    //         }
    //    }
    int count_begin_symbol(QByteArray ba)
    {
        char *tmp=ba.data();
        int sz=ba.size();
        int ret=0;
        int i;
        for( i=0;i<sz;i++){
            if(tmp[i]=='{'){
                ret++;
            }
        }
        return ret;
    }
    int count_end_symbol(QByteArray ba)
    {
        char *tmp=ba.data();
        int sz=ba.size();
        int ret=0;
        int i;
        for( i=0;i<sz;i++){
            if(tmp[i]=='}'){
                ret++;
            }
        }
        return ret;
    }
    void find_pos(QByteArray ba,int &endpos,int &left)
    {

    }
    bool try_get_obj_buf(QByteArray src,QByteArray &dst)
    {
        int ret=false;
        int stack=0;
        char *p_tmp=src.data();
        bool flg=false;
     //    bool flg_real_end=false;
        //char *p_start=src.data();
           dst.clear();
         dst.append(src);
         int i;
        if(count_begin_symbol(src)>0){
            for(i=0;i<src.size();i++){
                if(p_tmp[i]=='{')
                 {
                    stack++;
                    flg=true;
                }
                if(p_tmp[i]=='}')
                    stack--;


                if(stack==0&&flg)
                  {

                    break;
                }

            }
            if(i<src.size()){
                ret=true;
                if(src[i+1]=='\n')
                dst.truncate(i+2);
                else
                    dst.truncate(i+i);
            }
        }
        return ret;
    }

    //dst:a sting which contain a compelete json object
    //src:a slice ofstream buffer
    //tmp_msg:last slice of buffer(maybe begining of json string)
    bool get_valid_buf(QByteArray &src,QByteArray &dst)
    {
        //        bool ret=false;

        //        int begin_symbol_num=count_begin_symbol(src);
        //        int end_symbol_num=end_begin_symbol(src);
        //        if((begin_symbol_num>end_symbol_num&&objs_count==0)||begin_symbol_num==0)
        //        {
        //            ret=false;
        //        }else{
        //            dst.clear();
        //            dst.append(src);
        //            int endpos=0,left=0;
        //            find_pos(dst,endpos,left);
        //            dst.remove(endpos,left);
        //            src.truncate(src.size()-left);
        //        }
        //        return false;


        if(try_get_obj_buf(src,dst)){
            src.remove(0,dst.size());
            return true;
        }
        return false;

    }

    void handle_msg(){

        int writes_num=0;
        QByteArray client_buf=skt->readAll();
      //  QString str(client_buf);
    //    qDebug()<<"get msg--------------->"<<str;
        QByteArray valid_buf;
        valid_buf.clear();
        tmp_msg.append(client_buf);
        while(get_valid_buf(tmp_msg,valid_buf)) {
            QByteArray rt;
            rt.clear();
              QString str1(valid_buf);
          qDebug()<<"vaild msg--------------->"<<str1;
            emit client_request(valid_buf,rt,this);
            writes_num=skt->write(rt.data(),rt.size());
            prt(info,"server reply %d bytes",writes_num);
        }
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
