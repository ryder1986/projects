#include "filedatabase.h"
#include "tool1.h"
FileDatabase::FileDatabase(QString file_name)
{
    name=file_name;
    config.clear();
    bool ret=load(config);
    if(ret){
        //prt(info,"open profile %s ok\ncontent:\n%s",name.toStdString().data(),config.toStdString().data());
    }else{
        prt(info,"open profile %s fail",name.toStdString().data());
    }
}

