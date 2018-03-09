#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H
#include <QtOpenGL/QtOpenGL>
#include <QMouseEvent>
#include "tool1.h"
#include <QMutex>
//#include <QtNetwork>
//#include "pd.h"
//class ProcessedDataReciver: public QObject{
//    Q_OBJECT
//public:
//    ProcessedDataReciver()
//    {
//        udp_skt_alg_output=new QUdpSocket(this);
//        udp_skt_alg_output->bind(Protocol::SERVER_DATA_OUTPUT_PORT,QUdpSocket::ShareAddress);
//        connect(udp_skt_alg_output,SIGNAL(readyRead()),this,SLOT(get_rst()),Qt::QueuedConnection);
//    }
//signals:
//    void send_rst(QByteArray);
//public slots:
//    void get_rst()
//    {
//        QByteArray datagram_rst;
//        if(udp_skt_alg_output->hasPendingDatagrams())
//        {
//            //   int size=udp_skt_alg_output->pendingDatagramSize();
//            datagram_rst.resize((udp_skt_alg_output->pendingDatagramSize()));
//            udp_skt_alg_output->readDatagram(datagram_rst.data(),datagram_rst.size());
//            //        udp_skt_alg_output->readDatagram(sss,500);
//            //          datagram_rst= udp_skt_alg_output->readAll();
//#if 0
//          b  QList <QByteArray > bl= datagram_rst.split(':');
//            QByteArray b_index=bl[0];
//            int index=*(b_index);

//            prt(info,"get cam   %d rst",index);

//            QByteArray b_loc=bl[1];
//#else

//            prt(debug,"get data %s",datagram_rst.data());
//            emit send_rst(datagram_rst);
//#endif

//            //   emit send_camera_rst(index,b_loc);
//            //    QList <QByteArray > xy= b_loc.split(',');
//            //            int x=xy[0].toInt();
//            //            int y=xy[1].toInt();
//            //           prt(info," %d : %d",x,y);

//        }
//    }

//private:
//    QUdpSocket *udp_skt_alg_output;
//    QByteArray rst;
//};
typedef struct layout_info{
    bool valid;
    QRect rct;
    QList <QRect>  result_rcts;
}layout_info_t;

//using namespace cv;
class Layout_Controler:QWidget{
    QWidget *wgt;
public:
    Layout_Controler(QWidget *w)
    {
        wgt=w;
        pt_r=5;
        picked=false;
        pt.setX(0);
        pt.setY(0);
    }
    void paint(QPainter *p)
    {
        QBrush red_brush_trans(QColor(0,0,200,100));
        p->setBrush(red_brush_trans);
        p->drawEllipse(pt.x()-pt_r,pt.y()-pt_r,pt_r*2,pt_r*2);
    }
    void paint_extra(QPainter *p,QByteArray ba)
    {
        QBrush red_brush_trans(QColor(222,0,200,100));
        p->setBrush(red_brush_trans);
        //  p->drawEllipse(pt.x()-pt_r,pt.y()-pt_r,pt_r*2,pt_r*2);
        // prt(info,"paint %s",QString(ba.data()).toStdString().data());
        p->drawEllipse(QString(ba.data()).toInt()*100,100,50,50);
    }



    void paint_overlay(QPainter *p, void *data)
    {
        QPen blue_pen(QColor(111,111,0,0));
        blue_pen.setWidth(5);
        // painter.setBrush(blue_brush_trans);
        p->setPen(blue_pen);
        //     //   p->setBackgroundMode(Qt::TransparentMode);
        //        p->drawRect(0,0,300,300);
        layout_info_t *tmp=(layout_info_t *)data;
        int w=wgt->width();
        int h=wgt->height();
        if(tmp->valid){
            prt(info,"get rct------------------------------");
            foreach (QRect r, tmp->result_rcts) {
                prt(info,"(%d,%d,%d,%d)",r.x(),r.y(),r.width(),r.height());
                p->drawRect(r.x()*w/640*2,r.y()*h/480*2,r.width()*w/640*2,r.height()*w/480*2);

            }
        }
        tmp->valid=false;

        //        layout_info_t *tmp=(layout_info_t *)data;
        //        //        QPen pen1(QColor(222,0,200,255));
        //          QPen pen1(QColor(222,0,200,255));
        //                p->setPen(pen1);
        //                p->drawRect(QRect(1,1,111,111));



        //        if(tmp->valid){
        //        QPen pen1(QColor(222,0,200,255));
        //        p->setPen(pen1);
        //        p->drawRect(tmp->rct);
        //        QPen pen2(QColor(0,220,200,250));
        //        p->setPen(pen2);
        //              p->drawRect(tmp->rst);
        //        }


        //  p->drawEllipse(pt.x()-pt_r,pt.y()-pt_r,pt_r*2,pt_r*2);
        // prt(info,"paint %s",QString(ba.data()).toStdString().data());
        //p->drawEllipse(QString(ba.data()).toInt()*100,100,50,50);
    }

    void mouse_press(QPoint pos)
    {
        // pt=pos;
        float v_x=pos.x()-pt.x();
        float v_y=pos.y()-pt.y();
        float dis=10;
        if(v_x>-dis&& v_x<dis&&v_y>-dis && v_y<dis&& !picked){
            prt(info,"valid point");
            picked=true;
        }
    }
    void mouse_release(QPoint pos)
    {
        if(picked)
            picked=false;
    }
    void mouse_move(QPoint pos)
    {
        if(picked)
            pt=pos;
    }

private:
    // layout data
    // painter
    QPoint pt;
    bool picked;
    float pt_r;

};

class VideoWidget : public QOpenGLWidget
{
    Q_OBJECT
    QImage img1;
    int wi;
    int he;
    int tick;
    int pos_x;
    int pos_y;
    QStringList list;
    QList <QRect> rcts;
    void *init_data;
    void *extra_data;
    Layout_Controler *lc;

    //    QByteArray alg_rst;
    //  QList <QByteArray> alg_rst_list;
    void *data;
public:
    void set_init_data(void *d)
    {
        init_data=d;
    }

    //    VideoWidget();
    VideoWidget(QWidget *w):QOpenGLWidget(w)
    {
        wi=640;
        he=480;
        tick=0;
        pos_x=0;
        pos_y=0;
        rcts.clear();
        rcts.append(QRect(333,333,444,444));
        init_data=NULL;
        click_record=0;
        data=NULL;
        lc=new Layout_Controler(this);

        //  alg_rst_list.clear();
    }
    ~VideoWidget()
    {
        delete lc;
    }

    void set_rects(QByteArray rst)
    {
        // this->width()/640;
        //prt(info," pic width %d",this->width());
        //        if(init_data){
        //            QString *p=(QString *)init_data;
        //            if(p->length()>0){
        //                prt(info,"%s",p->toStdString().data());
        //            }
        //        }
        QString str(rst.data());
        QStringList list=str.split(":");
        QStringList l;
        foreach (QString s, list) {
            l=s.split(',');
            QRect r;
            if(l.size()==4){
                r.setRect(l[0].toInt()*this->width()/wi*2,l[1].toInt()*this->height()/he*2,l[2].toInt()*this->width()/wi*2,l[3].toInt()*this->height()/he*2);
                rcts.append(r);
            }
        }
    }

    int update_pic(QImage &im)
    {
        //   int size=frame_mat.total();
        lock.lock();
        img1=im.copy();
        lock.unlock();
        //     this->update();
        return 1;
    }
    int update_data(void *dat)
    {
        data=dat;
        return 1;
    }
public slots:
    //    void set_alg_rst(QByteArray ba)
    //    {
    //          // prt(info,"get %s",QString(ba.data()).toStdString().data());
    //        alg_rst_list.append(ba);
    //    }

protected:
    void paintEvent(QPaintEvent *)
    {
        // if(img1.width()>0){
        if(1){

            QPainter painter(this);
            //              painter.beginNativePainting();
            //             makeCurrent();

            QBrush blue_brush_trans(QColor(0,222,200,255));
            painter.setBrush(blue_brush_trans);
            painter.drawRect(0,0,this->width(),this->height());


            //                QBrush red_brush_trans(QColor(0,0,200,100));
            //                 painter.setBrush(red_brush_trans);
            //                         pos_x+=10;
            //                          painter.drawEllipse(pos_x%345,0,50,50);
            //              painter.beginNativePainting();
            //               makeCurrent();

            paint_frame(painter);

            if(data)
            {
                paint_overlay(painter,data);
                data=NULL;
            }

#if 0
            QPen blue_pen(QColor(111,111,0,255));
            blue_pen.setWidth(20);
            // painter.setBrush(blue_brush_trans);
            painter.setPen(blue_pen);
            painter.drawRect(0,0,this->width()-100,this->height()-100);
#endif
#if 0
            lc.paint(&painter);
            paint_frame(painter);
            if(alg_rst_list.size()>1){
                lc.paint_extra(&painter,alg_rst_list.first());
                alg_rst_list.pop_front();
            }
#endif
            //  painter.endNativePainting();

            //    paint_layout2(painter);

            //             painter.beginNativePainting();
            //             makeCurrent();
            //             QPainter *p=&painter;
            //             QBrush red_brush_trans(QColor(0,0,200,100));
            //             p->setBrush(red_brush_trans);
            //         //     pos_x+=10;
            //              p->drawEllipse(222,222,50,50);
            //              painter.endNativePainting();
            //             paint_layout(painter);
            //    paint_layout2(painter);
            //     paint_layout4(painter);
        }else{
            //prt(info,"invalid frame");
        }
    }
    void  initializeGL()
    {

    }
    void paint_overlay(QPainter &painter,void *data )
    {
        lc->paint_overlay(&painter,data);
    }
    void paint_frame(QPainter &painter)
    {
        lock.lock();
        painter.beginNativePainting();
        makeCurrent();
        //        Mat bgr_frame=frame;
        //        Mat rgb_frame;
        //        // imwrite("test.jpg",rgb_frame);
        //        //  cvtColor(rgb_frame,yuv_frame,CV_RGB2GRAY);
        //        cvtColor(bgr_frame,rgb_frame,CV_BGR2RGB);
        //        QImage  img = QImage((const uchar*)(rgb_frame.data),
        //                             rgb_frame.cols,rgb_frame.rows,
        //                             rgb_frame.cols*rgb_frame.channels(),
        //                             QImage::Format_RGB888);
        //      QBrush red_brush_trans(QColor(0,0,200,100));
        //      painter.setBrush(red_brush_trans);
        //       pos_x+=10;
        //       painter.drawEllipse(pos_x%300,0,50,50);
        painter.drawImage(QRect(0,0,this->width(),this->height()),img1);
        painter.endNativePainting();
        lock.unlock();
    }
    void paint_layout1(QPainter &painter){
        //#if 0
        //        painter.beginNativePainting();
        //        makeCurrent();
        //        CONVERT_YUV420PtoRGB24((unsigned char *)yuv_buf,(unsigned char *)rgb_buf,video_width,video_height);
        //        glPixelZoom(1.0f*this->width()/video_width, 1.0f*this->height()/video_height);
        //#if 0
        //        glDrawPixels(video_width, video_height,GL_RGB, GL_UNSIGNED_BYTE, rgb_buf);
        //#else
        //        QImage img((uchar *)rgb_buf,video_width,video_height,QImage::Format_RGB888);
        //        //  QImage img((uchar *)rgb_buf,video_width,video_height,QImage::Format_RGB888);
        //        //QImage  img = QImage((const uchar*)(frame.data),frame.cols,frame.rows,frame.cols*frame.channels(),QImage::Format_Indexed8);
        //        //   QImage  img = QImage((const uchar*)(frame.data),frame.cols,frame.rows,frame.cols*frame.channels(),QImage::Format_Grayscale8);

        //        painter.drawImage(QRect(0,0,this->width(),this->height()),img);
        //#endif
        //        painter.endNativePainting();
        //#else
        //        painter.beginNativePainting();
        //        makeCurrent();
        //        Mat bgr_frame=frame;
        //        Mat rgb_frame;
        //        // imwrite("test.jpg",rgb_frame);
        //        //  cvtColor(rgb_frame,yuv_frame,CV_RGB2GRAY);
        //        cvtColor(bgr_frame,rgb_frame,CV_BGR2RGB);
        //        QImage  img = QImage((const uchar*)(rgb_frame.data),
        //                             rgb_frame.cols,rgb_frame.rows,
        //                             rgb_frame.cols*rgb_frame.channels(),
        //                             QImage::Format_RGB888);
        //        painter.drawImage(QRect(0,0,this->width(),this->height()),img);
        //        painter.endNativePainting();

        //#endif
    }
    void paint_layout2(QPainter &painter){
        painter.beginNativePainting();
        //  makeCurrent();
        QBrush red_brush_trans(QColor(0,0,200,100));
        painter.setBrush(red_brush_trans);
        // painter.drawEllipse(pos_x++%500,pos_y++%500,50,50);
        pos_x+=10;
        painter.drawEllipse(pos_x%300,0,50,50);
        //        foreach (QRect r, rcts) {
        //            painter.drawRect(r);
        //        }

        if(rcts.size()>0)
        { painter.drawRect(rcts.first());
            rcts.clear();
        }
        painter.drawEllipse(500,500,50,50);
        painter.endNativePainting();

    }
    void paint_layout4(QPainter &painter){
        //  painter.beginNativePainting();
        // makeCurrent();
        QBrush red_brush_trans(QColor(110,110,111,0));
        painter.setBrush(red_brush_trans);

        QPen p(QColor(0,100,0),10);
        painter.setPen(p);


        // painter.drawEllipse(pos_x++%500,pos_y++%500,50,50);

        QString s;
        if(init_data){
            QString *p=(QString *)init_data;
            if(p->length()>0){
                //    prt(info,"%s",p->toStdString().data());
                QStringList lst=p->split(',');
                if(lst.length()>=4){
                    //  painter.drawRect(lst[0].,lst[1].toInt(),lst[2].toInt(),lst[3].toInt());
                    QString x=lst[0];
                    QString y=lst[1];
                    QString width=lst[2];
                    QString height=lst[3];
                    painter.drawRect(x.toInt(),y.toInt(),width.toInt(),height.toInt());
                }

            }
        }
        //  painter.drawRect();
        //        foreach (QRect r, rcts) {
        //            painter.drawRect(r);
        //        }

        //            if(rcts.size()>0)
        //            { painter.drawRect(rcts.first());
        //                 rcts.clear();
        //            }
        //  painter.drawEllipse(500,500,50,50);
        //    painter.endNativePainting();

    }

    void set_data(QByteArray ba)
    {
        QList<QByteArray> xy=ba.split(',');
        int x=xy[0].toInt();
        int y=xy[1].toInt();
        pos_x=x;
        pos_y=y;
    }
    void paint_layout3(QPainter &painter){
#if 0
        QBrush red_brush_trans(QColor(0,0,200,100));
        painter.setBrush(red_brush_trans);
        // pressed_x=0;
        // pressed_y=0;
        //  if(flg++>10)


        painter.drawEllipse(pressed_x+tick%300,pressed_y,100,100);
        QPen testpen(red_brush_trans,10);
        painter.setPen(testpen);

        for(int i=0;i<8;i++){
            painter.drawLine(pt[i*2],pt[i*2+1]);
        }


        for(int i=0;i<8;i++){
            painter.drawLine(pt[i*2],pt[i*2+1]);
        }

        for(int i=0;i<8;i++){
            painter.drawLine(pt_rear[i*2],pt_rear[i*2+1]);
        }
        painter.drawEllipse(p1,10,10);
        painter.drawEllipse(p2,10,10);
        painter.drawEllipse(p3,10,10);
#endif
    }

    bool get_area(int &x,int &y, int &w, int &h)
    {
        if(init_data){
            QString *p=(QString *)init_data;
            if(p->length()>0){
                //    prt(info,"%s",p->toStdString().data());
                QStringList lst=p->split(',');
                if(lst.length()>=4){
                    //  painter.drawRect(lst[0].,lst[1].toInt(),lst[2].toInt(),lst[3].toInt());
                    QString str_x=lst[0];
                    QString str_y=lst[1];
                    QString str_w=lst[2];
                    QString str_h=lst[3];
                    //painter.drawRect(400,y.toInt(),width.toInt(),height.toInt());
                    //                    p->clear();
                    //                    p->append(QString::number(e->x()));
                    //                    p->append(",");
                    //                    p->append(QString::number(e->y()));
                    //                    p->append(",");
                    //                    p->append(width);
                    //                    p->append(",");
                    //                    p->append(height);
                    x=str_x.toInt();
                    y=str_y.toInt();
                    w=str_w.toInt();
                    h=str_h.toInt();
                    return true;
                }

            }
        }
        return false;
    }
    bool set_area(int &x,int &y, int &w, int &h)
    {
        if(init_data){
            QString *p=(QString *)init_data;
            if(p->length()>0){
                //    prt(info,"%s",p->toStdString().data());
                QStringList lst=p->split(',');
                if(lst.length()>=4){
                    p->clear();
                    //  painter.drawRect(lst[0].,lst[1].toInt(),lst[2].toInt(),lst[3].toInt());
                    //                    QString str_x=lst[0];
                    //                    QString str_y=lst[1];
                    //                    QString str_w=lst[2];
                    //                    QString str_h=lst[3];
                    //painter.drawRect(400,y.toInt(),width.toInt(),height.toInt());
                    //                    p->clear();
                    p->append(QString::number(x));
                    p->append(",");
                    p->append(QString::number(y));
                    p->append(",");
                    p->append(QString::number(w));
                    p->append(",");
                    p->append(QString::number(h));
                }
            }
        }
        return true;
    }

private:
    void  mousePressEvent(QMouseEvent *e)
    {
        lc->mouse_press(e->pos());
        //        if(init_data){
        //            QString *p=(QString *)init_data;
        //            if(p->length()>0){
        //            //    prt(info,"%s",p->toStdString().data());
        //                QStringList lst=p->split(',');
        //                if(lst.length()>=4){
        //                  //  painter.drawRect(lst[0].,lst[1].toInt(),lst[2].toInt(),lst[3].toInt());
        //                    QString x=lst[0];
        //                    QString y=lst[1];
        //                    QString width=lst[2];
        //                    QString height=lst[3];
        //                    //painter.drawRect(400,y.toInt(),width.toInt(),height.toInt());
        //                    p->clear();
        //                    p->append(QString::number(e->x()));
        //                    p->append(",");
        //                    p->append(QString::number(e->y()));
        //                    p->append(",");
        //                    p->append(width);
        //                    p->append(",");
        //                    p->append(height);
        //                }

        //            }
        //        }
        //  qDebug()<<e->pos().x();
        prt(info,"(pres:%d,%d)",e->pos().x(),e->pos().y());

        int x,y,w,h;
        int new_x=e->x();
        int new_y=e->y();
        int new_w;
        int new_h;

        if(get_area(x,y,w,h)){
            new_w=new_x-x;
            new_h=new_y-y;
            if(e->button()!=Qt::RightButton){
                set_area(new_x,new_y,w,h);
            }else{
                set_area(x,y,new_w,new_h);
            }
        }


    }
    void mouseDoubleClickEvent(QMouseEvent *e)
    {
        prt(info,"(clk:%d,%d)",e->pos().x(),e->pos().y());
        //        click_record++;
        //        int x,y,w,h;
        //        int new_x=e->x();
        //        int new_y=e->y();
        //        int new_w;
        //        int new_h;

        //          if(get_area(x,y,w,h)){
        //               new_w=new_x-x;
        //               new_h=new_y-y;
        //              if(click_record%2){
        //                set_area(new_x,new_y,w,h);
        //              }else{
        //                set_area(x,y,new_w,new_h);
        //              }
        //          }
    }
    void mouseReleaseEvent(QMouseEvent *e)
    {
        lc->mouse_release(e->pos());
        prt(info,"rls:(%d,%d)",e->pos().x(),e->pos().y());
    }
    void mouseMoveEvent(QMouseEvent *e)
    {
        lc->mouse_move(e->pos());
        prt(info,"mv:(%d,%d)",e->pos().x(),e->pos().y());
    }

    int click_record;
    QMutex lock;
};

#endif // VIDEOWIDGET_H
