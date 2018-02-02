#include "formcameratext.h"
#include "ui_formcameratext.h"

FormCameraText::FormCameraText(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormCameraText)
{
    ui->setupUi(this);
}

FormCameraText::~FormCameraText()
{
    delete ui;
}
