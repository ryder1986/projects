#include "formcameragra.h"
#include "ui_formcameragra.h"

FormCameraGra::FormCameraGra(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormCameraGra)
{
    ui->setupUi(this);
}

FormCameraGra::~FormCameraGra()
{
    delete ui;
}
