#ifndef FORMDEVICEDETAIL_H
#define FORMDEVICEDETAIL_H

#include <QWidget>
#include "client.h"
#include "tool1.h"
#include "ui_formdevicedetail.h"
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
        Profile_t pro;
    }Config_t;
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
        foreach (Camera_t c, configuration.pro.cams) {
            QTreeWidgetItem *item=new QTreeWidgetItem(QStringList(c.url));
            root_item->addChild(item);
        }
    }
    void trans_config()
    {
        QJsonDocument doc= QJsonDocument::fromJson(config);
        QJsonObject obj=doc.object();
        configuration.dev_name=obj["device_name"].toString();
        QJsonArray array=obj["profile"].toObject()["cameras"].toArray();

        configuration.pro.cams.clear();
        foreach (QJsonValue v, array) {
            QString url=  v.toObject()["url"].toString();
            prt(info,"%s",url.toStdString().data());
            Camera_t c;
            c.url=url;
            c.alg= v.toObject()["alg"].toObject();
            configuration.pro.cams.append(c);
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
        emit camera_selected(configuration.pro.cams[cam_index]);
    }

    void camera_preview_stop(bool)
    {
        prt(info,"stoping  %d",cam_index);
        clt.disfocus_camera(cam_index+1);
        emit camera_detach();

    }
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
