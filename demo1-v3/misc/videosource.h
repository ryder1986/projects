#ifndef VIDEOSOURCE_H
#define VIDEOSOURCE_H

#include <QObject>
#include <QThread>
#include <QJsonObject>
#include "tool1.h"
class VideoSource : public QThread
{
    Q_OBJECT
public:
    explicit VideoSource(QJsonObject config);
    void set_config(const QJsonObject config)
    {
        url=config["url"].toString();
    }
    void get_config(QJsonObject &config)
    {

    }

private:
    void run()
    {
        while(!quit_flg){
           // prt(info,"runing thread %s",url.toStdString().data());
            QThread::sleep(1);
        }
    }

signals:

public slots:
private:
    QString url;
    bool quit_flg;
};

#endif // VIDEOSOURCE_H
