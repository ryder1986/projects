#include "formcameradetail.h"
#include "ui_formcameradetail.h"

FormCameraDetail::FormCameraDetail(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormCameraDetail)
{
    ui->setupUi(this);
player=NULL;
}

FormCameraDetail::~FormCameraDetail()
{
    delete player;
    delete ui;
}
