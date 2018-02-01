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

public:
    explicit FormDeviceDetail(QWidget *parent = 0);
    ~FormDeviceDetail();
    void set_client(Client *c)
    {
        clt=c;
        connect(clt,SIGNAL(get_config_done(bool,QByteArray)),this,SLOT(config_arrived(bool,QByteArray)));
    }
    void set_config(QByteArray cfg)
    {

    }

private slots:
    void config_arrived(bool ret,QByteArray cfg)
    {
        if(ret){
            config=cfg;
            ui->lineEdit_get_config->setText(config);
        }
        else{
            ui->lineEdit_get_config->setText("fail to get config");
        }
    }

private slots:
    void on_pushButton_connect_clicked();

    void on_pushButton_get_config_clicked();

private:
    Ui::FormDeviceDetail *ui;
    Client *clt;
    QByteArray config;
};

#endif // FORMDEVICEDETAIL_H
