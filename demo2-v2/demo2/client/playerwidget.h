#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QObject>
#include <QOpenGLWidget>
#include <QPainter>
#include <QTimer>
#include <QMutex>
class PlayerWidget : public QOpenGLWidget
{

public:
    PlayerWidget()
    {
        //        QTimer *t=new QTimer();
        //        connect(t,SIGNAL(timeout()),this,SLOT(update()));
        //        t->start(10);
    }


    void set_image(QImage img1)

    {
        lock.lock();
        img=img1;
        lock.unlock();
    }

protected:
    void paintEvent(QPaintEvent *)
    {
        // if(img1.width()>0){
        if(1){

            QPainter painter(this);
            lock.lock();
            painter.drawImage(QRect(0,0,this->width(),this->height()),img);
            lock.unlock();
            QBrush blue_brush_trans(QColor(0,222,200,255));
            painter.setBrush(blue_brush_trans);
         //   painter.drawRect(0,0,this->width(),this->height());
            painter.drawRect(100,100,300,300);

        }
    }
    void  initializeGL()
    {

    }


private:
    QImage img;
    QMutex lock;
};

#endif // PLAYERWIDGET_H
