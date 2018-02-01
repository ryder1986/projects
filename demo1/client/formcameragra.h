#ifndef FORMCAMERAGRA_H
#define FORMCAMERAGRA_H

#include <QWidget>

namespace Ui {
class FormCameraGra;
}

class FormCameraGra : public QWidget
{
    Q_OBJECT

public:
    explicit FormCameraGra(QWidget *parent = 0);
    ~FormCameraGra();

private:
    Ui::FormCameraGra *ui;
};

#endif // FORMCAMERAGRA_H
