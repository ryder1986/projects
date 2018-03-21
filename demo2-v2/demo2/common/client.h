#ifndef CLIENT_H
#define CLIENT_H
#include <QObject>
#include <QtNetwork>
#include <tool1.h>

#include "pd.h"
//class ServerReplyCheckRouting : public QObject
//{
//    Q_OBJECT

//public slots:
//    void check_reply(    QUdpSocket *udp_skt_find_server) {
//        QString str;
//        str.clear();
//        int try_times=100;
//        while(try_times--){
//            if(udp_skt_find_server->hasPendingDatagrams()){
//                datagram.resize((udp_skt_find_server->pendingDatagramSize()));
//                udp_skt_find_server->readDatagram(datagram.data(),datagram.size());
//                prt(info,"get server info : %s",datagram.data());
//                server_ip.clear();
//                server_ip.append(datagram.split(',')[0]);
//                prt(info,"ip : %s",server_ip.toStdString().data());
//                ip_list.append(server_ip);
//                emit resultReady(server_ip);
//            }else{
//                //      prt(info,"searching");
//            }
//            QThread::msleep(10);
//        }
//    }

//signals:
//    void resultReady(  QString result);
//private:
//    //  QUdpSocket *udp_skt_find_server;

//    QByteArray datagram;
//    QString server_ip;
//    QStringList ip_list;
//};

//class ServerInfoSearcher : public QObject{
//    Q_OBJECT
//    QThread check_thread;
//    ServerReplyCheckRouting *p_checker;

//public:
//    ServerInfoSearcher()
//    {

//        udp_skt_find_server=new QUdpSocket(this);
//        udp_skt_find_server->bind(Protocol::CLIENT_REPORTER_PORT,QUdpSocket::ShareAddress);
//        //     connect(udp_skt_find_server,SIGNAL(readyRead()),this,SLOT(get_reply()),Qt::QueuedConnection);

//        //   connect();

//        p_checker=new ServerReplyCheckRouting;
//        p_checker->moveToThread(&check_thread);
//        connect(&check_thread,&QThread::finished,p_checker,&QObject::deleteLater);
//        connect(this,SIGNAL(begin_search(QUdpSocket*)),p_checker,SLOT(check_reply(QUdpSocket*)),Qt::QueuedConnection);
//        connect(p_checker,SIGNAL(resultReady(QString)),this,SLOT(ip_found(QString)),Qt::QueuedConnection);
//    }
//    ~ServerInfoSearcher()
//    {
//        check_thread.quit();
//        check_thread.wait();
//    }
//    void broadcast_info()
//    {
//        QByteArray b;
//        b.append("pedestrian");
//        udp_skt_find_server->writeDatagram(b.data(), b.size(),
//                                           QHostAddress::Broadcast, Protocol::SERVER_REPORTER_PORT);
//        prt(info,"finding server ...");

//    }
//    void search()
//    {

//        check_thread.start();
//        emit begin_search(udp_skt_find_server);
//    }

//    void search_device()
//    {
//        ip_list.clear();
//        broadcast_info();
//        search();
//        //   p_find_server_thread=new std::thread(find_server);
//        //   QThread::msleep(3000);

//    }
//    QStringList search_rst()
//    {
//        return ip_list;
//    }
//    static void find_server()
//    {
//        prt(info," find server thread");
//        int times=10;
//        while(times--){

//        }
//    }
//signals:
//    void begin_search( QUdpSocket *udp_skt_find_server);
//    void find_ip(QString ip);

//public slots:
//    void ip_found(QString ip)
//    {
//        qDebug()<<ip;
//       // ip_list.append(ip);
//        emit find_ip(ip);
//    }

////    void get_reply()
////    {
////        //  while(udp_skt->hasPendingDatagrams())
////        if(udp_skt_find_server->hasPendingDatagrams())
////        {
////            datagram.resize((udp_skt_find_server->pendingDatagramSize()));
////            udp_skt_find_server->readDatagram(datagram.data(),datagram.size());
////            prt(info,"get server info : %s",datagram.data());
////            server_ip.append(datagram.split(',')[0]);
////            ip_list.append(server_ip);
////        }
////    }

//private :
//    QUdpSocket *udp_skt_find_server;

//    QByteArray datagram;
//    QString server_ip;
//    QStringList ip_list;
//};
class Client : public QObject
{
    QByteArray tmp_msg;
    Q_OBJECT
public:
    char buf[2000];
    Client()
    {tmp_msg.clear();
        server_ip.clear();
        tcp_socket=new QTcpSocket();
        in.setDevice(tcp_socket);
        in.setVersion(QDataStream::Qt_1_0);
        connect(tcp_socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));
        connect(tcp_socket,SIGNAL(readyRead()),this,SLOT(handle_server_msg()),Qt::DirectConnection);
        connect(tcp_socket,SIGNAL(connected()),this,SLOT(handle_connected()),Qt::DirectConnection);
            //   connect(&finder,SIGNAL(find_ip(QString)),this,SLOT(handle_server_msg()),Qt::DirectConnection);

        //  tcp_socket->write("test1",6);

    }
    ~Client()
    {
        delete tcp_socket;
    }

    void get_config()
    {

        //    int request_length=Protocol::encode_configuration_request(buf);//encoder buffer
        QJsonObject obj;
        obj["type"]=Protocol::GET_CONFIG;
        QJsonDocument doc(obj);

        bool ret= send(doc.toJson().data(),doc.toJson().length());//talk to server
        if(!ret){
            prt(info,"fail send");
        }
        //    return rst.remove(0,Protocol::HEAD_LENGTH);//TODO:get the ret value;
    }

    //    void set_config(QByteArray config)
    //    {

    //        //    int request_length=Protocol::encode_configuration_request(buf);//encoder buffer
    //        QJsonObject obj;
    //        obj["type"]=Protocol::SET_CONFIG;
    //        obj["config"]=config;
    //        QJsonDocument doc(obj);

    //        bool ret= send(doc.toJson().data(),doc.toJson().length());//talk to server
    //        if(!ret){
    //            prt(info,"fail send");
    //        }
    //        //    return rst.remove(0,Protocol::HEAD_LENGTH);//TODO:get the ret value;
    //    }
    void set_config(QByteArray cfg)
    {
        QJsonDocument doc_config=QJsonDocument::fromJson(cfg);
        QJsonObject obj;
        obj["type"]=Protocol::SET_CONFIG;
        obj["config"]=doc_config.object();
        QJsonDocument doc(obj);

        bool ret= send(doc.toJson().data(),doc.toJson().length());//talk to server
        //  ret= send(doc.toJson().data(),doc.toJson().length());//talk to server
        //   ret= send(doc.toJson().data(),doc.toJson().length());//talk to server
        if(!ret){
            prt(info,"fail send");
        }
    }
    void focus_camera(int cam_index)
    {
        //    int request_length=Protocol::encode_configuration_request(buf);//encoder buffer
        QJsonObject obj;
        obj["type"]=Protocol::CAM_OUTPUT_OPEN;
        obj["cam_index"]=cam_index;
        QJsonDocument doc(obj);

        bool ret= send(doc.toJson().data(),doc.toJson().length());//talk to server
        if(!ret){
            prt(info,"fail send");
        }
    }

    void disfocus_camera(int cam_index)
    {
        //    int request_length=Protocol::encode_configuration_request(buf);//encoder buffer
        QJsonObject obj;
        obj["type"]=Protocol::CAM_OUTPUT_CLOSE;
        obj["cam_index"]=cam_index;
        QJsonDocument doc(obj);

        bool ret= send(doc.toJson().data(),doc.toJson().length());//talk to server
        if(!ret){
            prt(info,"fail send");
        }
    }


    void add_camera(QJsonObject obj_cam,int index)
    {
        QJsonObject obj;
        obj["type"]=Protocol::INSERT_CAMERA;
        obj["cam_index"]=index;
        obj["camera"]=obj_cam;
        QJsonDocument doc(obj);
        int len=doc.toJson().length();
        bool ret= send(doc.toJson().data(),len);//talk to server
        if(!ret){
            prt(info,"fail send");
        }
    }

    //    void add_camera(QByteArray cam_cfg,QString url)
    //    {

    //    }

    void del_camera(int index)
    {
        QJsonObject obj;
        obj["type"]=Protocol::DELETE_CAMERA;
        obj["cam_index"]=index;
        QJsonDocument doc(obj);

        bool ret= send(doc.toJson().data(),doc.toJson().length());//talk to server
        if(!ret){
            prt(info,"fail send");
        }

    }
    void mod_camera(QByteArray new_camera_config,int index)
    {

    }

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

public slots:
    void handle_connected()
    {
        prt(info,"connected");
        emit connect_done();
    }


    void handle_server_msg()
    {

 //       lock.lock();
        ret_ba=tcp_socket->readAll();

        QByteArray valid_buf;
        valid_buf.clear();
        tmp_msg.append(ret_ba);
        while(get_valid_buf(tmp_msg,valid_buf)) {
            QJsonDocument doc=QJsonDocument::fromJson(valid_buf);
            QJsonObject obj=doc.object();
            prt(info,"get %d bytes ",valid_buf.size());
            if(valid_buf.size()>0)
                need_read=true;
 //           lock.unlock();
            //        prt(info,"state %d",tcp_socket->state());
            int op=obj["type"].toInt();
            switch(op)
            {
            case Protocol::GET_CONFIG:
            {
                QJsonDocument d(obj["config"].toObject());
                emit get_config_done(true,d.toJson());
            }
                break;
            case Protocol::NEED_UPDATE:
                need_update_config();
                break;
            default:break;
            }
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

    //    QString find_service()
    //    {
    //        QString rst;
    //        rst.clear();
    //      //  finder.search_device();
    //          QThread::sleep(10);
    //        QStringList ql=finder.search_rst();
    //        if(ql.size()>0){
    //            QString ip=ql.first();
    //            prt(info,"get %s",ip.toStdString().data());
    //            rst=ip;
    //        }

    //        return rst;
    //    }

signals:
    void get_config_done(bool,QByteArray buffer);
    void need_update_config();
    void connect_done();
 private:
    bool  send(char *buf,int len)
    {
        bool ret=false;
        int write_bytes=0;

        write_bytes=tcp_socket->write(buf,len);
        bool flush_ret=tcp_socket->flush();//TODO,not work for flush
        if(flush_ret){
            prt(info,"flush ok");
        }else{
            prt(info,"flush err");
        }

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
 //   mutex lock;
    QByteArray ret_ba;
    bool need_read;
    //ServerInfoSearcher finder;

};

#endif // CLIENT_H
