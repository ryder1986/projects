#ifndef FORM_DEVICE_DETAIL_H
#define FORM_DEVICE_DETAIL_H

#include <QWidget>

namespace Ui {
class Form_device_detail;
}

class FormDeviceTree : public QWidget
{
    Q_OBJECT

public:
    explicit FormDeviceTree(QWidget *parent = 0);
    ~FormDeviceTree();

private:
    Ui::Form_device_detail *ui;
};

#endif // FORM_DEVICE_DETAIL_H
