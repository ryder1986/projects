#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    flg=0;
    ui->setupUi(this);
    //    ply=new Player(ui->groupBox_picture);

    //    ply->setMinimumWidth(300);
    //    ply->setMinimumHeight(300);
    //    ui->groupBox_picture->layout()->addWidget(ply);
    //    ply->start();
    //    connect(ply,SIGNAL(doub_click()),this,SLOT(set_full()));
    //            ui->textEdit_2->hide();
    //            ui->textEdit->hide();
    connect(&searcher,SIGNAL(find_ip(QString)),this,SLOT(set_ip(QString)));
    ui->comboBox->clear();
    ui->comboBox->setEnabled(false);
//    Player *p=new Player("rtsp://192.168.1.216:8554/test1",this);
//    ui->groupBox_picture->layout()->addWidget(p);
//    p->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_groupBox_picture_clicked()
{
    prt(info,"click");
}

void MainWindow::on_groupBox_picture_clicked(bool checked)
{
    prt(info,"1");
}

void MainWindow::on_pushButton_clicked()
{
    prt(info,"start search ");
    ui->comboBox->clear();
    ui->comboBox->addItem("");

    searcher.search_device();
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    //    prt(info,"%d selected",index);
    //    QString ip=ui->comboBox->itemText(index);
    //    prt(info,"%s",ip.toStdString().data());
    //    ui->comboBox->setEnabled(false);
    //    open_device(ip);
}

void MainWindow::on_comboBox_activated(int index)
{
    prt(info,"%d selected",index);
    QString ip=ui->comboBox->itemText(index);
    prt(info,"%s",ip.toStdString().data());
    ui->comboBox->setEnabled(false);
    open_device(ip);

}

void MainWindow::on_pushButton_save_clicked()
{

    QString ip=ui->textEdit_config->toPlainText();
    QByteArray ba(ip.toStdString().data(),ip.size());
    clt.set_config(ba);

}
