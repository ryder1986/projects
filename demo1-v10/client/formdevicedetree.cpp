#include "formdevicetree.h"
#include "ui_formdevicetree.h"

FormDeviceTree::FormDeviceTree(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_device_detail)
{
    ui->setupUi(this);
}

FormDeviceTree::~FormDeviceTree()
{
    delete ui;
}
