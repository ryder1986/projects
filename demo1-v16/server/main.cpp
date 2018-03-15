#include <QCoreApplication>
#include "filedatabase.h"
#include "server.h"
int main(int argc, char *argv[])
{


 //   prt(info,"start");
   // Tool1::set_debug_level(Tool1::DEBUG_LEVEL::FATAL);
  //  Tool1::set_label(Tool1::LABEL_SELECTION::BOTH);
    QCoreApplication a(argc, argv);
    FileDatabase db("config.json");
    Server svr(&db);

    return a.exec();
}
