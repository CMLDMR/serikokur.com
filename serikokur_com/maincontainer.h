#ifndef MAINCONTAINER_H
#define MAINCONTAINER_H

#include "BaseClass/containerwiget.h"
#include "listitem.h"
#include "baskanimizcontainer.h"
#include "odullercontainer.h"
#include "hakkindacontainer.h"
#include "kitaplarcontainer.h"
#include "iletisimcontainer.h"
#include "duyuruetkinlikcontainer.h"
#include "user/userpanel.h"
#include "root/basvuruitem.h"
#include "root/smsmanager.h"
#include "user/sinavpanel.h"


class MainContainer : public ContainerWidget , public SerikBLDCore::DB
{
public:
    MainContainer(SerikBLDCore::DB* mDB);
    ~MainContainer();

    void init();

    void initLogo();

    void initBaskan();

    void initOduller();

    void initHakkinda();

    void initKitaplar();

    void initIletisim();

    void initDuyuruEtkinlik();

    void initLoginScreen(const std::string &telefon);

    void initSinavScreen(const std::string &tcno);


    bool initUserPanel(const std::string &telefon, const std::string &password );

    bool initTCPanel( const std::string &tcno , const std::string &password );

private:

    SMSManager *mSMSManager;

    BasvuruManager* mBasvuruManager;

};

#endif // MAINCONTAINER_H
