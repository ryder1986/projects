#ifndef FILEDATABASE_H
#define FILEDATABASE_H
#include <QObject>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

#include "tool1.h"
class FileDatabase
{
private:
    void save(QByteArray data)
    {
        QFile *f=new QFile(name);
        bool ret = f->open(QIODevice::ReadWrite|QIODevice::Truncate);
        if(!ret){
            prt(info,"fail to open %s",name.toStdString().data());
            delete f;
        }
        f->write(data);
        f->close();
    }
//    void save(QJsonObject obj)
//    {
//        QJsonDocument data(obj);
//        QFile *f=new QFile(name);
//        bool ret = f->open(QIODevice::ReadWrite|QIODevice::Truncate);
//        if(!ret){
//            prt(info,"fail to open %s",name.toStdString().data());
//            delete f;
//        }
//        f->write(data.toJson());
//        f->close();
//    }
    bool load(QByteArray &data)
    {

        QFile *f=new QFile(name);
        bool ret = f->open(QIODevice::ReadOnly);
        if(!ret){
            delete f;
            return ret;
        }
        data=f->readAll();
        f->close();
        return ret;
    }
public:
    FileDatabase(QString file_name);
    void save(QJsonObject node)
    {
        QJsonDocument json_doc_new(node);
      //  json_doc_new.setObject(node);
        save(json_doc_new.toJson());
    }
    void load(QJsonObject &node)
    {
        QByteArray ba;
        QJsonDocument json_doc_new;
        if(load(ba)){
            json_doc_new=QJsonDocument::fromJson(ba);
            node=json_doc_new.object();
        }else{
        }
    }
private:
    QString name;
    QByteArray config;
};

#endif // FILEDATABASE_H
