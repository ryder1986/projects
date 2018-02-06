#ifndef TOOL1_H
#define TOOL1_H

#include <iostream>
#include <cstdio>
#include <chrono>
#include <thread>
#include <ctime>
#include <cstring>
#include <mutex>
#include <thread>
#include <bitset>
#include <list>
#include <iterator>

//#include <ifaddrs.h>
#include "tool1.h"


#ifdef IS_UNIX
#include <sys/stat.h>

#else
#include <direct.h>
#endif
using namespace std;


class LogFile{
    FILE *fp ;
public:
    LogFile(const char *fn)
    {
        log_file_open(fn);
    }
    LogFile()
    {
        log_file_open(NULL);
    }
    int write(const char *log)
    {
        fwrite(log, 1, strlen(log), fp);
        return 0;
    }

    ~LogFile()
    {
        fclose(fp);
    }
private:
    inline int log_file_open(const char *fname)
    {
        char filename[1000];
        char dirname[1000] = { "log" };
        //    FILE *tmp = fopen(dirname, "r");
        //            if(!tmp){

        //            prt(info,"quit");
        //            exit(0);
        //        }else{
        //            cout<<"exist"<<endl;
        //        }

#ifdef IS_UNIX
        mkdir(dirname,0755);
#else
        mkdir(dirname);
#endif


        // FILE *fp = NULL;
        time_t timer;
        struct tm *tblock;
        /* gets time of day */
        timer = time(NULL);
        /* converts date/time to a structure */
        tblock = localtime(&timer);
        sprintf(filename, "%d_%d_%d", tblock->tm_year - 100 + 2000, tblock->tm_mon+1,
                tblock->tm_mday);
        if (fname != NULL) {
            strcpy(filename, fname);
        }
        strcat(dirname, "/");
        strcat(dirname, filename);
        fp=NULL;
        fp = fopen(dirname, "a");
        if (fp != NULL) {
            //	fwrite(log, 1, strlen(log)+1, fp);
         //   fwrite(log, 1, strlen(log), fp);
            //  fclose(fp);
        } else {
            perror("file  open fail");
            printf("file :%s\n",dirname);
        }
        return 0;
    }
};




class Tool1
{
public:
    enum LENGTH_FIXED_VALUE{
        STR_LENGTH=100,
        PATH_LENGTH=1000,
        BUFFER_LENGTH=1000
    };

    enum DEBUG_LEVEL{//choose process debug mode
        USER_DEFINED,
        DEBUG,//print most thing(show the running process)
        INFO,//routine output(necessary outputs)
        WARN,//print when warn,take care
        ERROR1,//very serious
        FATAL//most serous
    };
    enum LABEL_SELECTION{
        NORMAL=1,
        PRIVATE,
        BOTH,
        MATCHED,
        NONE
    };
public:


    static mutex lock;
private:
    static LogFile log_file1;
    int cc=0;
    static  char filename[LENGTH_FIXED_VALUE::PATH_LENGTH];
    const int static buf_size=200;
    static int lv;//debug level,default is "DEBUG_LEVEL::INFO"
    //   static char match_label[LENGTH_FIXED_VALUE::STR_LENGTH];
    static string match_label;
    static int label_printable;//1:only print "debug to fatal" label 2:only print user-defined label 3:print both "debug to fatal" and user-defined label 4:only match match_label


    Tool1()
    {

    }
public:
    static void set_label(int label,string str=string())
    {
        match_label=str;
        label_printable=label;
    }
    static inline void set_debug_level(enum DEBUG_LEVEL level=DEBUG_LEVEL::INFO)
    {
        lv=level;
    }

    inline static string last_substr(string str,char split_ch)
    {
        char tmp[LENGTH_FIXED_VALUE::BUFFER_LENGTH];
        memset(tmp,0,LENGTH_FIXED_VALUE::BUFFER_LENGTH);
        strcpy(tmp,str.data());
        char *p=tmp;
        int total=0;
        char *p1=p;
        while(0!=*(++p)){
            if(*p==split_ch){
                p1=p+1;
                total++;
            }
        }
        return string(p1);
    }

    inline static void prt(const char *buf,const int line_no,const char *func_name,const char *file_name,const char *label,const char *time)
    {
        //        char buffer[buf_size];
        //        memset(buffer,0,buf_size);
        //        memcpy(buffer,time,strlen(time));
        //        buffer[i]='\0';

        //   cout<<"("<<buf<<")"<<'['<<line_no<<']'<<'['<<func_name<<']'<<'['<<file_name<<']'<<'['<<buffer<<']'<<'['<<label<<']'<<endl;
        //  cout<<"("<<buf<<")"<<'['<<line_no<<']'<<'['<<func_name<<']'<<'['<<file_name<<']'<<'['<<buffer<<']'<<'['<<label<<']'<<endl;

        string fn(file_name);
#if 0
#ifdef  IS_UNIX
        char t='/';
#elseik
        char t='\\';
#endif
        cout<<last_substr(fn,t).data()<<"(line"<<line_no<<")"<<":"<<buf<<endl;
#endif
        //     cout<<last_substr(last_substr(fn,'/'),'\\').data()<<"(line"<<line_no<<")"<<":"<<buf<<endl;
        int debug_level=0;
        if(!strcmp("info",label)){
            debug_level=DEBUG_LEVEL::INFO;
        }else         if(!strcmp("debug",label)){
            debug_level=DEBUG_LEVEL::DEBUG;
        }else         if(!strcmp("warn",label)){
            debug_level=DEBUG_LEVEL::WARN;
        }else         if(!strcmp("error",label)){
            debug_level=DEBUG_LEVEL::ERROR1;
        }else         if(!strcmp("fatal",label)){
            debug_level=DEBUG_LEVEL::FATAL;
        }else {
            debug_level=DEBUG_LEVEL::USER_DEFINED;
        }
        //        cout<<debug_level<<endl;
        //        cout<<label_printable<<endl;
        //         cout<<debug_level<<endl;
        //          cout<<lv<<endl;
        bool flg=false;
        //        if(DEBUG_LEVEL::INFO<=debug_level&&debug_level<=DEBUG_LEVEL::FATAL)
        //            flg=true;

        switch(label_printable){
        case LABEL_SELECTION::BOTH:
            if((lv<=debug_level&&debug_level<=DEBUG_LEVEL::FATAL)||debug_level==DEBUG_LEVEL::USER_DEFINED)
                flg=true;
            break;
        case LABEL_SELECTION::NORMAL:
            if(lv<=debug_level&&debug_level<=DEBUG_LEVEL::FATAL)
                flg=true;
            break;
        case LABEL_SELECTION::MATCHED:
            if(debug_level==DEBUG_LEVEL::USER_DEFINED&&!strcmp(label,match_label.data()))
                flg=true;
            break;
        case LABEL_SELECTION::PRIVATE:
            if(debug_level==DEBUG_LEVEL::USER_DEFINED)
                flg=true;
            break;
        case LABEL_SELECTION::NONE:break;
        }
        string tmp_str;
        tmp_str.clear();
        char buf1[100];
        memset(buf1,0,100);
        sprintf(buf1,"%d",line_no);
        if(flg){
            tmp_str.append("[").append(time).append("][").append(label).append("][").\
                    append(last_substr(last_substr(fn,'/'),'\\').data()).append(",").append(buf1).append(",").append(func_name).append("]===>").append(buf).append("\n");
            cout<<tmp_str;
            log_file1.write(tmp_str.data());
            fflush(NULL);
        }
    }
    inline static char* get_time_n()
    {
        chrono::system_clock::time_point today= chrono::system_clock::now();
        time_t tt= chrono::system_clock::to_time_t(today);
        return ctime(&tt);
    }
    inline static string get_time()
    {
        chrono::system_clock::time_point today= chrono::system_clock::now();
        time_t tt= chrono::system_clock::to_time_t(today);
        string tm(ctime(&tt));
        unsigned int pos=tm.find('\n');
        if(pos!=string::npos){
            tm[pos]=0;
        }

        return tm;
    }

    static int  aaaa;
    static const int ss=123;
    enum test{
        ABC=1,
        BCD=2
    };
    typedef test sss;

    void aaa()
    {



    }




};
#define prt(label,...) {Tool1::lock.lock(); char buf[Tool1::LENGTH_FIXED_VALUE::BUFFER_LENGTH];sprintf(buf,__VA_ARGS__);\
    Tool1::prt(buf,__LINE__,__FUNCTION__,__FILE__,#label,Tool1::get_time().data());Tool1::lock.unlock();}
#define THREAD_DEF(cls,fun) new thread(std::mem_fn(&cls::fun),*(cls*)this);


#endif // TOOL1_H
