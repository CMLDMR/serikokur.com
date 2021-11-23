#include <QCoreApplication>
#include "db.h"
#include <mongocxx/instance.hpp>
#include <QApplication>
#include "mainapplication.h"


std::unique_ptr<WApplication> createApplication(const WEnvironment& env)
{
  std::unique_ptr<WApplication> app
      = cpp14::make_unique<MainApplication>(env);
  return app;
}




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    mongocxx::instance ins{};

//    for( int i = 0 ; i < argc ; i++ ){
//        LOG << argv[i] << LOGEND;
//    }

//    Resource resource;

    return Wt::WRun(argc,argv,[](const Wt::WEnvironment &env){
        return Wt::cpp14::make_unique<MainApplication>(env);
    });

//        server1.addResource(&resource, "/users");
//        server1.addResource(&resource, "/users/${user}");
//        server1.addResource(&resource, "/users/${user}/post");
//        server1.addResource(&resource, "/users/${user}/post/${val}");


//    try {
//        int argc = 5;
//        auto argv1 = std::unique_ptr<char*[]>(new char*[argc]);

//        argv1[0] = (char *) "D:/project/Yonetim-yazilimi/serikokur.com/serikokur-com/build-serikokur_com-MSVC2017X64_Qt_5_13_1-Release/release/serikokur_com.exe";
//        argv1[1] = (char *) "--http-address=192.168.0.31";
//        argv1[2] = (char *) "--http-port=8443";
//        argv1[3] = (char *) "--docroot=.;docroot";
//        argv1[4] = (char *) "--approot=approot";
////        argv1[5] = (char *) "--ssl-tmp-dh=dh2048.pem";
////        argv1[6] = (char *) "--ssl-private-key=server.key";
////        argv1[7] = (char *) "--ssl-certificate=server.crt";
////        argv1[8] = (char *) "--http-address=192.168.0.31";
////        argv1[9] = (char *) "--http-port=8080";

//        for( int i = 0 ; i < argc ; i++ ){
//            LOG << argv1[i] << LOGEND;
//        }

//        WServer server1(argc, argv1.get(), WTHTTP_CONFIGURATION);
//        LOG << "Server Created: " << LOGEND;
//        //server1.addEntryPoint(EntryPointType::Application,)
//        server1.addEntryPoint(EntryPointType::Application, createApplication);

//        server1.run();

//        LOG << "Server: " << server1.httpPort() << LOGEND;

////        if (server1.start()) {
////            LOG << "Server: " << server1.httpPort() << LOGEND;
////            LOG << "STARTED" << LOGEND;
////            server1.waitForShutdown();
////        }else{
////            LOG << "Server Can NOT STARTED" << LOGEND;
////        }
//    } catch (WServer::Exception& e) {
//        std::cerr << e.what() << std::endl;
//        LOG << e.what() << LOGEND;
//    } catch (std::exception &e) {
//        std::cerr << "exception: " << e.what() << std::endl;
//        LOG << e.what() << LOGEND;
//    }

}
