#include "formcameragra.h"
#include "ui_formcameragra.h"

FormCameraGra::FormCameraGra(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormCameraGra)
{
    ui->setupUi(this);
    player=new Player(ui->openGLWidget);
}

FormCameraGra::~FormCameraGra()
{
    delete player;
    delete ui;
}
