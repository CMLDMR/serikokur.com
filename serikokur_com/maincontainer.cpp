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







//    this->initYarismaDetail();

    this->initLogo();

    this->initBaskan();

    //    this->initDuyuruEtkinlik();

    this->initOduller();

    this->initKitaplar();

    this->initHakkinda();

    this->initIletisim();
}

void MainContainer::initYarismaDetail()
{


        auto container = Content()->addWidget(cpp14::make_unique<WContainerWidget>());
        container->setPositionScheme(PositionScheme::Fixed);
        container->setWidth(WLength("100%"));
        container->setHeight(WLength("100%"));
        container->setAttributeValue(Style::style,Style::background::color::rgba(0,0,0,0.85));
        container->setOffsets(0,Side::Top|Side::Left);
        container->setZIndex(999);

        auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());
        vLayout->addStretch(1);
        auto text = vLayout->addWidget(cpp14::make_unique<WText>("<p><b>Değerli Kitapsever Vatandaşımız,</b></p>"
                                                                 "<p>Yarışmacılar arasında eşitlik ve adaleti sağlamak amacıyla geniş katılım aralığı verilmeyecektir.</p>"
                                                                 "<p>Tüm yarışmacılar için sınava giriş saati 20.00 ile 20.15 arasında olup sınav süresi giriş yapılmasından itibaren 30 dakikadır.</p>"
                                                                 "<p>Sınav giriş şifreniz 17 Aralık itibariyle size mesaj olarak  gönderilecektir.</p>"
                                                                 "<p>Okumaya verdiğiniz değer için teşekkür ederiz.</p>"
                                                                 "<p style=\"color:red;\"><b>Dereceye Giren Yarışmacılarımız;</b></p>"
                                                                 "<p style=\"color:red;\"><b>■ 18 Yaş Altı Herhangi Bir Şart Aranmayacaktır.</b></p>"
                                                                 "<p style=\"color:red;\"><b>■ 18 Yaş Üstü Kişiler Öğrenci Belgesi yoksa İkametgah Belgesi İbraz Etmek Zorundadır.</b></p>"
                                                                 "<p><h4>SERİK OKUYOR YÜRÜTME KURULU</h4>",TextFormat::UnsafeXHTML));
        text->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue));
        vLayout->addStretch(1);

        container->clicked().connect([=](){
            Content()->removeWidget(container);
        });

}

void MainContainer::initSifreAl()
{

    auto container = Content()->addWidget(cpp14::make_unique<WContainerWidget>());
    container->setPositionScheme(PositionScheme::Fixed);
    container->setWidth(WLength("100%"));
    container->setHeight(WLength("100%"));
    container->setAttributeValue(Style::style,Style::background::color::rgba(255,255,255,0.90));
    container->setOffsets(0,Side::Top|Side::Left);
    container->setZIndex(999);
    container->setContentAlignment(AlignmentFlag::Center);

    auto container_ = container->addWidget(cpp14::make_unique<WContainerWidget>());
    container_->setMaximumSize(1024,WLength::Auto);





    auto vLayout = container_->setLayout(cpp14::make_unique<WVBoxLayout>());
    vLayout->addStretch(1);

    auto text = vLayout->addWidget(cpp14::make_unique<WText>("<p><h4>Dikkat; Cep Telefonunuza SMS Gelmiyorsa İletişim Bölümünden Bize Yazınız</h4></p>",TextFormat::UnsafeXHTML));
    //            text->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue));


    auto tcnoLineEdit = vLayout->addWidget(cpp14::make_unique<WLineEdit>(),0,AlignmentFlag::Justify);
    tcnoLineEdit->setPlaceholderText("Lütfen TC Kimlik Numaranızı Giriniz");




    auto robotImage = vLayout->addWidget(cpp14::make_unique<RobotImage>());
    robotImage->setMaximumSize(1024,50);


    auto colorText = vLayout->addWidget(cpp14::make_unique<WText>(WString("<p><b>{1}</b> Renkteki Kodu Giriniz."
                                                                          "<br>Kodu Okuyamıyorsanız Üstüne Tıklayarak Yenileyebilirsiniz</p>").arg(robotImage->currentColor()),TextFormat::UnsafeXHTML));


    robotImage->colorClicked().connect([=](const std::string& colorName){
        auto color = colorName;
        if( colorName == "Siyah" ){
            color = "black";
        }else if( colorName == "Mavi"){
            color = "blue";
        }else if( colorName == "Kırmızı"){
            color = "red";
        }else if( colorName == "Yeşil"){
            color = "green";
        }

        colorText->setText(WString("<p><b style=\"color:white;background-color:"+color+";\">{1}</b> Renkteki Kodu Giriniz."
                                                                                       "<br>Kodu Okuyamıyorsanız Üstüne Tıklayarak Yenileyebilirsiniz</p>").arg(colorName));
    });


    auto belirtilenKodeLineEdit = vLayout->addWidget(cpp14::make_unique<WLineEdit>(),0,AlignmentFlag::Center);
    belirtilenKodeLineEdit->setPlaceholderText("Resimde Belirtilen Kodu Giriniz");


    auto getSMSbtn = vLayout->addWidget(cpp14::make_unique<WPushButton>("Tek Kullanımlık Şifre İste"));
    getSMSbtn->addStyleClass(Bootstrap::Button::Primary);
    getSMSbtn->clicked().connect([=](){

        if( robotImage->correctValue() != belirtilenKodeLineEdit->text().toUTF8() ){
            this->warnDialog("Güvenlik Kodu Hatalı Tekrar Deneyiniz");
            return;
        }

        BasvuruItem filter;
        filter.setTCNO(tcnoLineEdit->text().toUTF8());

        auto val = this->mBasvuruManager->FindOneItem(filter);

        if( val.view().empty() ){

            this->warnDialog("TCNO Bulunamadı");

            return;
        }

        container_->setAttributeValue(Style::dataoid,val.oid().value().to_string());

        this->mDogrulamaKodu = robotImage->generateText();

        SerikBLDCore::SMS::SMSItem smsItem;
        smsItem.setNumara(val.getCepNo().c_str());
        smsItem.setSMS(robotImage->correctValue().c_str()+QString(" Güvenlik Kodlu Tek Kullanımlık Şifreniz: ")+mDogrulamaKodu.c_str());


        if( mSMSManager->insertAndSendSMS(smsItem) ){
            getSMSbtn->setEnabled(false);
            getSMSbtn->setText("SMS Gönderildi");
        }else{
            this->warnDialog("Bir Hata Oluştu. " + mSMSManager->getLastError().toStdString());
            getSMSbtn->setText("Bir Hata Oluştu. Sayfayı Yenileyiniz");
            getSMSbtn->addStyleClass(Bootstrap::Button::Danger);
        }

    });

    vLayout->addStretch(1);

    vLayout->addSpacing(50);

    auto tekKullanimlikLineEdit = vLayout->addWidget(cpp14::make_unique<WLineEdit>(),0,AlignmentFlag::Center);
    tekKullanimlikLineEdit->setPlaceholderText("Cep Telefonunuza Gelen Tek Kullanımlık Şifrenizi Giriniz");


    auto yeniSifreLineEdit = vLayout->addWidget(cpp14::make_unique<WLineEdit>(),0,AlignmentFlag::Center);
    yeniSifreLineEdit->setPlaceholderText("Yeni Şifrenizi Giriniz");
    yeniSifreLineEdit->setEchoMode(EchoMode::Password);

    auto yeniSifreLineEditTekrar = vLayout->addWidget(cpp14::make_unique<WLineEdit>(),0,AlignmentFlag::Center);
    yeniSifreLineEditTekrar->setPlaceholderText("Yeni Şifrenizi Tekrar Giriniz");
    yeniSifreLineEditTekrar->setEchoMode(EchoMode::Password);

    auto savePasswordBTN = vLayout->addWidget(cpp14::make_unique<WPushButton>("Kaydet"));
    savePasswordBTN->addStyleClass(Bootstrap::Button::Primary);

    savePasswordBTN->clicked().connect([=](){

        if( yeniSifreLineEdit->text().toUTF8().size() < 5 ){
            this->warnDialog("Şifreniz En Az 5 Haneli Olmalıdır");
            return;
        }



        if( this->mDogrulamaKodu != tekKullanimlikLineEdit->text().toUTF8() ){
            this->warnDialog("Tek Kullanımlık Şifreniz Hatalı");
            return;
        }

        if( yeniSifreLineEdit->text().toUTF8() != yeniSifreLineEditTekrar->text().toUTF8() ){
            this->warnDialog("Şifreniz Uyumsuz");
            return;
        }

        BasvuruItem filter;
        filter.setOid(container_->attributeValue(Style::dataoid).toUTF8());
        filter.setPassword(yeniSifreLineEditTekrar->text().toUTF8());

        if( mBasvuruManager->UpdateItem(filter) ){
            this->informDialog("Şifreniz Oluşturuldu.Sınava Bu Şifreniz İle Girebilirsiniz.Unutmanız Durumunda Tekrardan Şifre Oluşturabilirsiniz");
            savePasswordBTN->setEnabled(false);
            savePasswordBTN->setText("Kayıt Başarılı");
            Content()->removeWidget(container);
        }else{
            this->warnDialog("Bir Hata Oluştu: " + mBasvuruManager->lastError());

        }


    });
    vLayout->addStretch(1);

}

void MainContainer::initLogo()
{

    {
        auto uzatmaTextContainer = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
        uzatmaTextContainer->addStyleClass(Bootstrap::Grid::col_full_12);
        uzatmaTextContainer->setContentAlignment(AlignmentFlag::Center);
        uzatmaTextContainer->setMargin(35,Side::Top);
//            auto utext = uzatmaTextContainer->addWidget(cpp14::make_unique<WText>("<p><b>BAŞVURULAR SONA ERDİ.<br>"
//                                                                                  "</b><i>Sınav Tarihi: 19 Aralık 2021</i><br>"
//                                                                                  "Yarışma Hakkında Detaylı Bilgi İçin Tıklayınız.</p>",TextFormat::UnsafeXHTML));

        auto utext = uzatmaTextContainer->addWidget(cpp14::make_unique<WText>("<p>Şifrenizi Almak için Tıklayınız</p>",TextFormat::UnsafeXHTML));
        utext->addStyleClass("btn-darktoLite");
//            uzatmaTextContainer->clicked().connect([=](){
//                this->initYarismaDetail();
//            });

        uzatmaTextContainer->clicked().connect([=](){
            this->initSifreAl();
        });
    }

    {
        auto uzatmaTextContainer = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
        uzatmaTextContainer->addStyleClass(Bootstrap::Grid::col_full_12);
        uzatmaTextContainer->setContentAlignment(AlignmentFlag::Center);
        uzatmaTextContainer->setMargin(35,Side::Top);

        auto utext = uzatmaTextContainer->addWidget(cpp14::make_unique<WText>("<p>Giriş İçin Tıklayınız</p>",TextFormat::UnsafeXHTML));
        utext->addStyleClass("btn-darktoLite");

        uzatmaTextContainer->clicked().connect([=](){
            this->initSinavScreen();
        });
    }






    auto basvuruSayisiContainer = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
    basvuruSayisiContainer->addStyleClass(Bootstrap::Grid::col_full_12);
    basvuruSayisiContainer->setContentAlignment(AlignmentFlag::Center);
    basvuruSayisiContainer->setMargin(35,Side::Top);

    auto container = basvuruSayisiContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    container->setMaximumSize(1250,WLength::Auto);
    container->setContentAlignment(AlignmentFlag::Right);
//    auto itemCount = this->getDB()->countItem(SerikBLDCore::Item("basvuru"));

    auto text = container->addWidget(cpp14::make_unique<WText>("Başvuru Sayısı: 724"));
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



//    LOG << "Click: " << password->text().toUTF8() << " " << CurrentPassword << "\n";



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

void MainContainer::initSinavScreen()
{


    auto mDialog = this->createDialog("Giriş");

    auto rContainer = mDialog->contents()->addWidget(cpp14::make_unique<WContainerWidget>());
    rContainer->addStyleClass(Bootstrap::Grid::row);

    auto username = rContainer->addWidget(cpp14::make_unique<WLineEdit>());
    username->addStyleClass(Bootstrap::Grid::col_full_12);
    username->setPlaceholderText("TCNO Giriniz");

    auto password = rContainer->addWidget(cpp14::make_unique<WLineEdit>());
    password->addStyleClass(Bootstrap::Grid::col_full_12);
    password->setEchoMode(EchoMode::Password);
    password->setPlaceholderText("Şifreyi Giriniz");


    auto loginBtn = mDialog->footer()->addWidget(cpp14::make_unique<WPushButton>("Giriş"));
    loginBtn->addStyleClass(Bootstrap::Button::Primary);

//    auto robotScreen = rContainer->addWidget(cpp14::make_unique<RobotImage>());
//    robotScreen->setWidth(WLength("100%"));
//    robotScreen->setHeight(50);
//    robotScreen->addStyleClass(Bootstrap::Grid::col_full_12);


    loginBtn->clicked().connect([=](){


        BasvuruItem filter;
        filter.setTCNO(username->text().toUTF8());
        filter.setPassword(password->text().toUTF8());


        auto val = mBasvuruManager->FindOneItem(filter);

        if( val.view().empty() ){
            this->warnDialog("Hatalı Giriş");
            return;
        }else{
            this->removeDialog(mDialog);
            this->Content()->clear();
            this->Content()->addWidget(cpp14::make_unique<SinavPanel>(this->getDB(),val.getTCNO()));
        }


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
