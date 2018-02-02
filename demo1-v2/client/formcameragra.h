#ifndef FORMCAMERAGRA_H
#define FORMCAMERAGRA_H
#include <QOpenGLWidget>
#include <QWidget>
#include <QJsonObject>
#include "ui_formcameragra.h"
#include "tool1.h"
#include "alg.h"
namespace Ui {
class FormCameraGra;
}


class FormCameraGra : public QWidget
{
    Q_OBJECT
    typedef struct Camera{
        QString url;
        QJsonObject alg;
    }Camera_t;
    alg_config_t alg_cfg;
public:
    explicit FormCameraGra(QWidget *parent = 0);
    ~FormCameraGra();
    void trans_config()
    {
        alg_cfg.selected_alg=configuration.alg["selected_alg"].toString();
        QString area=configuration.alg["pd"].toObject()["detect_area"].toString();
        QStringList lst=area.split(',');

        if(lst.size()==4){
            alg_cfg.pd.x=lst[0].toInt();
            alg_cfg.pd.y=lst[1].toInt();
            alg_cfg.pd.w=lst[2].toInt();
            alg_cfg.pd.h=lst[3].toInt();
        }
    }

public slots:
    void set_camera(Camera_t cfg)
    {
        prt(info,"get %s",cfg.url.toStdString().data());
        ui->lineEdit_url->setText(cfg.url);
        configuration=cfg;
        trans_config();
    }
private:
    Ui::FormCameraGra *ui;
    Camera_t configuration;
};

#endif // FORMCAMERAGRA_H
