#include "formdevicedetail.h"
#include "ui_formdevicedetail.h"

FormDeviceDetail::FormDeviceDetail(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormDeviceDetail)
{
    ui->setupUi(this);
    connect(&clt,SIGNAL(get_config_done(bool,QByteArray)),this,SLOT(config_arrived(bool,QByteArray)));
}

FormDeviceDetail::~FormDeviceDetail()
{
    delete ui;
}

void FormDeviceDetail::on_pushButton_connect_clicked()
{
    prt(info,"connecting to server");
    clt.connect_to_server(ui->lineEdit_connect->text());
}

void FormDeviceDetail::on_pushButton_get_config_clicked()
{
    clt.get_config();
 //   ui->lineEdit_get_config->setText(config);
}

void FormDeviceDetail::on_treeWidget_device_doubleClicked(const QModelIndex &index)
{
 //  QAbstractItemView::
   QTreeWidgetItem *p_item_device_current= ui->treeWidget_device->currentItem();
//   p_item_device_current=  ui->treeWidget_device->currentItem();
   if(p_item_device_current){
       if(!p_item_device_current->parent()){//root

       }else{//child
             prt(info,"%s:%d",p_item_device_current->text(0).toStdString().data(),index.row());
             emit camera_selected(configuration.pro.cams[index.row()]);
       }
   }

}
