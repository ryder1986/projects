#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
 //   connect(ui->widget_device_detail,SIGNAL(camera_selected(Camera_t)),ui->widget_camera_text,SLOT(set_camera(Camera_t)));
    connect(ui->widget_device_detail,SIGNAL(camera_selected(Camera_t)),
            ui->widget_camera_detail,SLOT(set_camera(Camera_t)));
    connect(ui->widget_device_detail,SIGNAL(camera_detach()),
            ui->widget_camera_detail,SLOT(detach_camera()),Qt::DirectConnection);

        //  ui->widget_device_detail->set_client(&clt);
}

MainWindow::~MainWindow()
{
    delete ui;
}
