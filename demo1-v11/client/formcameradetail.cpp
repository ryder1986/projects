#include "formcameradetail.h"
#include "ui_formcameradetail.h"

FormCameraDetail::FormCameraDetail(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormCameraDetail)
{
    ui->setupUi(this);

}

FormCameraDetail::~FormCameraDetail()
{
    delete player;
    delete ui;
}
