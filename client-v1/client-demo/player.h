#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QPainter>
#include <opencv2/core/core.hpp>
#include "videosource.h"
#include <QMutex>
#include <QThread>
#include <QObject>

#include <QMouseEvent>
using namespace cv;
class Player :public QObject,public QThread, public QOpenGLWidget
{
    Q_OBJECT
public:
    Player(QString str,QWidget *w):QOpenGLWidget(w)
    {
        src=new VideoSource(str);
        rct.setCoords(100,100,200,200);
        holding=false;
    }

    void set_data()
    {

    }
    void update_pic(Mat t)
    {
        //    this->update();
    }
protected:

    void paintEvent(QPaintEvent *)
    {
        if(1){

            QPainter painter(this);
            QBrush blue_brush_trans(QColor(0,222,200,255));
            painter.setBrush(blue_brush_trans);
            painter.drawRect(0,0,this->width(),this->height());
            lock.lock();
            paint_frame(painter);

            painter.drawText(QPointF(100,100),"123123421");
            painter.drawEllipse(rct.x(),rct.y(),30,30);
            painter.drawEllipse(rct.x()+rct.width(),rct.y(),30,30);
            painter.drawEllipse(rct.x(),rct.y()+rct.width(),30,30);
            painter.drawEllipse(rct.x()+rct.width(),rct.y()+rct.height(),30,30);
            lock.unlock();

        }else{
            //prt(info,"invalid frame");
        }
    }
    void  initializeGL()
    {

    }

    void run()
    {

        //        while(1){
        //            this->update();
        //                 src->get_frame(bgr_frame);
        //          this->usleep(100);
        //}
        //                img1=QImage((const uchar*)(rgb_frame.data),
        //                            640,480,
        //                            3,
        //                            QImage::Format_RGB888);
        //        if(src->get_frame(bgr_frame)){
        //            src->get_frame(bgr_frame);
        //        img1=QImage((const uchar*)(rgb_frame.data),
        //                    rgb_frame.cols,rgb_frame.rows,
        //                    rgb_frame.cols*rgb_frame.channels(),
        //                    QImage::Format_RGB888);
        //        }

        img1=QImage(640,480,
                    QImage::Format_RGB888);

        while(1){

            if(src->get_frame(bgr_frame)){
                lock.lock();
                src->get_frame(bgr_frame);
                cvtColor(bgr_frame,rgb_frame,CV_BGR2RGB);
                img1=QImage((const uchar*)(rgb_frame.data),
                            rgb_frame.cols,rgb_frame.rows,
                            QImage::Format_RGB888);
                QByteArray ba((const char*)(rgb_frame.data),640*480*3);

                //    img1.loadFromData((const uchar*)(rgb_frame.data),640*480);
                //                prt(info,"%d,%d,%d", rgb_frame.cols,rgb_frame.rows,
                //                    rgb_frame.cols*rgb_frame.channels());
                lock.unlock();
                this->update();

                //     this->sleep(1);
                //    prt(info,"get frame");
            }else{
                //this->usleep(1);
            }
        }

    }
    //    void mouseDoubleClickEvent(QMouseEvent *e)
    //    {
    //        prt(info,"(clk:%d,%d)",e->pos().x(),e->pos().y());
    //      //  emit d_click();
    //    }
    void mousePressEvent(QMouseEvent *e)
    {
        if(abs(e->pos().x()-rct.x())<30&&abs(e->pos().y()-rct.y()<30)){
            holding=true;
        }
    }
    void mouseReleaseEvent(QMouseEvent *e)
    {
        holding=false;
        // prt(info,"rls:(%d,%d)",e->pos().x(),e->pos().y());
    }
    void mouseMoveEvent(QMouseEvent *e)
    {
        if(holding){
            rct.setX(e->pos().x());
            rct.setY(e->pos().y());
        }
        // prt(info,"mv:(%d,%d)",e->pos().x(),e->pos().y());
    }
    void mouseDoubleClickEvent(QMouseEvent *e)
    {
        // emit doub_click();
    }
signals:
    void doub_click();
private:
    void paint_frame(QPainter &painter)
    {
        //lock.lock();
        painter.beginNativePainting();
        makeCurrent();
        painter.drawImage(QRect(0,0,this->width(),this->height()),img1);
        painter.endNativePainting();
        //     lock.unlock();
    }
    QMutex lock;
    cv::Mat mt;
    QImage img1;
    Mat rgb_frame;
    Mat bgr_frame;
    VideoSource *src;
    QRect rct;
    bool holding;
    //   QMutex lock;
};

#endif // PLAYER_H
