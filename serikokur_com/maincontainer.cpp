#include "maincontainer.h"


MainContainer::MainContainer(DB *mDB)
    :SerikBLDCore::DB(mDB)
{


    mSMSManager = new SMSManager(this->getDB());

    mBasvuruManager = new BasvuruManager(this->getDB());


    this->Content()->setContentAlignment(AlignmentFlag::Center);

    this->init();

}

MainContainer::~MainContainer()
{

    delete mSMSManager;
    delete mBasvuruManager;

}

void MainContainer::init()
{
    this->Content()->clear();

    this->initLogo();

    this->initBaskan();

    //    this->initDuyuruEtkinlik();

    this->initOduller();

    this->initKitaplar();

    this->initHakkinda();

    this->initIletisim();
}

void MainContainer::initLogo()
{

    auto uzatmaTextContainer = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
    uzatmaTextContainer->addStyleClass(Bootstrap::Grid::col_full_12);
    uzatmaTextContainer->setContentAlignment(AlignmentFlag::Center);
    uzatmaTextContainer->setMargin(35,Side::Top);
    auto utext = uzatmaTextContainer->addWidget(cpp14::make_unique<WText>("<p><b>SON BAŞVURU TARİHİ <i style=\"background-color: red;color:white;font-family: verdana;\">01/ARALIK/2021</i> TARİHİNE KADAR UZATILMIŞTIR.<br>"
                                                             "KİTAP SEVER TÜM ARKADAŞLARA DUYURULUR.</b><br><i>Sınav Tarihi: 19 Aralık 2021</i></p>",TextFormat::UnsafeXHTML));
    utext->addStyleClass("btn-darktoLite");



    auto basvuruSayisiContainer = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
    basvuruSayisiContainer->addStyleClass(Bootstrap::Grid::col_full_12);
    basvuruSayisiContainer->setContentAlignment(AlignmentFlag::Center);
    basvuruSayisiContainer->setMargin(35,Side::Top);

    auto container = basvuruSayisiContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    container->setMaximumSize(1250,WLength::Auto);
    container->setContentAlignment(AlignmentFlag::Right);
    auto itemCount = this->getDB()->countItem(SerikBLDCore::Item("basvuru"));

    auto text = container->addWidget(cpp14::make_unique<WText>("Başvuru Sayısı: "+std::to_string(itemCount)));
    text->addStyleClass("btn-grad");

    auto logoContainer = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
    logoContainer->addStyleClass(Bootstrap::Grid::col_full_12);
    logoContainer->setHeight(750);
    logoContainer->setAttributeValue(Style::style,Style::background::url("afis.png")+Style::background::position::center_center+Style::background::size::contain+Style::background::repeat::norepeat);
}

void MainContainer::initBaskan()
{
    auto logoContainer = this->Content()->addWidget(cpp14::make_unique<BaskanimizContainer>());
    logoContainer->addStyleClass(Bootstrap::Grid::col_full_12);
}

void MainContainer::initOduller()
{
    auto logoContainer = this->Content()->addWidget(cpp14::make_unique<OdullerContainer>());
    logoContainer->addStyleClass(Bootstrap::Grid::col_full_12);
}

void MainContainer::initHakkinda()
{
    auto logoContainer = this->Content()->addWidget(cpp14::make_unique<HakkindaContainer>());
    logoContainer->addStyleClass(Bootstrap::Grid::col_full_12);
}

void MainContainer::initKitaplar()
{
    auto logoContainer = this->Content()->addWidget(cpp14::make_unique<KitaplarContainer>());
    logoContainer->addStyleClass(Bootstrap::Grid::col_full_12);
}

void MainContainer::initIletisim()
{
    auto logoContainer = this->Content()->addWidget(cpp14::make_unique<IletisimContainer>(this->getDB()));
    logoContainer->addStyleClass(Bootstrap::Grid::col_full_12);
}

void MainContainer::initDuyuruEtkinlik()
{
    auto logoContainer = this->Content()->addWidget(cpp14::make_unique<DuyuruEtkinlikContainer>(/*this->getDB()*/));
    logoContainer->addStyleClass(Bootstrap::Grid::col_full_12);
}

void MainContainer::initLoginScreen( const std::string &telefon)
{

    auto mDialog = this->createDialog("Login");

    auto rContainer = mDialog->contents()->addWidget(cpp14::make_unique<WContainerWidget>());
    rContainer->addStyleClass(Bootstrap::Grid::row);

    auto username = rContainer->addWidget(cpp14::make_unique<WLineEdit>());
    username->addStyleClass(Bootstrap::Grid::col_full_12);
    username->setText(telefon);
    username->setEnabled(false);
    username->setEchoMode(EchoMode::Password);

    auto password = rContainer->addWidget(cpp14::make_unique<WLineEdit>());
    password->addStyleClass(Bootstrap::Grid::col_full_12);
    password->setEchoMode(EchoMode::Password);
    password->setPlaceholderText("Şifrenizi Giriniz");


    auto infoText = rContainer->addWidget(cpp14::make_unique<WText>(""));
    infoText->addStyleClass(Bootstrap::Grid::col_full_12);
    infoText->setTextAlignment(AlignmentFlag::Center);


    auto loginBtn = mDialog->footer()->addWidget(cpp14::make_unique<WPushButton>("Giriş"));
    loginBtn->addStyleClass(Bootstrap::Button::Primary);


    loginBtn->clicked().connect([=](){

        if( this->initUserPanel(telefon,password->text().toUTF8()) ){
            this->removeDialog(mDialog);
        }else{
            infoText->setText("<b>Hatalı Giriş</b>");
        }
    });


    mDialog->show();

}

void MainContainer::initSinavScreen(const std::string &tcno)
{


    std::string CurrentPassword = "";

    std::string errorOccured = "";
    //    {

    auto passCreator = [=](){

        QString pasword_;
        for( int i = 0 ; i < 5 ; i++ ){
            pasword_ += SKey::LetterSTR.at(this->getRandom(0,SKey::LetterSTR.count()-1));
        }
        return pasword_;

    };


    CurrentPassword = passCreator().toStdString();

    auto mDialog = this->createDialog("Giriş");

    auto rContainer = mDialog->contents()->addWidget(cpp14::make_unique<WContainerWidget>());
    rContainer->addStyleClass(Bootstrap::Grid::row);

    auto username = rContainer->addWidget(cpp14::make_unique<WLineEdit>());
    username->addStyleClass(Bootstrap::Grid::col_full_12);
    username->setText(tcno);
    username->setEnabled(false);
    username->setEchoMode(EchoMode::Password);

    auto password = rContainer->addWidget(cpp14::make_unique<WLineEdit>());
    password->addStyleClass(Bootstrap::Grid::col_full_12);
    password->setEchoMode(EchoMode::Password);
    password->setPlaceholderText("Telefonunuza Gelen Şifreyi Giriniz");




    auto infoText = rContainer->addWidget(cpp14::make_unique<WText>("Lütfen Sayfayı Yenilemeyiniz!"));
    infoText->addStyleClass(Bootstrap::Grid::col_full_12);
    infoText->setTextAlignment(AlignmentFlag::Center);


    auto loginBtn = mDialog->footer()->addWidget(cpp14::make_unique<WPushButton>("Giriş"));
    loginBtn->addStyleClass(Bootstrap::Button::Primary);







    BasvuruItem filter;
    filter.setTCNO(tcno);

    auto val = mBasvuruManager->FindOneItem(filter);

    if( val.view().empty() ){

        this->warnDialog("Hatalı Giriş");
        return;
    }else{
        SerikBLDCore::SMS::SMSItem smsItem;
        smsItem.setNumara(val.getCepNo().c_str());
        smsItem.setSMS("SerikOKUYOR: Tek Kullanımlık Şifreniz: " + QString::fromStdString(CurrentPassword));
//        mSMSManager->insertAndSendSMS(smsItem);
    }



    LOG << "Click: " << password->text().toUTF8() << " " << CurrentPassword << "\n";



    loginBtn->clicked().connect([=](){

        if( /*password->text().toUTF8() == CurrentPassword*/ true ){
            this->removeDialog(mDialog);
            this->Content()->clear();
            this->Content()->addWidget(cpp14::make_unique<SinavPanel>(this->getDB(),tcno));
        }else{
            infoText->setText("<b>Şifre Yada TCNO Hatalı</b>");
        }


    });


    mSMSManager->ErrorOccured().connect([=]( const std::string &errorText){
        infoText->setText("<b>"+errorText+"</b><i>"+mSMSManager->getLastError().toStdString()+"</i>");
        return;
    });

    mSMSManager->smsSended().connect([=]( const std::string &smsText){
        infoText->setText("<b>SMS Gönderildi. Lütfen Sayfayı Yenilemeyiniz</b>");

        return;
    });


    mDialog->show();

}

bool MainContainer::initUserPanel( const std::string &telefon , const std::string &password )
{

    User filter;
    filter.setPassword(password);
    filter.setTelefon(telefon);

    UserManager* mUserManager = new UserManager(this->getDB());

    auto _user = mUserManager->FindOneItem(filter);

    if( _user.view().empty() ){
        return false;
    }

    if( _user.isDisabled() ){
        return false;
    }

    delete  mUserManager;



    this->Content()->clear();
    this->Content()->setContentAlignment(AlignmentFlag::Center);
    this->Content()->addWidget(cpp14::make_unique<UserPanel>(this->getDB(),_user));
    return true;
}

bool MainContainer::initTCPanel(const std::string &tcno, const std::string &password)
{



//    auto passCreator = [=](){

//        QString pasword_;
//        for( int i = 0 ; i < 6 ; i++ ){
//            pasword_ += SKey::LetterSTR.at(this->getRandom(0,SKey::LetterSTR.count()-1));
//        }
//        return pasword_;

//    };


//    BasvuruItem filter;
//    filter.setTCNO(tcno);
//    BasvuruManager* mManager = new BasvuruManager(this->getDB());


    //    SerikBLDCore::SMSAbstractManager* mSMSManager = new SerikBLDCore::SMSAbstractManager





    //    mManager->setLimit(1000);

//    auto list = mManager->UpdateList();

    //    int counter = 0;


    //    for( const auto &item : list ){

    //        auto pasword = passCreator();


    //            filter.clear();
    //            filter.setOid(item.oid().value().to_string());
    //            filter.setPassword(pasword.toStdString());

    //            auto upt = mManager->UpdateItem(filter);

    //            if( upt ){
    //                std::cout << "PASSWORD CREATED: " << password <<" " << counter++ << "\n";
    //            }else{
    //                std::cout << "PASSWORD NOT\n";
    //            }

    //    }







//    delete mManager;

    return true;
}
