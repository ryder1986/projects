#ifndef VIDEOPROCESSOR_H
#define VIDEOPROCESSOR_H

#include <QObject>

class VideoProcessor : public QObject
{
    Q_OBJECT
public:
    explicit VideoProcessor(QObject *parent = 0);
    virtual void process(char *yuv,char *ret_buf)
    {

    }

signals:

public slots:
};

#endif // VIDEOPROCESSOR_H
