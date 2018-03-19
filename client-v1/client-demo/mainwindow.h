#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "tool1.h"
//#include "player.h"
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

private slots:
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
    }
private:
    Ui::MainWindow *ui;
    int flg;
    //Player *ply;
    ServerInfoSearcher searcher;
};

#endif // MAINWINDOW_H
