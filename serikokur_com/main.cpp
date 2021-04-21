#include <QCoreApplication>
#include "db.h"
#include <mongocxx/instance.hpp>
#include <QApplication>
#include "mainapplication.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    mongocxx::instance ins{};


    return Wt::WRun(argc,argv,[](const Wt::WEnvironment &env){
        return Wt::cpp14::make_unique<MainApplication>(env);
    });

}
