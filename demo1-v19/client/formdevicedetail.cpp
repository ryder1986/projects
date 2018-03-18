#include "formdevicedetail.h"
#include "ui_formdevicedetail.h"
#include <QMenu>
FormDeviceDetail::FormDeviceDetail(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormDeviceDetail)
{
    cam_index=0;
    ui->setupUi(this);
    connect(&clt,SIGNAL(get_config_done(bool,QByteArray)),this,SLOT(config_arrived(bool,QByteArray)));
    connect(&clt,SIGNAL(need_update_config()),this,SLOT(need_sync_config()));
     connect(&searcher,SIGNAL(find_ip(QString)),
            this,SLOT(ip_search_done(QString)),Qt::DirectConnection);

    click_times=0;
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
{//  QByteArray cfg=QByteArray::fromStdString(ui->lineEdit_set_config->text().toStdString());
    clt.get_config();
    ui->lineEdit_get_config->setText(config);
}

void FormDeviceDetail::on_treeWidget_device_doubleClicked(const QModelIndex &index)
{
    //  QAbstractItemView::
    //    QTreeWidgetItem *p_item_device_current= ui->treeWidget_device->currentItem();
    //    //   p_item_device_current=  ui->treeWidget_device->currentItem();
    //    if(p_item_device_current){
    //        if(!p_item_device_current->parent()){//root

    //        }else{//child
    //            prt(info,"%s:%d",p_item_device_current->text(0).toStdString().data(),index.row());
    //            if(click_times++%2){
    //                clt.focus_camera(index.row()+1);
    //                emit camera_selected(configuration.pro.cams[index.row()]);
    //            }else{
    //                emit camera_detach();
    //                clt.disfocus_camera(index.row()+1);
    //            }


    //        }
    //    }

}

void FormDeviceDetail::on_pushButton_set_config_clicked()
{
    QByteArray cfg=QByteArray::fromStdString(ui->lineEdit_set_config->text().toStdString());
    clt.set_config(cfg);
}

void FormDeviceDetail::on_treeWidget_device_clicked(const QModelIndex &index)
{

}

void FormDeviceDetail::on_treeWidget_device_customContextMenuRequested(const QPoint &pos)
{
    QTreeWidgetItem *p_item_device_current= ui->treeWidget_device->itemAt(pos);
    if(p_item_device_current){
        if(!p_item_device_current->parent()){//root

        }else{//child
            cam_index=p_item_device_current->parent()->indexOfChild(p_item_device_current);
            QMenu *cmenu = new QMenu(ui->treeWidget_device);
            QAction *action_preview_start = cmenu->addAction("camera preview start");
            QAction *action_preview_stop = cmenu->addAction("camera preview stop");
            connect(action_preview_start, SIGNAL(triggered(bool)), this, SLOT(camera_preview_start(bool)));
            connect(action_preview_stop, SIGNAL(triggered(bool)), this, SLOT(camera_preview_stop(bool)));
            cmenu->exec(QCursor::pos());

            //      connect(action_preview, SIGNAL(triggered(bool)), this, SLOT(preview_camera(bool)));

        }
    }

}

void FormDeviceDetail::on_pushButton_search_clicked()
{
    ui->lineEdit_connect->clear();
    searcher.search_device();
    // ui->lineEdit_connect->setText(clt.find_service());
}
#include <QMessageBox>
void FormDeviceDetail::on_pushButton_del_cam_clicked()
{
//   QMessageBox  *box1=new QMessageBox(QMessageBox::Warning,"Information","update?",QMessageBox::Yes|QMessageBox::No,NULL);
//   box1->show();
    int index=ui->lineEdit_del_cam->text().toInt();
    clt.del_camera(index);
    clt.get_config();
  //  prt(info,"del cam %d",index);
 ui->lineEdit_get_config->clear();
}

void FormDeviceDetail::on_pushButton_add_cam_clicked()
{
    QString url=ui->lineEdit_add_cam->text();
    QJsonObject alg;

    QJsonObject obj;
    obj["url"]=url;
    obj["alg"]=alg;
    clt.add_camera(obj,configuration.cams.size());
    clt.get_config();
    //  clt.get_config();
    //
    ui->lineEdit_get_config->clear();
}
