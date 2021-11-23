#include "mainapplication.h"

#include "BaseClass/containerwiget.h"
#include "bootstrap.h"
#include "inlinestyle.h"

MainApplication::MainApplication(const WEnvironment &env)
    :WApplication(env)
{
//    mResource = new Resource();

//    wApp->environment().server()->addResource(mResource,"/test");

    wApp->addMetaHeader(MetaHeaderType::Meta,"Content-Type","text/html; charset=windows-1254");

    wApp->addMetaHeader("description","Serik OKUYOR","text/html; charset=utf-8");

    WApplication::useStyleSheet(WLink("css.css"));

    p_wtTheme = std::make_shared<Wt::WBootstrapTheme>();

    p_wtTheme->setVersion(Wt::WBootstrapTheme::Version::v3);

    p_wtTheme.get()->setResponsive(true);

    Wt::WApplication::instance()->setTheme(p_wtTheme);

    Wt::WApplication::instance()->useStyleSheet("resources/themes/bootstrap/3/bootstrap-theme.min.css");

    Wt::WApplication::instance()->addMetaLink("20180126113337667.ico","shortcut icon","","","image/x-icon","16x16",false);
    Wt::WApplication::instance()->setTitle("Serik OKUYOR");



    this->init();


    Wt::WApplication::require("script.js");

    //    Wt::WApplication::require("demo1.151408fb.js");


    WApplication::instance()->require("https://www.googletagmanager.com/gtag/js?id=G-T4V6LSK8WR");


    WApplication::instance()->doJavaScript("window.dataLayer = window.dataLayer || [];"
                                           "function gtag(){dataLayer.push(arguments);}"
                                           "gtag('js', new Date());"
                                           "gtag('config', 'G-T4V6LSK8WR');");







    mHeaderContainer = root()->addWidget(cpp14::make_unique<HeaderContainer>());

    mMainContainer = root()->addWidget(cpp14::make_unique<MainContainer>(new SerikBLDCore::DB(&db)));

    mHeaderContainer->MainClicked().connect(mMainContainer,&MainContainer::init);

    mHeaderContainer->BasvuruClicked().connect([=](){
        this->initBasvuru();
    });


    {
        auto copyRightContainer = root()->addWidget(cpp14::make_unique<WContainerWidget>());
        copyRightContainer->addStyleClass("copyRight");
        copyRightContainer->addWidget(cpp14::make_unique<WText>("© 2021"));
    }

    mFooterContainer = root()->addWidget(cpp14::make_unique<WContainerWidget>());
    //    mFooterContainer->setPositionScheme(PositionScheme::Fixed);
    mFooterContainer->setOffsets(0,Side::Left|Side::Bottom);
    mFooterContainer->setWidth(WLength("100%"));

    mFooterContainer->setHeight(75);
    mFooterContainer->addStyleClass("footer");
    mFooterContainer->setContentAlignment(AlignmentFlag::Center);

    {
        auto logo1 = mFooterContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        logo1->setWidth(WLength("100%"));
        logo1->setHeight(75);
        logo1->setAttributeValue(Style::style,Style::background::url("footer.png")+Style::background::size::contain+Style::background::position::center_center+Style::background::repeat::norepeat);
    }




    QMap<QString,QString> mapList;
    //    test Link : http://192.168.0.31:8080/?type=dilekce&_id=5daee97a6435000043002489 cevaplanmis
    // http://192.168.0.31:8080/?type=dilekce&_id=5daeebd8222400005d0005dc Cevaplanmamis
    for (const auto &str : env.getParameterMap() ) {
        //        std::cout << "First: " << str.first << " " << str.second.size() << " " << str.second.back() << std::endl;
        for( const auto &sec : str.second )
        {
            mapList[str.first.c_str ()] = QString::fromStdString (sec);
        }
    }



    //http://192.168.0.31:8080/?type=_login&ph=05335018051
    if( mapList.contains ("type") )
    {
        if( mapList["type"] == "_login" )
        {
            auto oid = mapList["ph"];
            if( oid.size() == 11 && oid.at(0) == '0' && oid.at(1) == '5'){
                mMainContainer->initLoginScreen(oid.toStdString());
            }
        }

        if( mapList["type"] == "exm" )
        {
            auto oid = mapList["ph"];
            if( oid.size() == 11 && oid.at(0) != '0'){
                mMainContainer->initSinavScreen(oid.toStdString());
            }
        }
    }

}

MainApplication::~MainApplication()
{

    LOG << "MainApplication Destruction" << LOGEND;
//    delete mResource;
    delete mClient;

}

void MainApplication::init()
{

    try {
        mClient = new mongocxx::client(mongocxx::uri("mongodb://HooverPhonic:Aa<05358564091>@192.168.0.11:27018/?authSource=admin"));
    } catch (mongocxx::exception& e) {
        std::cout << "MongoDB Connection Error: " << e.what() << std::endl;
        root()->addWidget(cpp14::make_unique<WText>("Driver Yüklenemedi!"));
        return;
    }

    db = mClient->database("SERIKOKUYOR");

}

void MainApplication::initBackground()
{
    auto bodyContainer = root()->addWidget(cpp14::make_unique<WContainerWidget>());
    bodyContainer->addStyleClass("demo-1 loading zIndex");
    bodyContainer->setHeight(WLength("100%"));
    bodyContainer->setPositionScheme(PositionScheme::Fixed);
    bodyContainer->setZIndex(-999);
    bodyContainer->setOffsets(0,Side::Top);

    auto mainContainer = bodyContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    mainContainer->setHtmlTagName("main");





    {
        auto contentContainer = mainContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        contentContainer->addStyleClass("content");
        contentContainer->setHeight(WLength("100%"));

        auto gridContainer = contentContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        gridContainer->addStyleClass("grid");


        {
            auto div = gridContainer->addWidget(cpp14::make_unique<WContainerWidget>());
            div->addStyleClass("grid__item pos-1");

            auto subdiv = div->addWidget(cpp14::make_unique<WContainerWidget>());
            subdiv->addStyleClass("grid__item-img");
            subdiv->setAttributeValue(Style::style,Style::background::url("1.dc197a9a.jpg"));
        }

        {
            auto div = gridContainer->addWidget(cpp14::make_unique<WContainerWidget>());
            div->addStyleClass("grid__item pos-2");

            auto subdiv = div->addWidget(cpp14::make_unique<WContainerWidget>());
            subdiv->addStyleClass("grid__item-img");
            subdiv->setAttributeValue(Style::style,Style::background::url("2.3ca6bb44.jpg"));
        }

        {
            auto div = gridContainer->addWidget(cpp14::make_unique<WContainerWidget>());
            div->addStyleClass("grid__item pos-3");

            auto subdiv = div->addWidget(cpp14::make_unique<WContainerWidget>());
            subdiv->addStyleClass("grid__item-img");
            subdiv->setAttributeValue(Style::style,Style::background::url("3.a433b89d.jpg"));
        }

        {
            auto div = gridContainer->addWidget(cpp14::make_unique<WContainerWidget>());
            div->addStyleClass("grid__item pos-4");

            auto subdiv = div->addWidget(cpp14::make_unique<WContainerWidget>());
            subdiv->addStyleClass("grid__item-img");
            subdiv->setAttributeValue(Style::style,Style::background::url("4.c6d96be5.jpg"));
        }

        {
            auto div = gridContainer->addWidget(cpp14::make_unique<WContainerWidget>());
            div->addStyleClass("grid__item pos-5");

            auto subdiv = div->addWidget(cpp14::make_unique<WContainerWidget>());
            subdiv->addStyleClass("grid__item-img");
            subdiv->setAttributeValue(Style::style,Style::background::url("5.689b68fd.jpg"));
        }


        {
            auto div = gridContainer->addWidget(cpp14::make_unique<WContainerWidget>());
            div->addStyleClass("grid__item pos-6");

            auto subdiv = div->addWidget(cpp14::make_unique<WContainerWidget>());
            subdiv->addStyleClass("grid__item-img");
            subdiv->setAttributeValue(Style::style,Style::background::url("6.e96dcfff.jpg"));
        }

        {
            auto div = gridContainer->addWidget(cpp14::make_unique<WContainerWidget>());
            div->addStyleClass("grid__item pos-7");

            auto subdiv = div->addWidget(cpp14::make_unique<WContainerWidget>());
            subdiv->addStyleClass("grid__item-img");
            subdiv->setAttributeValue(Style::style,Style::background::url("7.2d66e3ed.jpg"));
        }


        {
            auto div = gridContainer->addWidget(cpp14::make_unique<WContainerWidget>());
            div->addStyleClass("grid__item pos-8");

            auto subdiv = div->addWidget(cpp14::make_unique<WContainerWidget>());
            subdiv->addStyleClass("grid__item-img");
            subdiv->setAttributeValue(Style::style,Style::background::url("8.f4323fe0.jpg"));
        }

        {
            auto div = gridContainer->addWidget(cpp14::make_unique<WContainerWidget>());
            div->addStyleClass("grid__item pos-9");

            auto subdiv = div->addWidget(cpp14::make_unique<WContainerWidget>());
            subdiv->addStyleClass("grid__item-img");
            subdiv->setAttributeValue(Style::style,Style::background::url("9.c9233dac.jpg"));
        }

        {
            auto div = gridContainer->addWidget(cpp14::make_unique<WContainerWidget>());
            div->addStyleClass("grid__item pos-10");

            auto subdiv = div->addWidget(cpp14::make_unique<WContainerWidget>());
            subdiv->addStyleClass("grid__item-img");
            subdiv->setAttributeValue(Style::style,Style::background::url("10.5e22fdc3.jpg"));
        }


    }
}

void MainApplication::initHeader()
{



    {
        auto headerContainer = root()->addWidget(cpp14::make_unique<WContainerWidget>());

        headerContainer->addStyleClass("boxshadow headerHeight");
        headerContainer->setPositionScheme(PositionScheme::Fixed);
        headerContainer->setHeight(100);
        headerContainer->setWidth(WLength("100%"));
        headerContainer->setAttributeValue(Style::style,Style::background::color::color(Style::color::White::AliceBlue));
        headerContainer->setZIndex(100);
        headerContainer->setContentAlignment(AlignmentFlag::Center);
        headerContainer->setOffsets(0,Side::Top);

        auto container = headerContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container->setHeight(100);
        container->setMaximumSize(WLength(1280),WLength::Auto);
        container->setPositionScheme(PositionScheme::Relative);
        container->addStyleClass("headerHeight");

        auto titleLogo = container->addWidget(cpp14::make_unique<WContainerWidget>());
        titleLogo->setPositionScheme(PositionScheme::Absolute);
        titleLogo->setOffsets(0,Side::Left);
        titleLogo->setHeight(100);
        titleLogo->setWidth(200);
        titleLogo->addStyleClass("titleLogo");
        titleLogo->setAttributeValue(Style::style,Style::background::url("titleLogo.png")+
                                     Style::background::size::contain+
                                     Style::background::position::center_center+
                                     Style::background::repeat::norepeat);
        titleLogo->decorationStyle().setCursor(Cursor::PointingHand);
        titleLogo->clicked().connect(this,&MainApplication::initMain);




        {
            auto menuContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
            menuContainer->setPositionScheme(PositionScheme::Absolute);
            menuContainer->setOffsets(0,Side::Top|Side::Right);
            menuContainer->setHeight(100);
            menuContainer->addStyleClass("headerHeight");
            menuContainer->addStyleClass("menuContainer");


            auto vLayout = menuContainer->setLayout(cpp14::make_unique<WVBoxLayout>());

            auto menuRow = vLayout->addWidget(cpp14::make_unique<WContainerWidget>(),0,AlignmentFlag::Middle);

            auto textContainer = menuRow->addWidget(cpp14::make_unique<WContainerWidget>());

            auto hLayout = textContainer->setLayout(cpp14::make_unique<WHBoxLayout>());



            auto baskanimizText = hLayout->addWidget(cpp14::make_unique<WText>("<h4>Başkanımız</h4>"));
            baskanimizText->decorationStyle().setCursor(Cursor::PointingHand);
            baskanimizText->addStyleClass("mTitle");
            baskanimizText->clicked().connect(this,&MainApplication::baskanmesaji);

            auto hakkindaText = hLayout->addWidget(cpp14::make_unique<WText>("<h4>Hakkında</h4>"));
            hakkindaText->decorationStyle().setCursor(Cursor::PointingHand);
            hakkindaText->addStyleClass("mTitle");
            hakkindaText->clicked().connect(this,&MainApplication::initHakkinda);




            //            Wt::WLink link = Wt::WLink(LinkType::Url,"katilimsartname.pdf");
            //            link.setTarget(Wt::LinkTarget::NewWindow);

            //            std::unique_ptr<Wt::WAnchor> anchor =
            //                    Wt::cpp14::make_unique<Wt::WAnchor>(link,
            //                                                        "<h4>Katılım Şartları</h4>");

            //            hLayout->addWidget(std::move(anchor));


            auto basvuruText = hLayout->addWidget(cpp14::make_unique<WText>("<h4>Başvuru</h4>"));
            basvuruText->decorationStyle().setCursor(Cursor::PointingHand);
            basvuruText->addStyleClass("mTitle");
            basvuruText->clicked().connect(this,&MainApplication::initBasvuru);


            auto kitaplarText = hLayout->addWidget(cpp14::make_unique<WText>("<h4>Kitaplar</h4>"));
            kitaplarText->decorationStyle().setCursor(Cursor::PointingHand);
            kitaplarText->addStyleClass("mTitle");
            kitaplarText->clicked().connect(this,&MainApplication::Kitaplar);

            titleLogo->clicked().connect(this,&MainApplication::init);
        }

        {
            auto menuContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
            menuContainer->setPositionScheme(PositionScheme::Absolute);
            menuContainer->setOffsets(0,Side::Top|Side::Right);
            menuContainer->setHeight(100);
            menuContainer->setWidth(WLength("30%"));
            menuContainer->addStyleClass("headerHeight");
            menuContainer->addStyleClass("mobilContainer");

            {
                auto _container = menuContainer->addWidget(cpp14::make_unique<WContainerWidget>());
                _container->addStyleClass ("headerDown");
                _container->setHeight(50);
                //                            _container->addStyleClass(Bootstrap::Grid::Large::col_lg_1+Bootstrap::Grid::Medium::col_md_1+Bootstrap::Grid::Hidden::hidden_sm+Bootstrap::Grid::Hidden::hidden_xs);
                auto layout = _container->setLayout(cpp14::make_unique<WVBoxLayout>());
                auto text = layout->addWidget(cpp14::make_unique<WText>("MENÜ"),0,AlignmentFlag::Center|AlignmentFlag::Middle);
                text->setAttributeValue(Style::style,Style::color::color(Style::color::White::Snow)+Style::font::size::s14px);

                {
                    auto popContainer = layout->addWidget (cpp14::make_unique<WContainerWidget>());
                    popContainer->addStyleClass ("headerDown-content");

                    {
                        auto _pC = popContainer->addWidget (cpp14::make_unique<WContainerWidget>());
                        _pC->addStyleClass ("headerItem");
                        _pC->addWidget (cpp14::make_unique<WText>("Başkanımız"));
                        _pC->clicked().connect([=](){
                            this->baskanmesaji();
                        });
                    }

                    {
                        auto _pC = popContainer->addWidget (cpp14::make_unique<WContainerWidget>());
                        _pC->addStyleClass ("headerItem");
                        _pC->addWidget (cpp14::make_unique<WText>("Hakkında"));
                        _pC->clicked().connect([=](){
                            this->initHakkinda();
                        });
                    }

                    //                                {
                    //                                    auto _pC = popContainer->addWidget (cpp14::make_unique<WContainerWidget>());
                    //                                    _pC->addStyleClass ("headerItem");
                    //                                    Wt::WLink link = Wt::WLink(LinkType::Url,"katilimsartname.pdf");
                    //                                    link.setTarget(Wt::LinkTarget::NewWindow);

                    //                                    std::unique_ptr<Wt::WAnchor> anchor =
                    //                                            Wt::cpp14::make_unique<Wt::WAnchor>(link,
                    //                                                                                "Katılım Şartları");

                    //                                    _pC->addWidget(std::move(anchor));
                    //                                }

                    {
                        auto _pC = popContainer->addWidget (cpp14::make_unique<WContainerWidget>());
                        _pC->addStyleClass ("headerItem");
                        _pC->addWidget (cpp14::make_unique<WText>("Başvuru"));
                        _pC->clicked().connect([=](){
                            this->initBasvuru();
                        });
                    }

                    {
                        auto _pC = popContainer->addWidget (cpp14::make_unique<WContainerWidget>());
                        _pC->addStyleClass ("headerItem");
                        _pC->addWidget (cpp14::make_unique<WText>("Kitaplar"));
                        _pC->clicked().connect([=](){
                            this->Kitaplar();
                        });
                    }
                }
                text->decorationStyle().setCursor(Cursor::PointingHand);
            }



        }

    }










}

void MainApplication::initMain()
{

    mMainContainer_->clear();
    auto aContainer = mMainContainer_->addWidget(cpp14::make_unique<WContainerWidget>());
    aContainer->setContentAlignment(AlignmentFlag::Center);
    aContainer->setWidth(WLength("100%"));

    auto afisContainer = aContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    afisContainer->setMargin(50,Side::Top);
    afisContainer->setAttributeValue(Style::style,Style::background::url("afis.png")+Style::background::position::center_center+Style::background::size::contain+Style::background::repeat::norepeat);
    afisContainer->setWidth(WLength("100%"));
    afisContainer->setHeight(500);




}

void MainApplication::initHakkinda()
{

    mMainContainer_->clear();
    mMainContainer_->setContentAlignment(AlignmentFlag::Center);
    auto container = mMainContainer_->addWidget(cpp14::make_unique<WContainerWidget>());
    container->setMaximumSize(1280,WLength::Auto);
    container->setAttributeValue(Style::style,Style::background::color::rgba(25,25,25,0.85));

    container->setPadding(50,Side::Top|Side::Bottom);


    auto titleText = container->addWidget(cpp14::make_unique<WText>("<h3>HAKKINDA</h3>"));
    titleText->setMargin(75,Side::Top);

    titleText->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue));


    auto text = container->addWidget(cpp14::make_unique<WText>("<h4><p align=\"justify\">Serik ilçesi genelindeki yaşı ve eğitim düzeyi fark etmeksizin tüm vatandaşlara "
                                                                    "kitap okuma alışkanlığı kazandırmak ve okunan kitap sayısını arttırmaktır.</p>"
                                                                    "<p align=\"justify\">Aile bağlarının güçlenmesi, genç ve yetişkin fark etmeksizin aynı kitap üzerinde "
                                                                    "fikir alışverişi yapılabilmesi, ailenin sohbet bağlamının kültür ve edebiyat üzerine "
                                                                    "olarak dönüştürülmesi, sosyal medya ve televizyon gibi mavi ekranlardan uzakta vakit "
                                                                    "geçirilmesine yardımcı ve teşvik edici olması amaçlanmaktadır.</p></h4>"));
    text->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue));
    text->setTextAlignment(AlignmentFlag::Justify);
    text->setMargin(40,Side::Top);
    text->setMargin(15,Side::Left|Side::Right);

}

void MainApplication::baskanmesaji()
{

    mMainContainer_->clear();
    mMainContainer_->setContentAlignment(AlignmentFlag::Center);
    auto container = mMainContainer_->addWidget(cpp14::make_unique<WContainerWidget>());
    container->setMaximumSize(1280,WLength::Auto);
    container->setAttributeValue(Style::style,Style::background::color::rgba(75,75,75,0.9));
    container->setZIndex(999);

    container->setPadding(50,Side::Top|Side::Bottom);

    //    container->addStyleClass(Bootstrap::Grid::container_fluid);

    auto rContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
    rContainer->addStyleClass(Bootstrap::Grid::row);

    auto fotoContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    fotoContainer->addStyleClass(Bootstrap::Grid::Large::col_lg_4+
                                 Bootstrap::Grid::Medium::col_md_4+
                                 Bootstrap::Grid::Small::col_sm_12+
                                 Bootstrap::Grid::ExtraSmall::col_xs_12);

    auto fContainer = fotoContainer->addWidget(cpp14::make_unique<WContainerWidget>());


    fContainer->setAttributeValue(Style::style,Style::background::url("baskan1.png")+
                                  Style::background::size::contain+
                                  Style::background::repeat::norepeat+
                                  Style::background::position::center_center);
    fContainer->setHeight(450);



    auto textContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    textContainer->addStyleClass(Bootstrap::Grid::Large::col_lg_8+
                                 Bootstrap::Grid::Medium::col_md_8+
                                 Bootstrap::Grid::Small::col_sm_12+
                                 Bootstrap::Grid::ExtraSmall::col_xs_12);


    auto titleText = textContainer->addWidget(cpp14::make_unique<WText>("<h3>Başkanın Mesajı</h3>"));
    titleText->setMargin(75,Side::Top);
    titleText->setTextAlignment(AlignmentFlag::Left);

    titleText->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue));


    auto text = textContainer->addWidget(cpp14::make_unique<WText>("<h4><p align=\"justify\">Medeniyetin gelişmesindeki en temel unsurlardan biri, hiç kuşkusuz bilgi ve bilginin "
                                                                "paylaşılmasıdır. Bilgiyi yaymak, hemşehrilerimizin sosyal ve kültürel "
                                                                "hayatlarına katkı sağlamak amacıyla eğitimin yaşı yoktur diyerek kültürel faaliyetlere "
                                                                "destek veriyoruz. Nitelikli okumanın ve okutmanın önemini biliyor, her zeminde bunu dile getiriyoruz.</p>"
                                                                "<p align=\"justify\">Okumak sonsuz ve kültürel zenginlikler ile dolu bir dünyada uzun bir yolculuğa çıkmak gibidir. "
                                                                "Biz de bu uzun yola sizlerle birlikte çıkmak ve bu yolda bizi yalnız bırakmayan hemşehrilerimizi "
                                                                "ödüllendirmek istedik. Okuma yarışmasında sizlere vereceğimiz küçük ödüllerden öte, okumanın verdiği "
                                                                "hazzın ve katacağı vizyonun en büyük ödül olduğunun farkındayız.</p>"
                                                                "<p align=\"justify\">Serik Belediyesi olarak; yaşadığımız coğrafyanın değerlerini geleceğe taşıyacak "
                                                                "olan siz değerli hemşehrilerimizi bu okuma seferberliğine davet ediyoruz.</p></h4>"));
    text->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue));
    text->setTextAlignment(AlignmentFlag::Justify);
    text->setMargin(40,Side::Top);
    text->setMargin(10,Side::Left|Side::Right);


}

void MainApplication::Kitaplar()
{
    mMainContainer_->clear();
    mMainContainer_->setContentAlignment(AlignmentFlag::Center);
    auto container = mMainContainer_->addWidget(cpp14::make_unique<WContainerWidget>());
    container->setMaximumSize(1280,WLength::Auto);
    container->setAttributeValue(Style::style,Style::background::color::rgba(75,75,75,0.9));
    container->setZIndex(999);

    container->setPadding(50,Side::Top|Side::Bottom);

    auto rContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
    rContainer->addStyleClass(Bootstrap::Grid::row);


    {
        auto kcontainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        kcontainer->addStyleClass(Bootstrap::Grid::Large::col_lg_3+Bootstrap::Grid::Medium::col_md_3+Bootstrap::Grid::Small::col_sm_4+Bootstrap::Grid::ExtraSmall::col_xs_6);

        auto vLayout = kcontainer->setLayout(cpp14::make_unique<WVBoxLayout>());



        auto kapakContainer = vLayout->addWidget(cpp14::make_unique<WContainerWidget>());
        kapakContainer->setHeight(200);
        kapakContainer->setAttributeValue(Style::style,Style::background::url("1.dc197a9a.jpg")+
                                          Style::background::size::contain+
                                          Style::background::position::center_center+
                                          Style::background::repeat::norepeat);


        auto textContainer = vLayout->addWidget(cpp14::make_unique<WContainerWidget>());

        textContainer->addWidget(cpp14::make_unique<WText>("<h4><p align=\"center\"><b>Deli Tarla</b></p></h4>"
                                                           "<h5><p align=\"center\">ŞERMİN YAŞAR</p></h5>"));
        textContainer->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue));
    }


    {
        auto kcontainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        kcontainer->addStyleClass(Bootstrap::Grid::Large::col_lg_3+Bootstrap::Grid::Medium::col_md_3+Bootstrap::Grid::Small::col_sm_4+Bootstrap::Grid::ExtraSmall::col_xs_6);

        auto vLayout = kcontainer->setLayout(cpp14::make_unique<WVBoxLayout>());



        auto kapakContainer = vLayout->addWidget(cpp14::make_unique<WContainerWidget>());
        kapakContainer->setHeight(200);
        kapakContainer->setAttributeValue(Style::style,Style::background::url("2.3ca6bb44.jpg")+
                                          Style::background::size::contain+
                                          Style::background::position::center_center+
                                          Style::background::repeat::norepeat);


        auto textContainer = vLayout->addWidget(cpp14::make_unique<WContainerWidget>());

        textContainer->addWidget(cpp14::make_unique<WText>("<h4><p align=\"center\"><b>Fatih-i Harbiye</b></p></h4>"
                                                           "<h5><p align=\"center\">PEYAMİ SAFA</p></h5>"));
        textContainer->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue));
    }

    {
        auto kcontainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        kcontainer->addStyleClass(Bootstrap::Grid::Large::col_lg_3+Bootstrap::Grid::Medium::col_md_3+Bootstrap::Grid::Small::col_sm_4+Bootstrap::Grid::ExtraSmall::col_xs_6);

        auto vLayout = kcontainer->setLayout(cpp14::make_unique<WVBoxLayout>());



        auto kapakContainer = vLayout->addWidget(cpp14::make_unique<WContainerWidget>());
        kapakContainer->setHeight(200);
        kapakContainer->setAttributeValue(Style::style,Style::background::url("3.a433b89d.jpg")+
                                          Style::background::size::contain+
                                          Style::background::position::center_center+
                                          Style::background::repeat::norepeat);


        auto textContainer = vLayout->addWidget(cpp14::make_unique<WContainerWidget>());

        textContainer->addWidget(cpp14::make_unique<WText>("<h4><p align=\"center\"><b>Mücella</b></p></h4>"
                                                           "<h5><p align=\"center\">NAZAN BEKİROĞLU</p></h5>"));
        textContainer->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue));
    }

    {
        auto kcontainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        kcontainer->addStyleClass(Bootstrap::Grid::Large::col_lg_3+Bootstrap::Grid::Medium::col_md_3+Bootstrap::Grid::Small::col_sm_4+Bootstrap::Grid::ExtraSmall::col_xs_6);

        auto vLayout = kcontainer->setLayout(cpp14::make_unique<WVBoxLayout>());



        auto kapakContainer = vLayout->addWidget(cpp14::make_unique<WContainerWidget>());
        kapakContainer->setHeight(200);
        kapakContainer->setAttributeValue(Style::style,Style::background::url("4.c6d96be5.jpg")+
                                          Style::background::size::contain+
                                          Style::background::position::center_center+
                                          Style::background::repeat::norepeat);


        auto textContainer = vLayout->addWidget(cpp14::make_unique<WContainerWidget>());

        textContainer->addWidget(cpp14::make_unique<WText>("<h4><p align=\"center\"><b>101 Deyim 101 Öykü</b></p></h4>"
                                                           "<h5><p align=\"center\">SÜLEYMAN BULUT</p></h5>"));
        textContainer->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue));
    }



    {
        auto kcontainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        kcontainer->addStyleClass(Bootstrap::Grid::Large::col_lg_3+Bootstrap::Grid::Medium::col_md_3+Bootstrap::Grid::Small::col_sm_4+Bootstrap::Grid::ExtraSmall::col_xs_6);

        auto vLayout = kcontainer->setLayout(cpp14::make_unique<WVBoxLayout>());



        auto kapakContainer = vLayout->addWidget(cpp14::make_unique<WContainerWidget>());
        kapakContainer->setHeight(200);
        kapakContainer->setAttributeValue(Style::style,Style::background::url("9.c9233dac.jpg")+
                                          Style::background::size::contain+
                                          Style::background::position::center_center+
                                          Style::background::repeat::norepeat);


        auto textContainer = vLayout->addWidget(cpp14::make_unique<WContainerWidget>());

        textContainer->addWidget(cpp14::make_unique<WText>("<h4><p align=\"center\"><b>Acımak</b></p></h4>"
                                                           "<h5><p align=\"center\">REŞAT NURİ GÜNTEKİN</p></h5>"));
        textContainer->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue));
    }
}

void MainApplication::initBasvuru()
{


    auto container_ = root()->addWidget(cpp14::make_unique<WContainerWidget>());
    container_->setPositionScheme(PositionScheme::Fixed);
    container_->setWidth(WLength("100%"));
    container_->setHeight(WLength("100%"));
    container_->setAttributeValue(Style::style,Style::background::color::rgba(25,25,25));
    container_->setZIndex(500);
    container_->setOffsets(0,Side::Top|Side::Left);
    container_->setContentAlignment(AlignmentFlag::Center);
    container_->setId("container_");

    auto filContainer = container_->addWidget(cpp14::make_unique<WContainerWidget>());
    filContainer->addStyleClass("basvuruStyle");
    filContainer->setContentAlignment(AlignmentFlag::Center);
    //        filContainer->setScrollVisibilityEnabled(true);
    filContainer->setOverflow(Overflow::Scroll,Orientation::Vertical);
    filContainer->setAttributeValue(Style::style,Style::background::color::rgba(50,125,200,0.75));



    auto container = filContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    //        container->setMaximumSize(1280,WLength::Auto);
    container->setZIndex(999);

    //    container->setPadding(50,Side::Top|Side::Bottom);





    auto tempcontainer = container->addWidget(cpp14::make_unique<WContainerWidget>());




    auto rContainer = tempcontainer->addWidget(cpp14::make_unique<WContainerWidget>());
    rContainer->addStyleClass(Bootstrap::Grid::row);
    rContainer->setPadding(25,Side::Bottom);





    auto baslikContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    baslikContainer->setMargin(20,Side::Top);
    baslikContainer->setMargin(25,Side::Bottom);
    baslikContainer->addStyleClass(Bootstrap::Grid::col_full_12);
    auto baslikText = baslikContainer->addWidget(cpp14::make_unique<WText>("<h3>BAŞVURU</h3>"));
    baslikText->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue));


    const auto styleStr1 = Bootstrap::Grid::Large::col_lg_5+Bootstrap::Grid::Medium::col_md_5+Bootstrap::Grid::Small::col_sm_5+Bootstrap::Grid::ExtraSmall::col_xs_5;
    const auto styleStr2 = Bootstrap::Grid::Large::col_lg_7+Bootstrap::Grid::Medium::col_md_7+Bootstrap::Grid::Small::col_sm_7+Bootstrap::Grid::ExtraSmall::col_xs_7;

    auto adtextContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    adtextContainer->setContentAlignment(AlignmentFlag::Right);
    auto adText = adtextContainer->addWidget(cpp14::make_unique<WText>("<b>Ad Soyad</b>"));
    adtextContainer->addStyleClass(styleStr1);
    adtextContainer->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue));
    adtextContainer->setHeight(40);

    auto adlineContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    adlineContainer->setContentAlignment(AlignmentFlag::Left);
    auto adlineEdit = adlineContainer->addWidget(cpp14::make_unique<WLineEdit>());
    adlineEdit->setPlaceholderText("Ad & Soyad Giriniz (Zorunlu)");
    adlineEdit->setMaximumSize(WLength(445),WLength::Auto);
    adlineContainer->addStyleClass(styleStr2);
    adlineContainer->setHeight(40);




    auto tctextContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    tctextContainer->setContentAlignment(AlignmentFlag::Right);
    tctextContainer->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue));
    auto tcText = tctextContainer->addWidget(cpp14::make_unique<WText>("<b>TCNO</b>"));
    tctextContainer->addStyleClass(styleStr1);
    tctextContainer->setHeight(40);

    auto tclineContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    tclineContainer->setContentAlignment(AlignmentFlag::Left);
    tclineContainer->addStyleClass(styleStr2);
    auto tclineEdit = tclineContainer->addWidget(cpp14::make_unique<WLineEdit>());
    tclineEdit->setPlaceholderText("TCNO Giriniz (Zorunlu)");
    tclineEdit->setMaximumSize(WLength(445),WLength::Auto);
    tclineContainer->setHeight(40);





    auto ceptextContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    ceptextContainer->setContentAlignment(AlignmentFlag::Right);
    ceptextContainer->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue));
    auto cepText = ceptextContainer->addWidget(cpp14::make_unique<WText>("<b>Cep Telefonu</b>"));
    ceptextContainer->addStyleClass(styleStr1);
    ceptextContainer->setHeight(40);

    auto ceplineContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    ceplineContainer->setContentAlignment(AlignmentFlag::Left);
    ceplineContainer->addStyleClass(styleStr2);
    auto ceplineEdit = ceplineContainer->addWidget(cpp14::make_unique<WLineEdit>());
    ceplineEdit->setPlaceholderText("Cep Telefonu Giriniz (Zorunlu)");
    ceplineEdit->setMaximumSize(WLength(445),WLength::Auto);
    ceplineContainer->setHeight(40);




    auto emailtextContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    emailtextContainer->setContentAlignment(AlignmentFlag::Right);
    emailtextContainer->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue));
    auto emailText = emailtextContainer->addWidget(cpp14::make_unique<WText>("<b>e-Mail</b>"));
    emailtextContainer->addStyleClass(styleStr1);
    emailtextContainer->setHeight(40);

    auto emaillineContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    emaillineContainer->setContentAlignment(AlignmentFlag::Left);
    emaillineContainer->addStyleClass(styleStr2);
    auto emaillineEdit = emaillineContainer->addWidget(cpp14::make_unique<WLineEdit>());
    emaillineEdit->setPlaceholderText("e-Mail Adresi Giriniz");
    emaillineEdit->setMaximumSize(WLength(445),WLength::Auto);
    emaillineContainer->setHeight(40);





    auto cinsiyettextContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    cinsiyettextContainer->setContentAlignment(AlignmentFlag::Right);
    cinsiyettextContainer->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue));
    auto cinsiyetText = cinsiyettextContainer->addWidget(cpp14::make_unique<WText>("<b>Cinsiyet</b>"));
    cinsiyettextContainer->addStyleClass(styleStr1);
    cinsiyettextContainer->setHeight(40);

    auto cinsiyetlineContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    cinsiyetlineContainer->setContentAlignment(AlignmentFlag::Left);
    cinsiyetlineContainer->addStyleClass(styleStr2);
    auto cinsiyetComboBox = cinsiyetlineContainer->addWidget(cpp14::make_unique<WComboBox>());
    cinsiyetComboBox->setMaximumSize(WLength(445),WLength::Auto);
    cinsiyetComboBox->addItem("Seçiniz");
    cinsiyetComboBox->addItem("Kadın");
    cinsiyetComboBox->addItem("Erkek");
    cinsiyetlineContainer->setHeight(40);




    auto yasTexttContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    yasTexttContainer->setContentAlignment(AlignmentFlag::Right);
    yasTexttContainer->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue));
    auto yasText = yasTexttContainer->addWidget(cpp14::make_unique<WText>("<b>Yaş Aralığı</b>"));
    yasTexttContainer->addStyleClass(styleStr1);
    yasTexttContainer->setHeight(40);

    auto yaslineContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    yaslineContainer->setContentAlignment(AlignmentFlag::Left);
    yaslineContainer->addStyleClass(styleStr2);
    auto yasComboBox = yaslineContainer->addWidget(cpp14::make_unique<WComboBox>());
    yasComboBox->setMaximumSize(WLength(445),WLength::Auto);
    yasComboBox->addItem("Seçiniz");
    yasComboBox->addItem("10-14");
    yasComboBox->addItem("15-18");
    yasComboBox->addItem("19-25");
    yasComboBox->addItem("26-35");
    yasComboBox->addItem("36-50");
    yasComboBox->addItem("50 Üzeri");
    yaslineContainer->setHeight(40);






    auto egitimTexttContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    egitimTexttContainer->setContentAlignment(AlignmentFlag::Right);
    egitimTexttContainer->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue));
    auto egitimText = egitimTexttContainer->addWidget(cpp14::make_unique<WText>("<b>Öğrenim Durumu</b>"));
    egitimTexttContainer->addStyleClass(styleStr1);
    egitimTexttContainer->setHeight(40);

    auto egitimlineContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    egitimlineContainer->setContentAlignment(AlignmentFlag::Left);
    egitimlineContainer->addStyleClass(styleStr2);
    auto egitimComboBox = egitimlineContainer->addWidget(cpp14::make_unique<WComboBox>());
    egitimComboBox->setMaximumSize(WLength(445),WLength::Auto);
    egitimComboBox->addItem("Seçiniz");
    egitimComboBox->addItem("İlkokul");
    egitimComboBox->addItem("Ortaokul");
    egitimComboBox->addItem("Lise");
    egitimComboBox->addItem("Önlisans");
    egitimComboBox->addItem("Lisans");
    egitimComboBox->addItem("Yüksek Lisans");
    egitimComboBox->addItem("Doktora");
    egitimlineContainer->setHeight(40);




    auto ailedenTextContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    ailedenTextContainer->setContentAlignment(AlignmentFlag::Right);
    ailedenTextContainer->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue));
    auto ailedenText = ailedenTextContainer->addWidget(cpp14::make_unique<WText>("<b>Ailenizden Katılan Kişi Sayısı</b>"));
    ailedenTextContainer->addStyleClass(styleStr1);
    ailedenTextContainer->setHeight(40);

    auto ailedenlineContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    ailedenlineContainer->setContentAlignment(AlignmentFlag::Left);
    ailedenlineContainer->addStyleClass(styleStr2);
    auto ailedenSpinBox = ailedenlineContainer->addWidget(cpp14::make_unique<WSpinBox>());
    ailedenSpinBox->setMaximumSize(WLength(445),WLength::Auto);
    ailedenSpinBox->setRange(0,10);
    ailedenlineContainer->setHeight(40);





    auto arkadasTextContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    arkadasTextContainer->setContentAlignment(AlignmentFlag::Right);
    arkadasTextContainer->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue));
    auto arkadasText = arkadasTextContainer->addWidget(cpp14::make_unique<WText>("<b>Arkadaşlarınızdan Katılan Kişi Sayısı</b>"));
    arkadasTextContainer->addStyleClass(styleStr1);
    arkadasTextContainer->setHeight(40);

    auto arkadaslineContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    arkadaslineContainer->setContentAlignment(AlignmentFlag::Left);
    arkadaslineContainer->addStyleClass(styleStr2);
    auto arkadasSpinBox = arkadaslineContainer->addWidget(cpp14::make_unique<WSpinBox>());
    arkadasSpinBox->setMaximumSize(WLength(445),WLength::Auto);
    arkadasSpinBox->setRange(0,50);
    arkadaslineContainer->setHeight(40);




    auto yarismaNerdenContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    yarismaNerdenContainer->setContentAlignment(AlignmentFlag::Right);
    yarismaNerdenContainer->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue));
    auto yarismaText = yarismaNerdenContainer->addWidget(cpp14::make_unique<WText>("<b>Nerden Duydunuz</b>"));
    yarismaNerdenContainer->addStyleClass(styleStr1);
    yarismaNerdenContainer->setHeight(40);

    auto yarismaTextlineContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    yarismaTextlineContainer->setContentAlignment(AlignmentFlag::Left);
    yarismaTextlineContainer->addStyleClass(styleStr2);
    auto yarismaNerdenComboBox = yarismaTextlineContainer->addWidget(cpp14::make_unique<WComboBox>());
    yarismaNerdenComboBox->setMaximumSize(WLength(445),WLength::Auto);
    yarismaNerdenComboBox->addItem("Seçiniz");
    yarismaNerdenComboBox->addItem("Sosyal Medya");
    yarismaNerdenComboBox->addItem("Okul");
    yarismaNerdenComboBox->addItem("Afiş");
    yarismaNerdenComboBox->addItem("Arkadaş");
    yarismaTextlineContainer->setHeight(40);





    auto katilmaSekliContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    katilmaSekliContainer->setContentAlignment(AlignmentFlag::Right);
    katilmaSekliContainer->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue));
    auto katilmaSekliText = katilmaSekliContainer->addWidget(cpp14::make_unique<WText>("<b>Katılma Şekli</b>"));
    katilmaSekliContainer->addStyleClass(styleStr1);
    katilmaSekliContainer->setHeight(40);

    auto katilmaSeklilineContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    katilmaSeklilineContainer->setContentAlignment(AlignmentFlag::Left);
    katilmaSeklilineContainer->addStyleClass(styleStr2);
    auto katilmaSekliComboBox = katilmaSeklilineContainer->addWidget(cpp14::make_unique<WComboBox>());
    katilmaSekliComboBox->setMaximumSize(WLength(445),WLength::Auto);
    katilmaSekliComboBox->addItem("Seçiniz");
    katilmaSekliComboBox->addItem("Sınav Çevrim içi Yapılırsa Katılırım");
    katilmaSekliComboBox->addItem("Sınav Yüzyüze Yapılırsa Katılırım");
    katilmaSekliComboBox->addItem("Sınava İki Türlü de Katılabilirim");
    katilmaSeklilineContainer->setHeight(40);




    auto adrestextContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    adrestextContainer->setContentAlignment(AlignmentFlag::Right);
    adrestextContainer->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue));
    auto adresText = adrestextContainer->addWidget(cpp14::make_unique<WText>("<b>İkametgah Adresiniz</b>"));
    adrestextContainer->addStyleClass(styleStr1);

    auto adreslineContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    adreslineContainer->setContentAlignment(AlignmentFlag::Left);
    adreslineContainer->addStyleClass(styleStr2);
    auto adreslineEdit = adreslineContainer->addWidget(cpp14::make_unique<WLineEdit>());
    adreslineEdit->setPlaceholderText("İkametgah Adresi Giriniz");
    adreslineEdit->setMaximumSize(WLength(445),WLength::Auto);


    auto onayContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    onayContainer->setContentAlignment(AlignmentFlag::Right);
    onayContainer->addStyleClass(styleStr1);
    auto vlayoutCheckBox = onayContainer->setLayout(cpp14::make_unique<WVBoxLayout>());
    vlayoutCheckBox->addStretch(1);
    auto onayCheckBox = vlayoutCheckBox->addWidget(cpp14::make_unique<WCheckBox>(),0,AlignmentFlag::Right);
    vlayoutCheckBox->addStretch(1);

    auto sartnameContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    sartnameContainer->addStyleClass(styleStr2);
    auto vLayout = sartnameContainer->setLayout(cpp14::make_unique<WVBoxLayout>());
    auto sartnametext = vLayout->addWidget(cpp14::make_unique<WText>("Yarışma Şartnamesini Okudum, Kabul Ediyorum."),0,AlignmentFlag::Left);
    sartnametext->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue)+Style::font::size::s16px);
    sartnametext->decorationStyle().setCursor(Cursor::PointingHand);
    sartnametext->clicked().connect([=](){
        sartnametext->doJavaScript("window.open(\"http://www.serikokuyor.com/serikokuyorsartname.pdf\", '_blank').focus();");
    });



    auto warnContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    warnContainer->addStyleClass(Bootstrap::Grid::col_full_12);
    auto warnText = warnContainer->addWidget(cpp14::make_unique<WText>("<h5>Yarışmaya Katılabilmeniz için İkametgahınız Serik İlçe Sınırları İçinde Olmalıdır.</h5>"));
    warnText->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue));

    auto warnContainer2 = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    warnContainer2->addStyleClass(Bootstrap::Grid::col_full_12);
    auto warnText2 = warnContainer2->addWidget(cpp14::make_unique<WText>("<h5>Öğrenci Belgesi İbraz Edenlerden İkametgah Şartı Aranmayacaktır.</h5>"));
    warnText2->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue));

    auto basvurBtnContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());

    auto iptalBtnContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    iptalBtnContainer->setMargin(25,Side::Bottom);
    iptalBtnContainer->addStyleClass(Bootstrap::Grid::col_full_12);
    auto iptalBtn = iptalBtnContainer->addWidget(cpp14::make_unique<WPushButton>("İptal"));
    iptalBtn->addStyleClass(Bootstrap::Button::Warning);
    iptalBtn->clicked().connect([=](){
        root()->removeWidget(container_);
    });



    basvurBtnContainer->setMargin(25,Side::Bottom);
    basvurBtnContainer->addStyleClass(Bootstrap::Grid::col_full_12);
    auto basvurBtn = basvurBtnContainer->addWidget(cpp14::make_unique<WPushButton>("Başvuruyu Tamamla"));
    basvurBtn->addStyleClass(Bootstrap::Button::Primary);





    basvurBtn->clicked().connect([=](){

        if( !onayCheckBox->isChecked() ){
            mMainContainer->warnDialog("Lütfen Önce Şartnameyi Kabul Ediniz");
            return;
        }

        if( tclineEdit->text().toUTF8().size() == 11 ){
            auto filter = document{};

            try {
                filter.append(kvp("tcno",tclineEdit->text().toUTF8()));
            }  catch (bsoncxx::exception &e) {
                mMainContainer_->warnDialog(std::string("tc no kontrol Hata: ")+e.what());
                return;
            }

            try {
                auto count = this->db.collection("basvuru").count_documents(filter.view());

                if( count != 0 ){
                    this->mMainContainer_->warnDialog("Bu TCNO Kayıtlı");
                    return;
                }

            }  catch (mongocxx::exception &e) {
                mMainContainer_->warnDialog(std::string("Başvuru Esnasında Bir Hata Oluştu: ")+e.what());
            }

        }


        if( ceplineEdit->text().toUTF8().size() != 11 ){
            this->mMainContainer_->warnDialog("Cep Telefonu Hatalı");
            return;
        }


        if( adreslineEdit->text().toUTF8().size() <= 10 ){
            this->mMainContainer_->warnDialog("Adres Bilgisi Yetersiz");
            return;
        }







        auto tcItem = document{};

        if( adlineEdit->text().toUTF8().size() <= 5 ){
            mMainContainer_->warnDialog("Ad&Soyad da Hata Var");
            return;

        }else{
            try {
                tcItem.append(kvp("adsoyad",adlineEdit->text().toUTF8()));
            }  catch (bsoncxx::exception &e) {
                mMainContainer_->warnDialog(std::string("ad soyad Hata: ")+e.what());
                return;
            }
        }



        if( tclineEdit->text().toUTF8().size() != 11 ){
            mMainContainer_->warnDialog("TCNO 11 Haneli Olmak Zorunda");
            return;
        }else{
            try {
                tcItem.append(kvp("tcno",tclineEdit->text().toUTF8()));
            }  catch (bsoncxx::exception &e) {
                mMainContainer_->warnDialog(std::string("TCNO Hata: ")+e.what());
                return;
            }
        }


        if( ceplineEdit->text().toUTF8().size() != 11 ){
            mMainContainer_->warnDialog("Cep Telefonu 11 Haneli Olmak Zorunda. Başında 0 Kullanınız");
            return;
        }else{
            try {
                tcItem.append(kvp("cep",ceplineEdit->text().toUTF8()));
            }  catch (bsoncxx::exception &e) {
                mMainContainer_->warnDialog(std::string("Cep Telefonu Hata: ")+e.what());
            }
        }


        try {
            tcItem.append(kvp("mail",emaillineEdit->text().toUTF8()));
        }  catch (bsoncxx::exception &e) {
            mMainContainer_->warnDialog(std::string("e-mail Hata: ")+e.what());
            return;
        }

        try {
            tcItem.append(kvp("adres",adreslineEdit->text().toUTF8()));
        }  catch (bsoncxx::exception &e) {
            mMainContainer_->warnDialog(std::string("adres Hata: ")+e.what());
            return;
        }



        if( cinsiyetComboBox->currentText().toUTF8() == "Seçiniz" ){
            mMainContainer_->warnDialog("Cinsiyet Seçmediniz");
            return;
        }else{
            try {
                tcItem.append(kvp("cinsiyet",cinsiyetComboBox->currentText().toUTF8()));
            }  catch (bsoncxx::exception &e) {
                mMainContainer_->warnDialog(std::string("Cinsiyet Hata: ")+e.what());
                return;
            }
        }

        if( egitimComboBox->currentText().toUTF8() == "Seçiniz" ){
            mMainContainer_->warnDialog("Eğitim Durumunu Seçmediniz");
            return;
        }else{
            try {
                tcItem.append(kvp("egitim",egitimComboBox->currentText().toUTF8()));
            }  catch (bsoncxx::exception &e) {
                mMainContainer_->warnDialog(std::string("Eğitim Hata: ")+e.what());
                return;
            }
        }




        if( yasComboBox->currentText().toUTF8() == "Seçiniz" ){
            mMainContainer_->warnDialog("Yaş Aralığı Seçmediniz");
            return;
        }else{
            try {
                tcItem.append(kvp("yasaralik",yasComboBox->currentText().toUTF8()));
            }  catch (bsoncxx::exception &e) {
                mMainContainer_->warnDialog(std::string("Yaş Aralığı Hata: ")+e.what());
                return;
            }
        }


        try {
            tcItem.append(kvp("aileKac",ailedenSpinBox->value()));
        }  catch (bsoncxx::exception &e) {
            mMainContainer_->warnDialog(std::string("Aile Kaç Kişi Hata: ")+e.what());
            return;
        }

        try {
            tcItem.append(kvp("arkadasKac",arkadasSpinBox->value()));
        }  catch (bsoncxx::exception &e) {
            mMainContainer_->warnDialog(std::string("Arkadaş Kaç Kişi Hata: ")+e.what());
            return;
        }

        if( yarismaNerdenComboBox->currentText().toUTF8() == "Seçiniz" ){
            mMainContainer_->warnDialog("Nerden Duyduğunuzu Seçmediniz");
            return;
        }else{
            try {
                tcItem.append(kvp("nerdenduydunuz",yarismaNerdenComboBox->currentText().toUTF8()));
            }  catch (bsoncxx::exception &e) {
                mMainContainer_->warnDialog(std::string("Nerden Duydunuz Hata: ")+e.what());
                return;
            }
        }


        if( katilmaSekliComboBox->currentText().toUTF8() == "Seçiniz" ){
            mMainContainer_->warnDialog("Katılma Durumunu Seçmediniz");
            return;
        }else{
            try {
                tcItem.append(kvp("nasilKatilirim",katilmaSekliComboBox->currentText().toUTF8()));
            }  catch (bsoncxx::exception &e) {
                mMainContainer_->warnDialog(std::string("Katılım Şekli Hata: ")+e.what());
                return;
            }
        }






        try {
            auto ins = this->db.collection("basvuru").insert_one(tcItem.view());


            if( ins.value().result().inserted_count() ){
                mMainContainer_->informDialog("Başvurunuz Değerlendirmeye Alındı.");
//                    this->initMain();
                root()->removeWidget(container_);
            }else{
                mMainContainer_->warnDialog("Başvurunuz Alınamadı!");
            }

        }  catch (mongocxx::exception &e) {
            mMainContainer_->warnDialog(std::string("Başvuru Esnasında Bir Hata Oluştu: ")+e.what());
        }


    });




}











