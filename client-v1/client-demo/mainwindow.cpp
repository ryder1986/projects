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
    searcher.search_device();
}
