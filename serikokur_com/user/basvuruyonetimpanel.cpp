#include "basvuruyonetimpanel.h"
#include "root/css.h"


BasvuruYonetimPanel::BasvuruYonetimPanel(DB *_mDB)
    :ContainerWidget("Başvurular"),
      BasvuruManager(_mDB)
{
    this->setLimit(24);
    this->UpdateList();


    this->initController();


}

void BasvuruYonetimPanel::initController()
{

    this->Header()->setMargin(15,Side::Top|Side::Bottom);

    {
        auto container_ = this->Header()->addWidget(cpp14::make_unique<WContainerWidget>());
        container_->addStyleClass(Bootstrap::Grid::col_full_12);
        container_->setMargin(15,Side::Bottom);

        auto hlayout = container_->setLayout(cpp14::make_unique<WHBoxLayout>());

        auto listBtn = hlayout->addWidget(cpp14::make_unique<WPushButton>("Listele"));
        listBtn->addStyleClass(Bootstrap::Button::Primary);

        listBtn->clicked().connect([=](){
            this->UpdateList();
        });


        int total = this->totalCount();

        auto totaltext = hlayout->addWidget(cpp14::make_unique<WText>(WString("<h5>Toplam Başvuru: {1}</h5>").arg(total)));
        totaltext->addStyleClass(Bootstrap::Label::info);
        totaltext->addStyleClass(CSSStyle::Radius::radius3px+CSSStyle::Shadows::shadow8px);

        int onayli = this->countItem(BasvuruItem().setOnay(true));

        auto onaylitext = hlayout->addWidget(cpp14::make_unique<WText>(WString("<h5>Onaylı: {1}</h5>").arg(onayli)));
        onaylitext->addStyleClass(Bootstrap::Label::Success);
        onaylitext->addStyleClass(CSSStyle::Radius::radius3px+CSSStyle::Shadows::shadow8px);

        int onaysiz = this->countItem(BasvuruItem().setOnay(false));

        auto onaysiztext = hlayout->addWidget(cpp14::make_unique<WText>(WString("<h5>Onaysız: {1}</h5>").arg(onaysiz)));
        onaysiztext->addStyleClass(Bootstrap::Label::Danger);
        onaysiztext->addStyleClass(CSSStyle::Radius::radius3px+CSSStyle::Shadows::shadow8px);

        auto istatisBtn = hlayout->addWidget(cpp14::make_unique<WPushButton>("İstatistik"));
        istatisBtn->addStyleClass(Bootstrap::Button::Primary);

        istatisBtn->clicked().connect([=](){
            this->Content()->clear();
            this->Content()->addWidget(cpp14::make_unique<IstatistikWidget>(this->getDB()))->addStyleClass(Bootstrap::Grid::col_full_12);
        });

    }







    this->Footer()->setMargin(50,Side::Top|Side::Bottom);

    {
        auto container = Footer()->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_4+
                                 Bootstrap::Grid::Medium::col_md_3+
                                 Bootstrap::Grid::Small::col_sm_2+
                                 Bootstrap::Grid::ExtraSmall::col_xs_1+Bootstrap::Grid::Hidden::hidden_xs);
    }

    auto backcontainer = Footer()->addWidget(cpp14::make_unique<WContainerWidget>());
    backcontainer->addStyleClass(Bootstrap::Grid::Large::col_lg_1+
                                 Bootstrap::Grid::Medium::col_md_2+
                                 Bootstrap::Grid::Small::col_sm_3+
                                 Bootstrap::Grid::ExtraSmall::col_xs_4);
    backcontainer->addWidget(cpp14::make_unique<WText>("Geri"));
    backcontainer->setContentAlignment(AlignmentFlag::Center);
    backcontainer->addStyleClass(CSS::Button::GrayGrad);



    auto pageContainer = Footer()->addWidget(cpp14::make_unique<WContainerWidget>());
    pageContainer->addStyleClass(Bootstrap::Grid::Large::col_lg_2+
                                 Bootstrap::Grid::Medium::col_md_2+
                                 Bootstrap::Grid::Small::col_sm_2+
                                 Bootstrap::Grid::ExtraSmall::col_xs_2);
    auto pageText = pageContainer->addWidget(cpp14::make_unique<WText>("<p>"+std::to_string(this->skip())+"-"+std::to_string(this->skip()+this->limit())+"</p><p>" + std::to_string(this->totalCount())+"</p>"));
    pageText->setAttributeValue(Style::style,Style::font::weight::bold);


    auto nextcontainer = Footer()->addWidget(cpp14::make_unique<WContainerWidget>());
    nextcontainer->addStyleClass(Bootstrap::Grid::Large::col_lg_1+
                                 Bootstrap::Grid::Medium::col_md_2+
                                 Bootstrap::Grid::Small::col_sm_3+
                                 Bootstrap::Grid::ExtraSmall::col_xs_4);
    nextcontainer->addWidget(cpp14::make_unique<WText>("İleri"));
    nextcontainer->setContentAlignment(AlignmentFlag::Center);
    nextcontainer->addStyleClass(CSS::Button::GrayGrad);


    backcontainer->clicked().connect([=](){
        this->back(BasvuruItem());
        pageText->setText("<p>"+std::to_string(this->skip())+"-"+std::to_string(this->skip()+this->limit())+"</p><p>" + std::to_string(this->totalCount())+"</p>");
    });
    nextcontainer->clicked().connect([=](){
        this->next(BasvuruItem());
        pageText->setText("<p>"+std::to_string(this->skip())+"-"+std::to_string(this->skip()+this->limit())+"</p><p>" + std::to_string(this->totalCount())+"</p>");

    });



    {
        auto container = Footer()->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_4+
                                 Bootstrap::Grid::Medium::col_md_3+
                                 Bootstrap::Grid::Small::col_sm_2+
                                 Bootstrap::Grid::ExtraSmall::col_xs_1+Bootstrap::Grid::Hidden::hidden_xs);
    }
}

void BasvuruYonetimPanel::onList(const QVector<BasvuruItem> *mlist)
{
    this->Content()->clear();

    for( const auto &item : *mlist ){

        auto _container = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
        _container->addStyleClass(Bootstrap::Grid::Large::col_lg_2+
                                  Bootstrap::Grid::Medium::col_md_3+
                                  Bootstrap::Grid::Small::col_sm_4+
                                  Bootstrap::Grid::ExtraSmall::col_xs_6);
        _container->setMargin(15,Side::Top);
        _container->decorationStyle().setCursor(Cursor::PointingHand);

        auto container = _container->addWidget(cpp14::make_unique<WContainerWidget>());
        if( item.getCinsiyet() == "Erkek"){
            container->addStyleClass(CSS::BackGround::DimBlueCyan);
        }else if( item.getCinsiyet() == "Kadın"){
            container->addStyleClass(CSS::BackGround::DarkPurple);
        } else {
            container->addStyleClass(CSS::BackGround::LightPurple);
        }
        container->setPadding(10,Side::Top|Side::Bottom);
        container->addStyleClass(CSSStyle::Shadows::shadow8px+CSSStyle::Radius::radius3px);

        {
            auto text = container->addWidget(cpp14::make_unique<WText>("<b>"+item.getAdSoyad()+"</b>"));
            text->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue));
        }
        container->addWidget(cpp14::make_unique<WBreak>());

        {
            auto text = container->addWidget(cpp14::make_unique<WText>("<i>"+item.getEgitim()+"</i>"));
            text->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue));
        }
        container->addWidget(cpp14::make_unique<WBreak>());

        {
            auto text = container->addWidget(cpp14::make_unique<WText>(item.getOnay() ? "<i>Onaylanmış</i>" : "<i>Onaylanmamış</i>"));
            text->setPadding(5,Side::Right|Side::Left);
            if( item.getOnay() ){
                text->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue)+Style::background::color::color(Style::color::Green::Green));
            }else{
                text->setAttributeValue(Style::style,Style::color::color(Style::color::Grey::Black)+Style::background::color::color(Style::color::Red::LightSalmon));
            }
        }

        _container->clicked().connect([=](){

            auto mDialog = this->createDialog("<h4><b>"+item.getAdSoyad()+"</b></h4>");

            auto vLayout = mDialog->contents()->setLayout(cpp14::make_unique<WVBoxLayout>());

            vLayout->addWidget(cpp14::make_unique<WText>("TCNO: "+item.getTCNO()));
            vLayout->addWidget(cpp14::make_unique<WText>("Cep: "+item.getCepNo()));
            vLayout->addWidget(cpp14::make_unique<WText>("Mail: "+item.getMail()));
            vLayout->addWidget(cpp14::make_unique<WText>("Cinsiyet: "+item.getCinsiyet()));
            vLayout->addWidget(cpp14::make_unique<WText>("Eğitim: "+item.getEgitim()));
            vLayout->addWidget(cpp14::make_unique<WText>("Yaş Aralık: "+item.getYasAralik()));
            vLayout->addWidget(cpp14::make_unique<WText>("Aileden: "+item.getAileKatilim()));
            vLayout->addWidget(cpp14::make_unique<WText>("Arkadaş: "+item.getArkadasKatilim()));
            vLayout->addWidget(cpp14::make_unique<WText>("Nereden: "+item.getNereden()));
            vLayout->addWidget(cpp14::make_unique<WText>("Katılım Şartı: "+item.getNasilKatilirim()));
            vLayout->addWidget(cpp14::make_unique<WText>("Adres: "+item.getAdres()));

            auto onaylaBtn = mDialog->footer()->addWidget(cpp14::make_unique<WPushButton>("Başvuruyu Onayla"));
            onaylaBtn->addStyleClass(Bootstrap::Button::Success);
            onaylaBtn->clicked().connect([=](){
                BasvuruItem filter;
                filter.setOid(item.oid().value().to_string());
                filter.setOnay(true);
                if( this->UpdateItem(filter) ){
                    this->UpdateList();
                }
                this->removeDialog(mDialog);
            });

            auto redBtn = mDialog->footer()->addWidget(cpp14::make_unique<WPushButton>("Başvuruyu Red Et"));
            redBtn->addStyleClass(Bootstrap::Button::Danger);
            redBtn->clicked().connect([=](){
                BasvuruItem filter;
                filter.setOid(item.oid().value().to_string());
                filter.setOnay(false);
                if( this->UpdateItem(filter) ){
                    this->UpdateList();
                }
                this->removeDialog(mDialog);
            });

            mDialog->show();
        });


    }
}

void BasvuruYonetimPanel::errorOccured(const std::string &errorText)
{
    this->warnDialog(errorText);
}

IstatistikWidget::IstatistikWidget(DB *_mDB)
    :BasvuruManager(_mDB)
{
    this->initIstatistik();
}

void IstatistikWidget::onList(const QVector<BasvuruItem> *mlist)
{

}

void IstatistikWidget::errorOccured(const std::string &errorText)
{
    this->warnDialog(errorText);
}

void IstatistikWidget::initIstatistik()
{



    {
        int cinsiyetKadin = this->countItem(BasvuruItem().setCinsiyet(true));
        int cinsiyetErkek = this->countItem(BasvuruItem().setCinsiyet(false));

        auto container_ = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
        container_->addStyleClass(Bootstrap::Grid::Large::col_lg_4+
                                 Bootstrap::Grid::Medium::col_md_4+
                                 Bootstrap::Grid::Small::col_sm_6+
                                 Bootstrap::Grid::ExtraSmall::col_xs_12);
        auto container = container_->addWidget(cpp14::make_unique<WContainerWidget>());

        container->setHeight(75);
        container->setPositionScheme(PositionScheme::Relative);
        container->addStyleClass(CSSStyle::Radius::radius3px+CSSStyle::Shadows::shadow8px);
        container->setAttributeValue(Style::style,Style::background::color::rgb(this->getRandom(200,255),this->getRandom(200,255),this->getRandom(200,255))+Style::color::color(Style::color::White::AliceBlue));

        auto titleContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
        titleContainer->setHeight(20);
        titleContainer->setPositionScheme(PositionScheme::Absolute);
        titleContainer->setWidth(WLength("100%"));
        titleContainer->setAttributeValue(Style::style,Style::background::color::rgb(this->getRandom(50,100),this->getRandom(50,100),this->getRandom(50,100))+Style::color::color(Style::color::White::AliceBlue));
        titleContainer->setOffsets(0,Side::Left);
        titleContainer->setOffsets(5,Side::Top);
        titleContainer->setContentAlignment(AlignmentFlag::Center);
        titleContainer->addWidget(cpp14::make_unique<WText>("<b>Cinsiyet Dağılımı</b>"));

        auto kadinContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
        kadinContainer->setHeight(20);
        kadinContainer->setPositionScheme(PositionScheme::Absolute);
        kadinContainer->setWidth(WLength(WString("{1}%").arg(static_cast<double>(cinsiyetKadin)/static_cast<double>(cinsiyetErkek+cinsiyetKadin)*100).toUTF8()));
        kadinContainer->setAttributeValue(Style::style,Style::background::color::rgb(this->getRandom(50,100),this->getRandom(50,100),this->getRandom(50,100))+Style::color::color(Style::color::White::AliceBlue));
        kadinContainer->setOffsets(0,Side::Left);
        kadinContainer->setOffsets(30,Side::Top);
        kadinContainer->setContentAlignment(AlignmentFlag::Left);
        kadinContainer->addWidget(cpp14::make_unique<WText>(WString("<i>Kadın : {1}</i>").arg(cinsiyetKadin)));

        auto erkekContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
        erkekContainer->setHeight(20);
        erkekContainer->setPositionScheme(PositionScheme::Absolute);
        erkekContainer->setWidth(WLength(WString("{1}%").arg(static_cast<double>(cinsiyetErkek)/static_cast<double>(cinsiyetErkek+cinsiyetKadin)*100).toUTF8()));
        erkekContainer->setAttributeValue(Style::style,Style::background::color::rgb(this->getRandom(50,100),this->getRandom(50,100),this->getRandom(50,100))+Style::color::color(Style::color::White::AliceBlue));
        erkekContainer->setOffsets(0,Side::Left);
        erkekContainer->setOffsets(53,Side::Top);
        erkekContainer->setContentAlignment(AlignmentFlag::Left);
        erkekContainer->addWidget(cpp14::make_unique<WText>(WString("<i>Erkek : {1}</i>").arg(cinsiyetErkek)));
    }

    {

//        yasComboBox->addItem("10-14");
//        yasComboBox->addItem("15-18");
//        yasComboBox->addItem("19-25");
//        yasComboBox->addItem("26-35");
//        yasComboBox->addItem("36-50");
//        yasComboBox->addItem("50 Üzeri");

        int yas10_14 = this->countItem(BasvuruItem().setYasAralik("10-14"));
        int yas15_18 = this->countItem(BasvuruItem().setYasAralik("15-18"));
        int yas19_25 = this->countItem(BasvuruItem().setYasAralik("19-25"));
        int yas26_35 = this->countItem(BasvuruItem().setYasAralik("26-35"));
        int yas36_50 = this->countItem(BasvuruItem().setYasAralik("36-50"));
        int yas50Uzeri = this->countItem(BasvuruItem().setYasAralik("50 Üzeri"));

        double totalBas = static_cast<double>(yas10_14+yas15_18+yas19_25+yas26_35+yas36_50+yas50Uzeri);



        auto container_ = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
        container_->addStyleClass(Bootstrap::Grid::Large::col_lg_4+
                                 Bootstrap::Grid::Medium::col_md_4+
                                 Bootstrap::Grid::Small::col_sm_6+
                                 Bootstrap::Grid::ExtraSmall::col_xs_12);
        auto container = container_->addWidget(cpp14::make_unique<WContainerWidget>());
        container->setHeight(180);
        container->setPositionScheme(PositionScheme::Relative);
        container->addStyleClass(CSSStyle::Radius::radius3px+CSSStyle::Shadows::shadow8px);
        container->setAttributeValue(Style::style,Style::background::color::rgb(this->getRandom(200,255),this->getRandom(200,255),this->getRandom(200,255))+Style::color::color(Style::color::White::AliceBlue));

        auto titleContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
        titleContainer->setHeight(20);
        titleContainer->setPositionScheme(PositionScheme::Absolute);
        titleContainer->setWidth(WLength("100%"));
        titleContainer->setAttributeValue(Style::style,Style::background::color::rgb(this->getRandom(50,100),this->getRandom(50,100),this->getRandom(50,100))+Style::color::color(Style::color::White::AliceBlue));
        titleContainer->setOffsets(0,Side::Left);
        titleContainer->setOffsets(5,Side::Top);
        titleContainer->setContentAlignment(AlignmentFlag::Center);
        titleContainer->addWidget(cpp14::make_unique<WText>("<b>Yaş Dağılımı</b>"));

        {
            auto oContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
            oContainer->setHeight(20);
            oContainer->setPositionScheme(PositionScheme::Absolute);
            oContainer->setWidth(WLength(WString("{1}%").arg(static_cast<double>(yas10_14)/static_cast<double>(totalBas)*100).toUTF8()));
            oContainer->setAttributeValue(Style::style,Style::background::color::rgb(this->getRandom(50,100),this->getRandom(50,100),this->getRandom(50,100))+Style::color::color(Style::color::White::AliceBlue));
            oContainer->setOffsets(0,Side::Left);
            oContainer->setOffsets(30,Side::Top);
            oContainer->setContentAlignment(AlignmentFlag::Left);
            oContainer->addWidget(cpp14::make_unique<WText>(WString("<i>10-14 : {1}</i>").arg(yas10_14)));
        }

        {
            auto oContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
            oContainer->setHeight(20);
            oContainer->setPositionScheme(PositionScheme::Absolute);
            oContainer->setWidth(WLength(WString("{1}%").arg(static_cast<double>(yas15_18)/static_cast<double>(totalBas)*100).toUTF8()));
            oContainer->setAttributeValue(Style::style,Style::background::color::rgb(this->getRandom(50,100),this->getRandom(50,100),this->getRandom(50,100))+Style::color::color(Style::color::White::AliceBlue));
            oContainer->setOffsets(0,Side::Left);
            oContainer->setOffsets(55,Side::Top);
            oContainer->setContentAlignment(AlignmentFlag::Left);
            oContainer->addWidget(cpp14::make_unique<WText>(WString("<i>15-18 : {1}</i>").arg(yas15_18)));
        }

        {
            auto oContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
            oContainer->setHeight(20);
            oContainer->setPositionScheme(PositionScheme::Absolute);
            oContainer->setWidth(WLength(WString("{1}%").arg(static_cast<double>(yas19_25)/static_cast<double>(totalBas)*100).toUTF8()));
            oContainer->setAttributeValue(Style::style,Style::background::color::rgb(this->getRandom(50,100),this->getRandom(50,100),this->getRandom(50,100))+Style::color::color(Style::color::White::AliceBlue));
            oContainer->setOffsets(0,Side::Left);
            oContainer->setOffsets(80,Side::Top);
            oContainer->setContentAlignment(AlignmentFlag::Left);
            oContainer->addWidget(cpp14::make_unique<WText>(WString("<i>19-25 : {1}</i>").arg(yas19_25)));
        }

        {
            auto oContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
            oContainer->setHeight(20);
            oContainer->setPositionScheme(PositionScheme::Absolute);
            oContainer->setWidth(WLength(WString("{1}%").arg(static_cast<double>(yas26_35)/static_cast<double>(totalBas)*100).toUTF8()));
            oContainer->setAttributeValue(Style::style,Style::background::color::rgb(this->getRandom(50,100),this->getRandom(50,100),this->getRandom(50,100))+Style::color::color(Style::color::White::AliceBlue));
            oContainer->setOffsets(0,Side::Left);
            oContainer->setOffsets(105,Side::Top);
            oContainer->setContentAlignment(AlignmentFlag::Left);
            oContainer->addWidget(cpp14::make_unique<WText>(WString("<i>26-35 : {1}</i>").arg(yas26_35)));
        }

        {
            auto oContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
            oContainer->setHeight(20);
            oContainer->setPositionScheme(PositionScheme::Absolute);
            oContainer->setWidth(WLength(WString("{1}%").arg(static_cast<double>(yas36_50)/static_cast<double>(totalBas)*100).toUTF8()));
            oContainer->setAttributeValue(Style::style,Style::background::color::rgb(this->getRandom(50,100),this->getRandom(50,100),this->getRandom(50,100))+Style::color::color(Style::color::White::AliceBlue));
            oContainer->setOffsets(0,Side::Left);
            oContainer->setOffsets(130,Side::Top);
            oContainer->setContentAlignment(AlignmentFlag::Left);
            oContainer->addWidget(cpp14::make_unique<WText>(WString("<i>36-50 : {1}</i>").arg(yas36_50)));
        }

        {
            auto oContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
            oContainer->setHeight(20);
            oContainer->setPositionScheme(PositionScheme::Absolute);
            oContainer->setWidth(WLength(WString("{1}%").arg(static_cast<double>(yas36_50)/static_cast<double>(totalBas)*100).toUTF8()));
            oContainer->setAttributeValue(Style::style,Style::background::color::rgb(this->getRandom(50,100),this->getRandom(50,100),this->getRandom(50,100))+Style::color::color(Style::color::White::AliceBlue));
            oContainer->setOffsets(0,Side::Left);
            oContainer->setOffsets(155,Side::Top);
            oContainer->setContentAlignment(AlignmentFlag::Left);
            oContainer->addWidget(cpp14::make_unique<WText>(WString("<i>50 Üzeri : {1}</i>").arg(yas50Uzeri)));
        }

    }


    {

        int ilkokul = this->countItem(BasvuruItem().setEgitim(SKey::BasvuruItem::Egitim::ilkOkul));
        int ortaOkul = this->countItem(BasvuruItem().setEgitim(SKey::BasvuruItem::Egitim::ortaOkul));
        int lise = this->countItem(BasvuruItem().setEgitim(SKey::BasvuruItem::Egitim::lise));
        int onlisans = this->countItem(BasvuruItem().setEgitim(SKey::BasvuruItem::Egitim::onlisans));
        int lisans = this->countItem(BasvuruItem().setEgitim(SKey::BasvuruItem::Egitim::lisans));
        int yuksellisans = this->countItem(BasvuruItem().setEgitim(SKey::BasvuruItem::Egitim::yukselLisans));
        int doktora = this->countItem(BasvuruItem().setEgitim(SKey::BasvuruItem::Egitim::doktora));

        double totalBas = static_cast<double>(ilkokul+ortaOkul+lise+onlisans+lisans+yuksellisans+doktora);



        auto container_ = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
        container_->addStyleClass(Bootstrap::Grid::Large::col_lg_4+
                                 Bootstrap::Grid::Medium::col_md_4+
                                 Bootstrap::Grid::Small::col_sm_6+
                                 Bootstrap::Grid::ExtraSmall::col_xs_12);
        auto container = container_->addWidget(cpp14::make_unique<WContainerWidget>());
        container->setHeight(200);
        container->setPositionScheme(PositionScheme::Relative);
        container->addStyleClass(CSSStyle::Radius::radius3px+CSSStyle::Shadows::shadow8px);
        container->setAttributeValue(Style::style,Style::background::color::rgb(this->getRandom(150,200),this->getRandom(150,200),this->getRandom(150,200))+Style::color::color(Style::color::White::AliceBlue));

        auto titleContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
        titleContainer->setHeight(20);
        titleContainer->setPositionScheme(PositionScheme::Absolute);
        titleContainer->setWidth(WLength("100%"));
        titleContainer->setAttributeValue(Style::style,Style::background::color::rgb(this->getRandom(50,100),this->getRandom(50,100),this->getRandom(50,100))+Style::color::color(Style::color::White::AliceBlue));
        titleContainer->setOffsets(0,Side::Left);
        titleContainer->setOffsets(5,Side::Top);
        titleContainer->setContentAlignment(AlignmentFlag::Center);
        titleContainer->addWidget(cpp14::make_unique<WText>("<b>Eğitim Dağılımı</b>"));

        {
            auto oContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
            oContainer->setHeight(20);
            oContainer->setPositionScheme(PositionScheme::Absolute);
            oContainer->setWidth(WLength(WString("{1}%").arg(static_cast<double>(ilkokul)/static_cast<double>(totalBas)*100).toUTF8()));
            oContainer->setAttributeValue(Style::style,Style::background::color::rgb(this->getRandom(50,100),this->getRandom(50,100),this->getRandom(50,100))+Style::color::color(Style::color::White::AliceBlue));
            oContainer->setOffsets(0,Side::Left);
            oContainer->setOffsets(30,Side::Top);
            oContainer->setContentAlignment(AlignmentFlag::Left);
            oContainer->addWidget(cpp14::make_unique<WText>(WString("<i>İlkokul:{1}</i>").arg(ilkokul)));
        }

        {
            auto oContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
            oContainer->setHeight(20);
            oContainer->setPositionScheme(PositionScheme::Absolute);
            oContainer->setWidth(WLength(WString("{1}%").arg(static_cast<double>(ortaOkul)/static_cast<double>(totalBas)*100).toUTF8()));
            oContainer->setAttributeValue(Style::style,Style::background::color::rgb(this->getRandom(50,100),this->getRandom(50,100),this->getRandom(50,100))+Style::color::color(Style::color::White::AliceBlue));
            oContainer->setOffsets(0,Side::Left);
            oContainer->setOffsets(55,Side::Top);
            oContainer->setContentAlignment(AlignmentFlag::Left);
            oContainer->addWidget(cpp14::make_unique<WText>(WString("<i>Ortaokul:{1}</i>").arg(ortaOkul)));
        }

        {
            auto oContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
            oContainer->setHeight(20);
            oContainer->setPositionScheme(PositionScheme::Absolute);
            oContainer->setWidth(WLength(WString("{1}%").arg(static_cast<double>(lise)/static_cast<double>(totalBas)*100).toUTF8()));
            oContainer->setAttributeValue(Style::style,Style::background::color::rgb(this->getRandom(50,100),this->getRandom(50,100),this->getRandom(50,100))+Style::color::color(Style::color::White::AliceBlue));
            oContainer->setOffsets(0,Side::Left);
            oContainer->setOffsets(80,Side::Top);
            oContainer->setContentAlignment(AlignmentFlag::Left);
            oContainer->addWidget(cpp14::make_unique<WText>(WString("<i>Lise:{1}</i>").arg(lise)));
        }

        {
            auto oContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
            oContainer->setHeight(20);
            oContainer->setPositionScheme(PositionScheme::Absolute);
            oContainer->setWidth(WLength(WString("{1}%").arg(static_cast<double>(onlisans)/static_cast<double>(totalBas)*100).toUTF8()));
            oContainer->setAttributeValue(Style::style,Style::background::color::rgb(this->getRandom(50,100),this->getRandom(50,100),this->getRandom(50,100))+Style::color::color(Style::color::White::AliceBlue));
            oContainer->setOffsets(0,Side::Left);
            oContainer->setOffsets(105,Side::Top);
            oContainer->setContentAlignment(AlignmentFlag::Left);
            oContainer->addWidget(cpp14::make_unique<WText>(WString("<i>ÖnLisans:{1}</i>").arg(onlisans)));
        }

        {
            auto oContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
            oContainer->setHeight(20);
            oContainer->setPositionScheme(PositionScheme::Absolute);
            oContainer->setWidth(WLength(WString("{1}%").arg(static_cast<double>(lisans)/static_cast<double>(totalBas)*100).toUTF8()));
            oContainer->setAttributeValue(Style::style,Style::background::color::rgb(this->getRandom(50,100),this->getRandom(50,100),this->getRandom(50,100))+Style::color::color(Style::color::White::AliceBlue));
            oContainer->setOffsets(0,Side::Left);
            oContainer->setOffsets(130,Side::Top);
            oContainer->setContentAlignment(AlignmentFlag::Left);
            oContainer->addWidget(cpp14::make_unique<WText>(WString("<i>Lisans:{1}</i>").arg(lisans)));
        }

        {
            auto oContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
            oContainer->setHeight(20);
            oContainer->setPositionScheme(PositionScheme::Absolute);
            oContainer->setWidth(WLength(WString("{1}%").arg(static_cast<double>(yuksellisans)/static_cast<double>(totalBas)*100).toUTF8()));
            oContainer->setAttributeValue(Style::style,Style::background::color::rgb(this->getRandom(50,100),this->getRandom(50,100),this->getRandom(50,100))+Style::color::color(Style::color::White::AliceBlue));
            oContainer->setOffsets(0,Side::Left);
            oContainer->setOffsets(155,Side::Top);
            oContainer->setContentAlignment(AlignmentFlag::Left);
            oContainer->addWidget(cpp14::make_unique<WText>(WString("<i>Yüksek_Lisans:{1}</i>").arg(yuksellisans)));
        }

        {
            auto oContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
            oContainer->setHeight(20);
            oContainer->setPositionScheme(PositionScheme::Absolute);
            oContainer->setWidth(WLength(WString("{1}%").arg(static_cast<double>(doktora)/static_cast<double>(totalBas)*100).toUTF8()));
            oContainer->setAttributeValue(Style::style,Style::background::color::rgb(this->getRandom(50,100),this->getRandom(50,100),this->getRandom(50,100))+Style::color::color(Style::color::White::AliceBlue));
            oContainer->setOffsets(0,Side::Left);
            oContainer->setOffsets(180,Side::Top);
            oContainer->setContentAlignment(AlignmentFlag::Left);
            oContainer->addWidget(cpp14::make_unique<WText>(WString("<i>Doktora:{1}</i>").arg(doktora)));
        }

    }


    {

        int sosyalMedya = this->countItem(BasvuruItem().setNerden(SKey::BasvuruItem::Nerden::sosyalMedya));
        int okul = this->countItem(BasvuruItem().setNerden(SKey::BasvuruItem::Nerden::okul));
        int afis = this->countItem(BasvuruItem().setNerden(SKey::BasvuruItem::Nerden::afis));
        int arkadas = this->countItem(BasvuruItem().setNerden(SKey::BasvuruItem::Nerden::arkadas));


        double totalBas = static_cast<double>(sosyalMedya+okul+afis+arkadas);



        auto container_ = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
        container_->addStyleClass(Bootstrap::Grid::Large::col_lg_4+
                                 Bootstrap::Grid::Medium::col_md_4+
                                 Bootstrap::Grid::Small::col_sm_6+
                                 Bootstrap::Grid::ExtraSmall::col_xs_12);
        auto container = container_->addWidget(cpp14::make_unique<WContainerWidget>());
        container->setHeight(135);
        container->setPositionScheme(PositionScheme::Relative);
        container->addStyleClass(CSSStyle::Radius::radius3px+CSSStyle::Shadows::shadow8px);
        container->setAttributeValue(Style::style,Style::background::color::rgb(this->getRandom(150,200),this->getRandom(150,200),this->getRandom(150,200))+Style::color::color(Style::color::White::AliceBlue));

        auto titleContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
        titleContainer->setHeight(20);
        titleContainer->setPositionScheme(PositionScheme::Absolute);
        titleContainer->setWidth(WLength("100%"));
        titleContainer->setAttributeValue(Style::style,Style::background::color::rgb(this->getRandom(50,100),this->getRandom(50,100),this->getRandom(50,100))+Style::color::color(Style::color::White::AliceBlue));
        titleContainer->setOffsets(0,Side::Left);
        titleContainer->setOffsets(5,Side::Top);
        titleContainer->setContentAlignment(AlignmentFlag::Center);
        titleContainer->addWidget(cpp14::make_unique<WText>("<b>Nerden</b>"));

        {
            auto oContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
            oContainer->setHeight(20);
            oContainer->setPositionScheme(PositionScheme::Absolute);
            oContainer->setWidth(WLength(WString("{1}%").arg(static_cast<double>(sosyalMedya)/static_cast<double>(totalBas)*100).toUTF8()));
            oContainer->setAttributeValue(Style::style,Style::background::color::rgb(this->getRandom(50,100),this->getRandom(50,100),this->getRandom(50,100))+Style::color::color(Style::color::White::AliceBlue));
            oContainer->setOffsets(0,Side::Left);
            oContainer->setOffsets(30,Side::Top);
            oContainer->setContentAlignment(AlignmentFlag::Left);
            oContainer->addWidget(cpp14::make_unique<WText>(WString("<i>Sosyal_Medya:{1}</i>").arg(sosyalMedya)));
        }

        {
            auto oContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
            oContainer->setHeight(20);
            oContainer->setPositionScheme(PositionScheme::Absolute);
            oContainer->setWidth(WLength(WString("{1}%").arg(static_cast<double>(okul)/static_cast<double>(totalBas)*100).toUTF8()));
            oContainer->setAttributeValue(Style::style,Style::background::color::rgb(this->getRandom(50,100),this->getRandom(50,100),this->getRandom(50,100))+Style::color::color(Style::color::White::AliceBlue));
            oContainer->setOffsets(0,Side::Left);
            oContainer->setOffsets(55,Side::Top);
            oContainer->setContentAlignment(AlignmentFlag::Left);
            oContainer->addWidget(cpp14::make_unique<WText>(WString("<i>Okul:{1}</i>").arg(okul)));
        }

        {
            auto oContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
            oContainer->setHeight(20);
            oContainer->setPositionScheme(PositionScheme::Absolute);
            oContainer->setWidth(WLength(WString("{1}%").arg(static_cast<double>(afis)/static_cast<double>(totalBas)*100).toUTF8()));
            oContainer->setAttributeValue(Style::style,Style::background::color::rgb(this->getRandom(50,100),this->getRandom(50,100),this->getRandom(50,100))+Style::color::color(Style::color::White::AliceBlue));
            oContainer->setOffsets(0,Side::Left);
            oContainer->setOffsets(80,Side::Top);
            oContainer->setContentAlignment(AlignmentFlag::Left);
            oContainer->addWidget(cpp14::make_unique<WText>(WString("<i>Afiş:{1}</i>").arg(afis)));
        }

        {
            auto oContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
            oContainer->setHeight(20);
            oContainer->setPositionScheme(PositionScheme::Absolute);
            oContainer->setWidth(WLength(WString("{1}%").arg(static_cast<double>(arkadas)/static_cast<double>(totalBas)*100).toUTF8()));
            oContainer->setAttributeValue(Style::style,Style::background::color::rgb(this->getRandom(50,100),this->getRandom(50,100),this->getRandom(50,100))+Style::color::color(Style::color::White::AliceBlue));
            oContainer->setOffsets(0,Side::Left);
            oContainer->setOffsets(105,Side::Top);
            oContainer->setContentAlignment(AlignmentFlag::Left);
            oContainer->addWidget(cpp14::make_unique<WText>(WString("<i>Arkadaş:{1}</i>").arg(arkadas)));
        }



    }


    {

        int cevrimici = this->countItem(BasvuruItem().setKatilimTuru(SKey::BasvuruItem::KatilimTuru::cevrimici));
        int yuzyuze = this->countItem(BasvuruItem().setKatilimTuru(SKey::BasvuruItem::KatilimTuru::yuzyuze));
        int herikisi = this->countItem(BasvuruItem().setKatilimTuru(SKey::BasvuruItem::KatilimTuru::herikisi));


        double totalBas = static_cast<double>(cevrimici+yuzyuze+herikisi);



        auto container_ = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
        container_->addStyleClass(Bootstrap::Grid::Large::col_lg_4+
                                 Bootstrap::Grid::Medium::col_md_4+
                                 Bootstrap::Grid::Small::col_sm_6+
                                 Bootstrap::Grid::ExtraSmall::col_xs_12);
        auto container = container_->addWidget(cpp14::make_unique<WContainerWidget>());
        container->setHeight(135);
        container->setPositionScheme(PositionScheme::Relative);
        container->addStyleClass(CSSStyle::Radius::radius3px+CSSStyle::Shadows::shadow8px);
        container->setAttributeValue(Style::style,Style::background::color::rgb(this->getRandom(150,200),this->getRandom(150,200),this->getRandom(150,200))+Style::color::color(Style::color::White::AliceBlue));

        auto titleContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
        titleContainer->setHeight(20);
        titleContainer->setPositionScheme(PositionScheme::Absolute);
        titleContainer->setWidth(WLength("100%"));
        titleContainer->setAttributeValue(Style::style,Style::background::color::rgb(this->getRandom(50,100),this->getRandom(50,100),this->getRandom(50,100))+Style::color::color(Style::color::White::AliceBlue));
        titleContainer->setOffsets(0,Side::Left);
        titleContainer->setOffsets(5,Side::Top);
        titleContainer->setContentAlignment(AlignmentFlag::Center);
        titleContainer->addWidget(cpp14::make_unique<WText>("<b>Katılım Türü Dağılımı</b>"));

        {
            auto oContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
            oContainer->setHeight(20);
            oContainer->setPositionScheme(PositionScheme::Absolute);
            oContainer->setWidth(WLength(WString("{1}%").arg(static_cast<double>(cevrimici)/static_cast<double>(totalBas)*100).toUTF8()));
            oContainer->setAttributeValue(Style::style,Style::background::color::rgb(this->getRandom(50,100),this->getRandom(50,100),this->getRandom(50,100))+Style::color::color(Style::color::White::AliceBlue));
            oContainer->setOffsets(0,Side::Left);
            oContainer->setOffsets(30,Side::Top);
            oContainer->setContentAlignment(AlignmentFlag::Left);
            oContainer->addWidget(cpp14::make_unique<WText>(WString("<i>Çevrimiçi:{1}</i>").arg(cevrimici)));
        }

        {
            auto oContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
            oContainer->setHeight(20);
            oContainer->setPositionScheme(PositionScheme::Absolute);
            oContainer->setWidth(WLength(WString("{1}%").arg(static_cast<double>(yuzyuze)/static_cast<double>(totalBas)*100).toUTF8()));
            oContainer->setAttributeValue(Style::style,Style::background::color::rgb(this->getRandom(50,100),this->getRandom(50,100),this->getRandom(50,100))+Style::color::color(Style::color::White::AliceBlue));
            oContainer->setOffsets(0,Side::Left);
            oContainer->setOffsets(55,Side::Top);
            oContainer->setContentAlignment(AlignmentFlag::Left);
            oContainer->addWidget(cpp14::make_unique<WText>(WString("<i>Yüzyüze:{1}</i>").arg(yuzyuze)));
        }

        {
            auto oContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
            oContainer->setHeight(20);
            oContainer->setPositionScheme(PositionScheme::Absolute);
            oContainer->setWidth(WLength(WString("{1}%").arg(static_cast<double>(herikisi)/static_cast<double>(totalBas)*100).toUTF8()));
            oContainer->setAttributeValue(Style::style,Style::background::color::rgb(this->getRandom(50,100),this->getRandom(50,100),this->getRandom(50,100))+Style::color::color(Style::color::White::AliceBlue));
            oContainer->setOffsets(0,Side::Left);
            oContainer->setOffsets(80,Side::Top);
            oContainer->setContentAlignment(AlignmentFlag::Left);
            oContainer->addWidget(cpp14::make_unique<WText>(WString("<i>Herikisi:{1}</i>").arg(herikisi)));
        }




    }

}























