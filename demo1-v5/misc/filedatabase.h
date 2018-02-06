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
    void set_config(QJsonObject node)
    {
        QJsonDocument json_doc_new;
        json_doc_new.setObject(node);
        save(json_doc_new.toJson());
    }
    void get_config(QJsonObject &node)
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
