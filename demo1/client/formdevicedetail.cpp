#include "formdevicedetail.h"
#include "ui_formdevicedetail.h"

FormDeviceDetail::FormDeviceDetail(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormDeviceDetail)
{
    ui->setupUi(this);
}

FormDeviceDetail::~FormDeviceDetail()
{
    delete ui;
}

void FormDeviceDetail::on_pushButton_connect_clicked()
{
    prt(info,"connecting to server");
    clt->connect_to_server(ui->lineEdit_connect->text());
}

void FormDeviceDetail::on_pushButton_get_config_clicked()
{
    clt->get_config();
 //   ui->lineEdit_get_config->setText(config);
}
