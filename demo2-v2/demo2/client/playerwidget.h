#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QObject>
#include <QOpenGLWidget>
#include <QPainter>
class PlayerWidget : public QOpenGLWidget
{
public:
    PlayerWidget();
protected:
    void paintEvent(QPaintEvent *)
    {
        // if(img1.width()>0){
        if(1){

            QPainter painter(this);
            painter.drawRect(100,100,300,300);

        }
    }
    void  initializeGL()
    {

    }
};

#endif // PLAYERWIDGET_H
