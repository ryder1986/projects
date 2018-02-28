#ifndef VIDEOPROCESSOR_H
#define VIDEOPROCESSOR_H

#include <QObject>

class VideoProcessor : public QObject
{
    Q_OBJECT
public:
    explicit VideoProcessor(QObject *parent = 0);
    virtual void process(const char *yuv,const int yuv_size,char *rst_buf,int &rst_len)
    {

    }
    virtual void init()
    {

    }

signals:

public slots:
};


class PDVideoProcessor: public VideoProcessor
{
public:
    PDVideoProcessor()
    {

    }
    ~PDVideoProcessor()
    {

    }

    void process(const char *yuv,const int yuv_size,char *rst_buf,int &rst_len)
    {

    }
    void init()
    {

    }

private:
//    bool work_inside(Mat &mt,string &rst)
//    {
//        CascadeClassifier cascade;
//        bool ret=false;
//        vector<Rect> objs;
//        string cascade_name = "hogcascade_pedestrians.xml";
//        if (!cascade.load(cascade_name))
//        {
//            prt(info,"can't load cascade");
//            exit(0);
//        }
//        // while (1)
//        {

//            Mat frame(mt);
//            QString str;
//            str.clear();
//            rst.clear();
//            if (!frame.empty())
//            {    //  if (frame_num % 3 == 0)
//                if (1)
//                {
//                    resize(frame,frame,Size(frame.cols / 2, frame.rows / 2),CV_INTER_LINEAR);
//                    cvtColor(frame, gray_frame, CV_BGR2GRAY);
//                    cascade.detectMultiScale(gray_frame, objs, 1.1, 3);
//                    vector<Rect>::iterator it = objs.begin();
//                    while (it != objs.end() && objs.size() != 0)
//                    {
//                        pedestrian_num++;
//                        pedestrians = frame(*it);

//                        Rect rct = *it;
//                        {
//                            rectangle(frame, rct, Scalar(0, 255, 0), 2);
//                            QString x_str=QString::number(rct.x);
//                            QString y_str=QString::number(rct.y);
//                            QString width_str=QString::number(rct.width);
//                            QString height_str=QString::number(rct.height);
//                            //QString test_str=QString::number(test);
//                            str.append(x_str).append(",").append(y_str).append(",").append(width_str).append(",").append(height_str).append(":");
//                            rst.append(str.toStdString().data());

//                            ret=true;
//                            //  break;//TODO, now we get first one
//                        }
//                        it++;
//                    }
//                    objs.clear();
//                }
//            }
//            else{
//                prt(info,"opencv handle frame error !");
//            }
//        }
//    }
};

#endif // VIDEOPROCESSOR_H
