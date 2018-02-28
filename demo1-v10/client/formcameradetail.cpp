#include "formcameradetail.h"
#include "ui_formcameradetail.h"

FormCameraDetail::FormCameraDetail(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormCameraDetail)
{
    ui->setupUi(this);
    player=new Player(ui->openGLWidget);
}

FormCameraDetail::~FormCameraDetail()
{
    delete player;
    delete ui;
}
