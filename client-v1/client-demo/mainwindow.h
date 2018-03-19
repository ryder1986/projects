#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "tool1.h"
#include "player.h"
#include "client.h"
#include "serverinfosearcher.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void open_device(QString ip)
    {
        clt.connect_to_server(ip);
        //            clt.get_config();
        connect(&clt,SIGNAL(get_config_done(bool,QByteArray)),this,SLOT(open_config(bool,QByteArray)));
        connect(&clt,SIGNAL(connect_done()),this,SLOT(clt_ready()));
    }

private slots:
    void open_config(bool ,QByteArray cfg)
    {
        prt(info,"---> %s",cfg.toStdString().data());
        ui->textEdit_config->setText(cfg);
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
        if(flg++){
            //ply->hide();
            //    ui->groupBox_picture->layout()->addWidget(ui->textEdit_2);

            //  ui->groupBox_picture->layout()->addWidget(ply);

        }else{
            ;

        }
        //        prt(info,"full screen");
        //     //   ui->groupBox_picture->layout()->removeWidget(ui->textEdit_2);
        //        if(flg++){
        //        ui->textEdit_2->hide();
        //        ui->textEdit->hide();

        //             }else{
        //            ui->groupBox_picture->layout()->addWidget(ui->textEdit_2);
        //            ui->groupBox_picture->layout()->addWidget(ui->textEdit);
        ////                   ui->textEdit_2->show();
        ////            ui->textEdit->show();
        //        }
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

private:
    Ui::MainWindow *ui;
    int flg;
    //Player *ply;
    ServerInfoSearcher searcher;
    Client clt;
};

#endif // MAINWINDOW_H
