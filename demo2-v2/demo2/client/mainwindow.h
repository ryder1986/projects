#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "tool.h"
#include "player.h"
#include "client.h"
#include "serverinfosearcher.h"
#include <QJsonObject>
#include "player.h"
#include "playerwidget.h"
namespace Ui {
class MainWindow;
}

class PlayThread;
class MainWindow : public QMainWindow
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
    configture_t cfg;
public:
    friend class PlayThread;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void open_device(QString ip)
    {
        clt.connect_to_server(ip);
        connect(&clt,SIGNAL(get_config_done(bool,QByteArray)),this,SLOT(open_config(bool,QByteArray)));
        connect(&clt,SIGNAL(connect_done()),this,SLOT(clt_ready()));
    }

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
    void play()//this will be call in helper thread
    {
        QJsonArray cams=  cfg.cams_cfg.toArray();

        foreach (Player *p, players) {
            delete p;
        }
        players.clear();
        foreach (QJsonValue v, cams) {
            players.append(new Player(v));
            emit add_picture(players.last());
            players.last()->start();
            //add_box(players.last()->get_widget());
        }
        Qt::HANDLE handle=QThread::currentThreadId();

    }
    void  play_start();

private slots:
//    void  update_pic(QWidget *w)
//    {
//        w->update();
//    }

    void on_add_picture(Player *p)
    {
        QWidget **w=p->get_widget();
        *w=new PlayerWidget();
        ui->groupBox_picture->layout()->addWidget(*w);
        //    update_pic();
    }

    void open_config(bool ,QByteArray ba)
    {
        prt(info,"---> get %d  bytes",ba.size());
        //   ui->textEdit_config->
        QJsonDocument doc=QJsonDocument::fromJson(ba);
        QJsonObject obj=doc.object();
        obj_2_cfg(obj);
        QString str(ba);
        prt(info,"---> get %d   ",str.size());
        ui->textEdit_config->setText(str);
        play_start();
    }
    void clt_ready()
    {
        prt(info,"--->  conect ok");
        clt.get_config();
    }

    void on_groupBox_picture_clicked();

    void on_groupBox_picture_clicked(bool checked);
    void set_full()
    {
    }
    void on_pushButton_clicked();
    void set_ip(QString ip)
    {
        prt(info,"find %s",ip.toStdString().data());
        ui->comboBox->addItem(ip);
        ui->comboBox->setEnabled(true);
    }
    void on_comboBox_currentIndexChanged(int index);

    void on_comboBox_activated(int index);

    void on_pushButton_save_clicked();

    void test()
    {
        while(1){
            prt(info,"ssss");
        }
        foreach (Player *p, players) {
            delete p;
        }
        players.clear();
        foreach (QJsonValue v,  cfg.cams_cfg.toArray()) {
            players.append(new Player(v));
        }
    }
signals:
    void add_picture(Player *);

private:
    Ui::MainWindow *ui;
    int flg;
    //Player *ply;
    ServerInfoSearcher searcher;
    Client clt;
    QList <Player *>players;
    // Tmp *player_starter;
    QThread starter_thread;
    PlayThread *pt;
};

class PlayThread:public QObject{
    Q_OBJECT
public:
    PlayThread(MainWindow *w)
    {
        mw=w;
    }
public slots:
    void play()
    {

        Qt::HANDLE handle=QThread::currentThreadId();
        mw->play();
    }
private:
    MainWindow *mw;

};

#endif // MAINWINDOW_H
