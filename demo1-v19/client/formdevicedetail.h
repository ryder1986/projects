#ifndef FORMDEVICEDETAIL_H
#define FORMDEVICEDETAIL_H

#include <QWidget>
#include "client.h"
#include "tool1.h"
#include "ui_formdevicedetail.h"
#include <QMessageBox>

class ServerReplyCheckRouting : public QObject
{
    Q_OBJECT

public slots:
    void check_reply(    QUdpSocket *udp_skt_find_server) {
        QString str;
        str.clear();
        int try_times=100;
        while(try_times--){
            if(udp_skt_find_server->hasPendingDatagrams()){
                datagram.resize((udp_skt_find_server->pendingDatagramSize()));
                udp_skt_find_server->readDatagram(datagram.data(),datagram.size());
                prt(info,"get server info : %s",datagram.data());
                server_ip.clear();
                server_ip.append(datagram.split(',')[0]);
                prt(info,"ip : %s",server_ip.toStdString().data());
                ip_list.append(server_ip);
                emit resultReady(server_ip);
            }else{
                //      prt(info,"searching");
            }
            QThread::msleep(10);
        }
    }

signals:
    void resultReady(  QString result);
private:
    //  QUdpSocket *udp_skt_find_server;

    QByteArray datagram;
    QString server_ip;
    QStringList ip_list;
};

class ServerInfoSearcher : public QObject{
    Q_OBJECT
    QThread check_thread;
    ServerReplyCheckRouting *p_checker;

public:
    ServerInfoSearcher()
    {

        udp_skt_find_server=new QUdpSocket(this);
        udp_skt_find_server->bind(Protocol::CLIENT_REPORTER_PORT,QUdpSocket::ShareAddress);
        //     connect(udp_skt_find_server,SIGNAL(readyRead()),this,SLOT(get_reply()),Qt::QueuedConnection);

        //   connect();

        p_checker=new ServerReplyCheckRouting;
        p_checker->moveToThread(&check_thread);
        connect(&check_thread,&QThread::finished,p_checker,&QObject::deleteLater);
        connect(this,SIGNAL(begin_search(QUdpSocket*)),p_checker,SLOT(check_reply(QUdpSocket*)),Qt::QueuedConnection);
        connect(p_checker,SIGNAL(resultReady(QString)),this,SLOT(ip_found(QString)),Qt::QueuedConnection);
    }
    ~ServerInfoSearcher()
    {
        check_thread.quit();
        check_thread.wait();
    }
    void broadcast_info()
    {
        QByteArray b;
        b.append("pedestrian");
        udp_skt_find_server->writeDatagram(b.data(), b.size(),
                                           QHostAddress::Broadcast, Protocol::SERVER_REPORTER_PORT);
        prt(info,"finding server ...");

    }
    void search()
    {

        check_thread.start();
        emit begin_search(udp_skt_find_server);
    }

    void search_device()
    {
        ip_list.clear();
        broadcast_info();
        search();
        //   p_find_server_thread=new std::thread(find_server);
        //   QThread::msleep(3000);

    }
    QStringList search_rst()
    {
        return ip_list;
    }
    static void find_server()
    {
        prt(info," find server thread");
        int times=10;
        while(times--){

        }
    }
signals:
    void begin_search( QUdpSocket *udp_skt_find_server);
    void find_ip(QString ip);

public slots:
    void ip_found(QString ip)
    {
        qDebug()<<ip;
       // ip_list.append(ip);
        emit find_ip(ip);
    }

//    void get_reply()
//    {
//        //  while(udp_skt->hasPendingDatagrams())
//        if(udp_skt_find_server->hasPendingDatagrams())
//        {
//            datagram.resize((udp_skt_find_server->pendingDatagramSize()));
//            udp_skt_find_server->readDatagram(datagram.data(),datagram.size());
//            prt(info,"get server info : %s",datagram.data());
//            server_ip.append(datagram.split(',')[0]);
//            ip_list.append(server_ip);
//        }
//    }

private :
    QUdpSocket *udp_skt_find_server;

    QByteArray datagram;
    QString server_ip;
    QStringList ip_list;
};

namespace Ui {
class FormDeviceDetail;
}

class FormDeviceDetail : public QWidget
{
    Q_OBJECT
    typedef struct Camera{
        QString url;
        QJsonObject alg;
    }Camera_t;
    typedef struct Profile{
        QList <Camera_t> cams;
    }Profile_t;
    typedef struct Config{
        QString dev_name;
         QList <Camera_t> cams;
    }Config_t;
    ServerInfoSearcher searcher;
public:
    explicit FormDeviceDetail(QWidget *parent = 0);
    ~FormDeviceDetail();
    //    void set_client(Client *c)
    //    {
    //        clt=c;
    //        connect(clt,SIGNAL(get_config_done(bool,QByteArray)),this,SLOT(config_arrived(bool,QByteArray)));
    //    }
    void set_config(QByteArray cfg)
    {

    }
private:

    void update_device_list()
    {
        ui->treeWidget_device->clear();
        QTreeWidgetItem *root_item=new QTreeWidgetItem(QStringList(configuration.dev_name));
        ui->treeWidget_device->addTopLevelItem(root_item);
        foreach (Camera_t c, configuration.cams) {
            QTreeWidgetItem *item=new QTreeWidgetItem(QStringList(c.url));
            root_item->addChild(item);
        }
    }
    void trans_config()
    {
        QJsonDocument doc= QJsonDocument::fromJson(config);
        QJsonObject obj=doc.object();
        configuration.dev_name=obj["device_name"].toString();
        QJsonArray array=obj["cameras"].toArray();

        configuration.cams.clear();
        foreach (QJsonValue v, array) {
            QString url=  v.toObject()["url"].toString();
            prt(info,"%s",url.toStdString().data());
            Camera_t c;
            c.url=url;
            c.alg= v.toObject()["alg"].toObject();
            configuration.cams.append(c);
        }

    }

private slots:
    void config_arrived(bool ret,QByteArray cfg)
    {
        if(ret){
            config=cfg;
            ui->lineEdit_get_config->setText(config);
            trans_config();
            update_device_list();
        }
        else{
            ui->lineEdit_get_config->setText("fail to get config");
        }
    }
    void need_sync_config( )
    {
        QMessageBox  *box1=new QMessageBox(QMessageBox::Warning,"Information","update?",QMessageBox::Yes|QMessageBox::No,NULL);
        box1->show();
    }

private slots:
    void on_pushButton_connect_clicked();

    void on_pushButton_get_config_clicked();

    void on_treeWidget_device_doubleClicked(const QModelIndex &index);
    void on_pushButton_set_config_clicked();

    void on_treeWidget_device_clicked(const QModelIndex &index);

    void on_treeWidget_device_customContextMenuRequested(const QPoint &pos);
    void camera_preview_start(bool)
    {
        prt(info,"starting  %d",cam_index);
        clt.focus_camera(cam_index+1);

        emit camera_detach();
        emit camera_selected(configuration.cams[cam_index]);
    }

    void camera_preview_stop(bool)
    {
        prt(info,"stoping  %d",cam_index);
        clt.disfocus_camera(cam_index+1);
        emit camera_detach();

    }
    void on_pushButton_search_clicked();
    void ip_search_done(QString ip)
    {
        ui->lineEdit_connect->setText(ip);
    }

    void on_pushButton_del_cam_clicked();

    void on_pushButton_add_cam_clicked();

signals:
    void camera_selected(Camera_t cfg);
    void camera_detach();

   private:
    Ui::FormDeviceDetail *ui;
    //    Client *clt;
    QByteArray config;
    Config_t configuration;
    Client clt;
    int click_times;
    int cam_index;

};

#endif // FORMDEVICEDETAIL_H
