#include <QCoreApplication>
#include "filedatabase.h"
#include "server.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    FileDatabase db("config.json");
    Server svr(&db);
    return a.exec();
}
