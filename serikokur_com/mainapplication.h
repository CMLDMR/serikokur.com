#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H

#include "mongoheaders.h"
#include "BaseClass/wtheaders.h"
#include "item.h"
#include "db.h"
#include "listitem.h"
#include "BaseClass/containerwiget.h"

#include "headercontainer.h"
#include "maincontainer.h"
#include "response.hpp"


using bsoncxx::builder::basic::document;
using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::array;
using bsoncxx::builder::basic::make_document;
using bsoncxx::builder::basic::make_array;


class MainApplication : public Wt::WApplication
{
public:
    MainApplication(const WEnvironment& env);
    ~MainApplication();
private:

//    Resource *mResource;

    mongocxx::client* mClient;

    mongocxx::database db;


    std::shared_ptr<Wt::WBootstrapTheme> p_wtTheme;


    void init();


    void initBackground();

    void initHeader();

    void initMain();

    ContainerWidget* mMainContainer_;

    WContainerWidget* mFooterContainer;


    void initHakkinda();

    void baskanmesaji();

    void Kitaplar();

    void initBasvuru();



private:
    HeaderContainer* mHeaderContainer;
    MainContainer* mMainContainer;

};

#endif // MAINAPPLICATION_H
