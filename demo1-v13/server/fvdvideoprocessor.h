#ifndef VIDEOPROCESSOR_H
#define VIDEOPROCESSOR_H
#include <QDebug>
#include "alg/m_arith.h"
#include <stdio.h>
#include <time.h>
//#include<unistd.h>
#include<string.h>
//#include "load-cfg.h"
class loader{
public:
    enum {
        CLASS_NULL,
        CLASS_char,
        CLASS_short,
        CLASS_int,
        CLASS_mCommand,
        CLASS_mDetectDeviceConfig,
        CLASS_mCamParam,
        CLASS_mCamDetectParam,
        CLASS_mChannelVirtualcoil,
        CLASS_mCamAttributes,
        CLASS_mCamDemarcateParam,
        CLASS_mCamDetectLane,
        CLASS_mChannelCoil,
        CLASS_mPoint,
        CLASS_mLine,
        CLASS_mVirtualLaneLine,
        CLASS_mStandardPoint,
        CLASS_mDemDetectArea,
        CLASS_mDetectParam,

    };
#pragma pack(push,1)

#define FILE_NAME_LENGTH 20
#define CAM_NUM_1 8
#define  VERSION    0x01
#define  PROTTYPE    0x02


#define  SETCAMPARAM    0x0001
#define  GETCAMPARAM    0x0002
#define  REPCAMPARAM    0x0003

#define  SETDETECTDEVICE    0x0004
#define  GETDETECTDEVICE    0x0005
#define  REPDETECTDEVICE    0x0006

#define  SETCHECHPARAM    0x0007
#define  GETCHECHPARAM    0x0008
#define  REPCHECHPARAM    0x0009

#define  HEART    0x1000
#define  SHUTDOWN    0x1001
#define  REPHEART    0x1002

#define  REBOOTZEN   0x2001

#define  FORKEXIT    0x3001

#define   HEARTTIME     60

#define  USERNAMEMAX   20
#define  IPADDRMAX     16
#define  DEVNAMEMAX    50


#define Z_NONE 0x0
#define Z_NORTH 0x1
#define Z_NORTHEAST 0x2
#define Z_EAST 0x3
#define Z_SOUTHEAST 0x4
#define Z_SOUTH 0x5
#define Z_SOUTHWEST 0x6
#define Z_WEST 0x7
#define Z_NORTHWEST 0x8
#define  COILPOINTMAX       4
#define  DETECTLANENUMMAX   4
#define  LANELINEMAX         8
#define  STANDPOINT          8
#define  STANDARDVAULEMAX    4
#define  ALGMAX               2
#define  MAXSUBSYSTEM         4

    typedef struct Command {
        unsigned char version;
        unsigned char prottype;
        unsigned short objnumber;
        unsigned short objtype;
        unsigned int objlen;
    } mCommand;

    typedef struct {
        unsigned short x;
        unsigned short y;
    } IVDPoint;
    typedef struct {
        unsigned char state;
        unsigned char isCarInTail;
        unsigned short queueLength;
        unsigned int vehnum;
        //unsigned int    speed;
        unsigned short uActualDetectLength;
        unsigned short uActualTailLength;
        IVDPoint LineUp[2];
    } mRealLaneInfo;

    typedef struct {
        unsigned char flag;
        unsigned char laneNum;
        unsigned char curstatus;
        unsigned char fuzzyflag;
        unsigned char visibility;
        unsigned short uDegreePoint[20][2];
        //unsigned short 	uDegreePoint[4][2];
        mRealLaneInfo lane[DETECTLANENUMMAX];  //16
    } mRealStaticInfo;

#define CAM_CLOSED_STATUS 0
#define CAM_OPENED_STATUS 1
typedef struct caminfo {

    unsigned char camstatus;
    unsigned char camdirect;
    unsigned char cammerIp[IPADDRMAX];
} m_caminfo;

typedef struct DetectDeviceConfig {
    unsigned int deviceID;
    unsigned int detectport;
    unsigned char camnum;
    unsigned char detectip[IPADDRMAX];
    unsigned char detectname[DEVNAMEMAX];
    m_caminfo cam_info[CAM_NUM_1];

} mDetectDeviceConfig;
typedef struct CamAttributes {
    unsigned char direction;
    unsigned int camID;
    unsigned int cammerport;
    unsigned int adjustport;
    unsigned int signalport;
    unsigned char urlname[USERNAMEMAX];
    unsigned char username[USERNAMEMAX];
    unsigned char passwd[USERNAMEMAX];
    unsigned char cammerIp[IPADDRMAX];
    unsigned char adjustIp[IPADDRMAX];
    unsigned char signalIp[IPADDRMAX];
} mCamAttributes;
typedef struct CamDemarcateParam {
    unsigned short cam2stop;
    unsigned short camheight;
    unsigned short lannum;
    unsigned short number;
    unsigned short baselinelen;
    unsigned short farth2stop;
    unsigned short recent2stop;
} mCamDemarcateParam;
typedef struct ChannelVirtualcoil {
    unsigned short number;
    unsigned short farthCoillen;
    unsigned short recentCoillen;
} mChannelVirtualcoil;
typedef struct CamParam {
    unsigned char coilnum;
    mCamAttributes camattr;
    mCamDemarcateParam camdem;
    mChannelVirtualcoil channelcoil[DETECTLANENUMMAX];
} mCamParam;
typedef struct Point {
    unsigned short x;
    unsigned short y;
} mPoint;
typedef struct Line {
    unsigned short startx;
    unsigned short starty;
    unsigned short endx;
    unsigned short endy;
} mLine;
typedef struct RearCoil {
    mPoint Rear[COILPOINTMAX];
    mPoint Front[COILPOINTMAX];
} mChannelCoil;

typedef struct CamDetectLane
{
    unsigned char lanenum;
    mChannelCoil virtuallane[DETECTLANENUMMAX];
} mCamDetectLane;

typedef struct VirtualLaneLine {
    unsigned char lanelinenum;         //
    mLine laneline[LANELINEMAX];
} mVirtualLaneLine;

typedef struct StandardPoint {
    mPoint coordinate;
    unsigned short value;
} mStandardPoint;

typedef struct DemDetectArea {
    mPoint vircoordinate[STANDPOINT];
    mPoint realcoordinate[STANDPOINT];
} mDemDetectArea;

typedef struct DetectParam {
    unsigned short uTransFactor;
    unsigned int uGraySubThreshold;
    unsigned int uSpeedCounterChangedThreshold;
    unsigned int uSpeedCounterChangedThreshold1;
    unsigned int uSpeedCounterChangedThreshold2;
    unsigned short uDayNightJudgeMinContiuFrame;
    unsigned short uComprehensiveSens;
    unsigned short uDetectSens1;
    unsigned short uDetectSens2;
    unsigned short uStatisticsSens1;
    unsigned short uStatisticsSens2;
    unsigned short uSobelThreshold;
    unsigned short shutterMax;        // 1 2 3 4 5 6 7 8
    unsigned short shutterMin;        // 1 2 3 4 5 6 7 8
} mDetectParam;

typedef struct CamDetectParam {
    unsigned int timep[4];
    mCamDetectLane detectlane;
    mVirtualLaneLine laneline;
    mStandardPoint standpoint[STANDARDVAULEMAX];
    mDemDetectArea area;
    mDetectParam detectparam[ALGMAX];
} mCamDetectParam;
#pragma pack()


    void load_buf(char *name, char *bf, int pos, int len)
    {
        FILE *f = NULL;
        f = fopen(name, "rb+");
        if (f == NULL) {
           // prt(info, "err in opne %s", name);
        } else {
           // prt(info, "ok in opne %s", name);
            fseek(f, pos, SEEK_SET);
            fread(bf, len, 1, f);
            //	prt(info,"read file %s ok",name);
            fclose(f);
        }
    }
    int get_obj_len(int class_type)
    {
        int len = 0;
        switch (class_type) {
        case CLASS_NULL:
            break;
        case CLASS_char:
            break;
        case CLASS_short:
            len = 2;
            break;
        case CLASS_int:
            len = 4;
            break;
        case CLASS_mCommand:
            len = sizeof(mCommand);
            break;
        case CLASS_mDetectDeviceConfig:
            len = sizeof(mDetectDeviceConfig);
            break;
        case CLASS_mCamParam:
            len = sizeof(mCamParam);
            break;
        case CLASS_mCamAttributes:
            len = sizeof(mCamAttributes);
            break;

        case CLASS_mCamDemarcateParam:
            len = sizeof(mCamDemarcateParam);
            break;
        case CLASS_mChannelVirtualcoil:
            len = sizeof(mChannelVirtualcoil);
            break;
        case CLASS_mCamDetectParam:
            len = sizeof(mCamDetectParam);

            break;

        case CLASS_mCamDetectLane:
            len = sizeof(mCamDetectLane);
            break;
        case CLASS_mChannelCoil:
            len = sizeof(mChannelCoil);
            break;
        case CLASS_mPoint:
            len = sizeof(mPoint);
            break;
        case CLASS_mLine:
            len = sizeof(mLine);
            break;
        case CLASS_mVirtualLaneLine:
            len = sizeof(mVirtualLaneLine);
            break;
        case CLASS_mStandardPoint:
            len = sizeof(mStandardPoint);
            break;
        case CLASS_mDemDetectArea:
            len = sizeof(mDemDetectArea);
            break;
        case CLASS_mDetectParam:
            len = sizeof(mDetectParam);
            break;
        default:
            //prt(info, "not recognize")
            //;
            break;
        }
        return len;
    }
    void load_obj(unsigned char * p_obj, int class_type, int index)
    {
        int pos = 0;
        char filename[FILE_NAME_LENGTH];
        int len = get_obj_len(class_type);
        if (class_type == CLASS_mDetectDeviceConfig) {
            pos = 0;
        } else {
            pos = index * len;
        }


        char *p_dst = NULL;
        switch (class_type) {
        case CLASS_mCamParam:
            //memcpy(&g_cam_cfg[index],p_obj,len);
            //	p_dst=(char *)&g_cam_cfg[index].cam_param;
            sprintf(filename, "./cfg/%s", "cam_param");
            break;
        case CLASS_mDetectDeviceConfig:
            //	p_dst=(char *)&g_dev_cfg;
            sprintf(filename, "./cfg/%s", "dev_config");
            break;
        case CLASS_mCamDetectParam:
            //	p_dst=(char *)&g_cam_cfg[index].det_param;
            sprintf(filename, "./cfg/%s", "det_param");
            //prt(info,"===11111>%d====>>> %d",g_cam_cfg[index].det_param.area.vircoordinate[2].x,((mCamDetectParam*)p_obj)->area.vircoordinate[2].x);
            break;

        default:
           // prt(info, "unsupported save class %d", class_type)
           // ;
            break;
        }
        //	memcpy(p_dst,p_obj,len);
        load_buf(filename, (char *) p_obj, pos, len);
    }
};
#include <QPoint>
class FvdVideoProcessor
{
    loader l;
     RESULTMSG outbuf;
     m_args alg_arg;
     LANEINISTRUCT LaneIn;
     loader::mCamParam obj_mCamParam;
     loader::mCamDetectParam obj_mCamDetectParam;
     loader::mDetectDeviceConfig obj_mDetectDeviceConfig;
public:
     QPoint pt[16];
     QPoint pt_rear[16];
    FvdVideoProcessor()
    {

        l.load_obj((unsigned char *) &obj_mCamParam, loader::CLASS_mCamParam, 0);
        l.load_obj((unsigned char *) &obj_mCamDetectParam, loader::CLASS_mCamDetectParam, 0);
        l.load_obj((unsigned char *) &obj_mDetectDeviceConfig, loader::CLASS_mDetectDeviceConfig, 0);
        memset(alg_arg.m_ptEnd, 0, sizeof(alg_arg.m_ptEnd));
        memset(alg_arg.ptimage, 0, sizeof(alg_arg.ptimage));
        memset(&LaneIn,0,sizeof(LaneIn));
        lane_param_init(0,&obj_mCamDetectParam.detectparam[1],&obj_mCamParam.camdem,&LaneIn);
        lane_pos_init(obj_mCamDetectParam.detectlane.virtuallane,
                obj_mCamDetectParam.laneline.laneline,
                      alg_arg.m_ptEnd,obj_mCamDetectParam.detectlane.lanenum);

        for (int i = 0; i < 16; i++)
        {
        //   qDebug("%d %d\n",(obj_mCamDetectParam.detectlane.virtuallane[i / 4].Front[i % 4].x, obj_mCamDetectParam.detectlane.virtuallane[i / 4].Front[i % 4].y));
           pt[i].setX(obj_mCamDetectParam.detectlane.virtuallane[i / 4].Front[i % 4].x);
           pt[i].setY(obj_mCamDetectParam.detectlane.virtuallane[i / 4].Front[i % 4].y);
            //        graHandle_trans.DrawEllipse(RedPen, overlay_data.rear[i].X, overlay_data.rear[i].Y, 20, 20);
         //  qDebug("%d %d\n",obj_mCamDetectParam.detectlane.virtuallane[i / 4].Rear[i % 4].x, obj_mCamDetectParam.detectlane.virtuallane[i / 4].Rear[i % 4].y);

           pt_rear[i].setX(obj_mCamDetectParam.detectlane.virtuallane[i / 4].Rear[i % 4].x);
           pt_rear[i].setY(obj_mCamDetectParam.detectlane.virtuallane[i / 4].Rear[i % 4].y);
        }

        int i;
        for(i=0; i<6; i++){
           alg_arg.ptimage[i].x =100;
            alg_arg.ptimage[i].y =100;
        }
       transform_init_DSP_VC(1, 3,LaneIn,&outbuf,&alg_arg);
    }






    int lane_param_init(int curstatus, loader::mDetectParam *tmpDetect,loader::mCamDemarcateParam * tmpCamdem , LANEINISTRUCT *LaneIn)
    {
     //   print_alg("alg ctrl switch");

         LaneIn->uTransFactor=tmpDetect[curstatus].uTransFactor;
         LaneIn->uGraySubThreshold=tmpDetect[curstatus].uGraySubThreshold;
         LaneIn->uSpeedCounterChangedThreshold=tmpDetect[curstatus].uSpeedCounterChangedThreshold;
         LaneIn->uSpeedCounterChangedThreshold1=tmpDetect[curstatus].uSpeedCounterChangedThreshold1;
         LaneIn->uSpeedCounterChangedThreshold2=tmpDetect[curstatus].uSpeedCounterChangedThreshold2;
         LaneIn->uDayNightJudgeMinContiuFrame=tmpDetect[curstatus].uDayNightJudgeMinContiuFrame;
         LaneIn->uComprehensiveSens=tmpDetect[curstatus].uComprehensiveSens;
         LaneIn->uDetectSens1=tmpDetect[curstatus].uDetectSens1;
         LaneIn->uDetectSens2=tmpDetect[curstatus].uDetectSens2;
         LaneIn->uStatisticsSens1=tmpDetect[curstatus].uStatisticsSens1;
         LaneIn->uStatisticsSens2=tmpDetect[curstatus].uStatisticsSens2;
         LaneIn->uSobelThreshold=tmpDetect[curstatus].uSobelThreshold;

    //	memcpy(& LaneIn,\
    //			&tmpDetect[curstatus],\
    //			& LaneIn->uEnvironmentStatus-  \
    //			& LaneIn->uTransFactor);

         LaneIn->uEnvironment=  1;
         LaneIn->uEnvironmentStatus=  3;
         LaneIn->base_length = (float)tmpCamdem->baselinelen;
         LaneIn->near_point_length = (float)tmpCamdem->recent2stop;
        return 0;
    }
    int lane_pos_init(loader::mChannelCoil *tmpcoil, loader::mLine *tmpline,CPoint *m_ptEnd,int lanenum)
    {
        int i=0;
        for(i=0; i<lanenum; i++)
        {
            m_ptEnd[0+i*12].x = tmpline[i*2].startx;
            m_ptEnd[0+i*12].y = tmpline[i*2].starty;
            m_ptEnd[2+i*12].x = tmpline[i*2+1].startx;
            m_ptEnd[2+i*12].y = tmpline[i*2+1].starty;
            m_ptEnd[4+i*12].x = tmpcoil[i].Front[1].x;
            m_ptEnd[4+i*12].y = tmpcoil[i].Front[1].y;

            m_ptEnd[5+i*12].x = tmpcoil[i].Front[2].x;
            m_ptEnd[5+i*12].y = tmpcoil[i].Front[2].y;

            m_ptEnd[6+i*12].x = tmpcoil[i].Front[0].x;
            m_ptEnd[6+i*12].y = tmpcoil[i].Front[0].y;
            m_ptEnd[7+i*12].x = tmpcoil[i].Front[3].x;
            m_ptEnd[7+i*12].y = tmpcoil[i].Front[3].y;
            m_ptEnd[8+i*12].x = tmpcoil[i].Rear[1].x;
            m_ptEnd[8+i*12].y = tmpcoil[i].Rear[1].y;
            m_ptEnd[9+i*12].x = tmpcoil[i].Rear[2].x;
            m_ptEnd[9+i*12].y = tmpcoil[i].Rear[2].y;
            m_ptEnd[10+i*12].x = tmpcoil[i].Rear[0].x;
            m_ptEnd[10+i*12].y = tmpcoil[i].Rear[0].y;
            m_ptEnd[11+i*12].x = tmpcoil[i].Rear[3].x;
            m_ptEnd[11+i*12].y = tmpcoil[i].Rear[3].y;

            m_ptEnd[1+i*12].x = tmpline[i*2].endx;
            m_ptEnd[1+i*12].y = tmpline[i*2].endy;
            m_ptEnd[3+i*12].x = tmpline[i*2+1].endx;
            m_ptEnd[3+i*12].y = tmpline[i*2+1].endy;
        }
        return 0;
    }


    void handle_frame(unsigned char *yuv_buf)
    {
       transform_Proc_DSP_VC(yuv_buf,yuv_buf+640*480/4*1,yuv_buf+640*480/4*2,640,480,0,&outbuf,&alg_arg);
       qDebug("pos %d",alg_arg.p_outbuf->LineUp[0][1].y);
   //qDebug("%d",alg_arg.p_outbuf->LineUp[1][1].y);
       //        p1.setX(alg_arg.p_outbuf->LineUp[0][1].x);
//        p1.setY(alg_arg.p_outbuf->LineUp[0][1].y);

//        p2.setX(alg_arg.p_outbuf->LineUp[1][1].x);
//        p2.setY(alg_arg.p_outbuf->LineUp[1][1].y);

//        p3.setX(alg_arg.p_outbuf->LineUp[2][1].x);
//        p3.setY(alg_arg.p_outbuf->LineUp[2][1].y);
          //   return1 ret;
    }

};

#endif // VIDEOPROCESSOR_H
