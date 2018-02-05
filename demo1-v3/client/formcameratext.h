#ifndef FORMCAMERATEXT_H
#define FORMCAMERATEXT_H

#include <QWidget>
#include <QJsonObject>
#include "tool1.h"
namespace Ui {
class FormCameraText;
}

class FormCameraText : public QWidget
{
    Q_OBJECT
    typedef struct Camera{
        QString url;
        QJsonObject alg;
    }Camera_t;
public:
    explicit FormCameraText(QWidget *parent = 0);
    ~FormCameraText();
public slots:
    void set_camera(Camera_t cfg)
    {
        prt(info,"get %s",cfg.url.toStdString().data());
    }

private:
    Ui::FormCameraText *ui;
};

#endif // FORMCAMERATEXT_H
