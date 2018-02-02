#ifndef FORMCAMERATEXT_H
#define FORMCAMERATEXT_H

#include <QWidget>

namespace Ui {
class FormCameraText;
}

class FormCameraText : public QWidget
{
    Q_OBJECT

public:
    explicit FormCameraText(QWidget *parent = 0);
    ~FormCameraText();

private:
    Ui::FormCameraText *ui;
};

#endif // FORMCAMERATEXT_H
