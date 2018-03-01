#ifndef PD_H
#define PD_H
#include <cstring>
#include <QJsonObject>
class Pd
{
public:
    enum LENGTH_FIXED_VALUE{
        STR_LENGTH=100,
        PATH_LENGTH=1000,
        BUFFER_LENGTH=1000,
        BUFFER_MAX_LENGTH=3000
    };
public:
    Pd();

};


/*

head defination:

    /    head  /   /  body   /
    -- -- -- --    ---.......
    byte1-2:data body length,byte 3-4:protocol version, byte 5-6:operation,byte 7-8:reply rst,9->:body

*/

class Protocol{
public :
    const int static camera_max_num=8;
    enum VER{
        VERSION=1
    };
    enum LEN{
        HEAD_LENGTH=8
    };

    enum AABB{
        SS=0,
        PP=1
    };
    enum CMD{
        GET_CONFIG,
        SET_CONFIG,
        ADD_CAMERA,
        DEL_CAMERA,
        MOD_CAMERA_SRC,
        MOD_CAMERA_ALG,
        CAM_OUTPUT_OPEN,
        CAM_OUTPUT_CLOSE,       
        NEED_UPDATE,
        HEART
    };

    enum RET{
        RET_SUCCESS,
        RET_FAIL,
        RET_REFRESH
    };
    enum PORTS{
        SERVER_PORT=12345,
        SERVER_DATA_OUTPUT_PORT=12346,
        CLIENT_REPORTER_PORT=12347,
        SERVER_REPORTER_PORT=12348
    };



};

//class PackgeManager{
//    static int get_type()
//    {

//    }
//};

#endif // PD_H
