#include "soruonaypanel.h"

#include <map>
#include <algorithm>
#include <random>
#include <iterator>


SoruOnayPanel::SoruOnayPanel(DB *_mDB, User *_mUser)
    :SoruManager(_mDB,_mUser),mUserManager(new UserManager(this->getDB()))
{


    this->setMargin(25,Side::Top|Side::Bottom);



    this->Footer()->setMargin(25,Side::Top);
    {
        auto container = Footer()->addWidget(cpp14::make_unique<WContainerWidget>());
        container->setContentAlignment(AlignmentFlag::Justify);
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_6+Bootstrap::Grid::Medium::col_md_6+Bootstrap::Grid::Small::col_sm_6+Bootstrap::Grid::ExtraSmall::col_xs_6);
        auto backBtn = container->addWidget(cpp14::make_unique<WPushButton>("Geri"));
        backBtn->addStyleClass(Bootstrap::Button::Primary);
        backBtn->setWidth(WLength("100%"));

        backBtn->clicked().connect([=](){
            this->back(Soru());
        });
    }
    {
        auto container = Footer()->addWidget(cpp14::make_unique<WContainerWidget>());
        container->setContentAlignment(AlignmentFlag::Justify);
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_6+Bootstrap::Grid::Medium::col_md_6+Bootstrap::Grid::Small::col_sm_6+Bootstrap::Grid::ExtraSmall::col_xs_6);
        auto backBtn = container->addWidget(cpp14::make_unique<WPushButton>("İleri"));
        backBtn->addStyleClass(Bootstrap::Button::Primary);
        backBtn->setWidth(WLength("100%"));
        backBtn->clicked().connect([=](){
            this->next(Soru());
        });
    }



    this->initStatistic();

}

void SoruOnayPanel::onList(const QVector<Soru> *mlist)
{

    this->Content()->clear();







    WContainerWidget* rContainer;
    int soruCounter = 0;


    QVector<Soru> newList;

    for( const auto &item : *mlist ){
        switch (mCurrentFilter) {
        case FILTER::NONE:
            newList.append(item);
            break;
        case FILTER::ONAYLI:
            if( item.isGecerli() ){
                newList.append(item);
            }
            break;

        case FILTER::ONAYSIZ:
            if( !item.isGecerli() ){
                newList.append(item);
            }
            break;
        case FILTER::OYLAMATAMAM:
            if( item.voteCount() >= 3 ){
                newList.append(item);
            }
            break;
        case FILTER::OYLAMABEKLEYEN:
            if( item.voteCount() < 3 ){
                newList.append(item);
            }
            break;

        case FILTER::IPTAL:
            if( item.isDeleted() ){
                newList.append(item);
            }
            break;
        default:
            break;
        }
    }


    for( const auto &item : newList ){


        if( soruCounter%4 == 0 ){
            rContainer = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
            rContainer->addStyleClass(Bootstrap::Grid::row);
            rContainer->addStyleClass(CSSStyle::Shadows::shadow8px+CSSStyle::Radius::radius3px);
            rContainer->setMargin(25,Side::Bottom|Side::Top);
        }

        soruCounter++;
        auto  container_ = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container_->setPositionScheme(PositionScheme::Relative);

        if( item.isDeleted() ){
            container_->setOverflow(Overflow::Hidden);
            auto deletedContainer = container_->addWidget(cpp14::make_unique<WContainerWidget>());
            deletedContainer->setPositionScheme(PositionScheme::Absolute);
            deletedContainer->setWidth(WLength("100%"));
            deletedContainer->setHeight(WLength("100%"));
            deletedContainer->setAttributeValue(Style::style,Style::background::color::rgba(255,0,0));
            deletedContainer->setZIndex(100);
            deletedContainer->setContentAlignment(AlignmentFlag::Center);
            deletedContainer->setPadding(100,Side::Top);

            auto delText = deletedContainer->addWidget(cpp14::make_unique<WText>("<b>İptal Edilmiş!</b>"));
            delText->setAttributeValue(Style::style,Style::font::size::s24px+Style::color::color(Style::color::White::AliceBlue));
            delText->setMargin(WLength("30%"),Side::Top);
        }


        //        auto container_ = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
        container_->setMargin(15,Side::Bottom|Side::Top);

        container_->addStyleClass(Bootstrap::Grid::Large::col_lg_3+
                                  Bootstrap::Grid::Medium::col_md_4+
                                  Bootstrap::Grid::Small::col_sm_6+
                                  Bootstrap::Grid::ExtraSmall::col_xs_12);

        auto container = container_->addWidget(cpp14::make_unique<WContainerWidget>());


        container->addStyleClass(Bootstrap::ContextualBackGround::bg_info+Bootstrap::ImageShape::img_thumbnail);

        auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());


        auto OnayContainer = vLayout->addWidget(cpp14::make_unique<WContainerWidget>(),0,AlignmentFlag::Justify);



        if( item.redCount()+item.onayCount() < 3 ){
            OnayContainer->addStyleClass(Bootstrap::ContextualBackGround::bg_danger);
            OnayContainer->addWidget(cpp14::make_unique<WText>("Onay Sayısı Yetersiz!!!"));
        }else{
            if( item.isGecerli() ){
                OnayContainer->setAttributeValue(Style::style,Style::background::color::color(Style::color::Green::DarkGreen)+Style::color::color(Style::color::White::AliceBlue));
                OnayContainer->addWidget(cpp14::make_unique<WText>("Onaylandı"));
            }else{
                OnayContainer->setAttributeValue(Style::style,Style::background::color::color(Style::color::Red::DarkRed)+Style::color::color(Style::color::White::AliceBlue));
                OnayContainer->addWidget(cpp14::make_unique<WText>("Red Edilmiş"));
            }
        }
        vLayout->addSpacing(2);

        vLayout->addWidget(cpp14::make_unique<WText>(item.getSoru()),0,AlignmentFlag::Left)->setTextAlignment(AlignmentFlag::Left);

        vLayout->addSpacing(2);
        auto cevapList = item.getCevaplarStruct();


        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(cevapList.begin(),
                     cevapList.end(),
                     g);

        int count = 1;
        for( const auto &cevapItem : cevapList ){
            if( cevapItem.index == item.getCevapIndex() ){
                std::string textSikBaslik = count == 1 ? "A) " : ( count == 2 ? "B) " : ( count == 3 ? "C) " : ( count == 4 ? "D) " : ( count == 5 ? "E) " : ( count == 6 ? "F) " : ( count == 7 ? "G) " : "H) " ) ) ) ) ) );


                if( item.isDeleted() ) {
                    auto text = vLayout->addWidget(cpp14::make_unique<WText>("<h5>"+textSikBaslik+cevapItem.Cevap+"</h5>"),0,AlignmentFlag::Left);
                    text->setTextAlignment(AlignmentFlag::Left);
                    //                    text->setAttributeValue(Style::style,Style::background::color::color(Style::color::Green::Green)+Style::color::color(Style::color::White::AliceBlue));
                    text->setPadding(5,Side::Right);
                }else{
                    auto text = vLayout->addWidget(cpp14::make_unique<WText>("<h5><b>"+textSikBaslik+cevapItem.Cevap+"</b></h5>"),0,AlignmentFlag::Left);
                    text->setTextAlignment(AlignmentFlag::Left);
                    text->setAttributeValue(Style::style,Style::background::color::color(Style::color::Green::Green)+Style::color::color(Style::color::White::AliceBlue));
                    text->setPadding(5,Side::Right);
                }
            }else{
                std::string textSikBaslik = count == 1 ? "A) " : ( count == 2 ? "B) " : ( count == 3 ? "C) " : ( count == 4 ? "D) " : ( count == 5 ? "E) " : ( count == 6 ? "F) " : ( count == 7 ? "G) " : "H) " ) ) ) ) ) );
                vLayout->addWidget(cpp14::make_unique<WText>(textSikBaslik+cevapItem.Cevap),0,AlignmentFlag::Left)->setTextAlignment(AlignmentFlag::Left);
            }
            count++;
        }
        vLayout->addSpacing(2);
        auto onayText = vLayout->addWidget(cpp14::make_unique<WText>(std::to_string(item.onayCount())+" Onay"),0,AlignmentFlag::Justify);
        onayText->setTextAlignment(AlignmentFlag::Center);
        onayText->addStyleClass(Bootstrap::Label::Success);

        vLayout->addSpacing(2);
        auto redText = vLayout->addWidget(cpp14::make_unique<WText>(std::to_string(item.redCount())+" Red"),0,AlignmentFlag::Justify);
        redText->setTextAlignment(AlignmentFlag::Center);
        redText->addStyleClass(Bootstrap::Label::Danger);

        vLayout->addSpacing(2);
        auto onayController = vLayout->addWidget(cpp14::make_unique<WContainerWidget>(),0,AlignmentFlag::Justify);
        auto hLayout = onayController->setLayout(cpp14::make_unique<WHBoxLayout>());
        auto onaylaBtn = hLayout->addWidget(cpp14::make_unique<WPushButton>("Onayla"));
        if( item.isDeleted() ) onaylaBtn->setEnabled(false);
        onaylaBtn->addStyleClass(Bootstrap::Button::Success);
        onaylaBtn->clicked().connect([=](){
            if( this->CurrentUser()->oid().value().to_string() == item.getEkleyen() ){
                this->criticDialog("Soru Sahibi Olduğunuz için <b>Onaylama Yapamazsınız!</b>");
                return;
            }
            Soru soru;
            soru.setDocumentView(item.view());
            if( soru.addOnay(true,this->CurrentUser()->oid().value().to_string()) ){
                if( this->UpdateItem(soru) ){
                    this->UpdateList();
                }else{
                    this->warnDialog("Onaylama Yapılamadı, E:"+this->getLastError().toStdString());
                }
            }else{
                this->warnDialog(std::to_string(__LINE__)+" " + std::string(__FILE__) +" <b>" +soru.lastError()+"</b>");
            }
        });


        auto redBtn = hLayout->addWidget(cpp14::make_unique<WPushButton>("Red Et"));
        redBtn->addStyleClass(Bootstrap::Button::Danger);
        if( item.isDeleted() ) redBtn->setEnabled(false);

        redBtn->clicked().connect([=](){
            if( this->CurrentUser()->oid().value().to_string() == item.getEkleyen() ){
                this->criticDialog("Soru Sahibi Olduğunuz için <b>Onaylama Yapamazsınız!</b>");
                return;
            }


            auto mDialog = createDialog("Gerekçe");

            auto mGerekceTextEdit = mDialog->contents()->addWidget(cpp14::make_unique<WTextArea>());
            mDialog->contents()->addWidget(cpp14::make_unique<WBreak>());
            auto infoText = mDialog->contents()->addWidget(cpp14::make_unique<WText>(""));
            auto saveBtn = mDialog->footer()->addWidget(cpp14::make_unique<WPushButton>("Kaydet"));

            saveBtn->clicked().connect([=](){

                if( mGerekceTextEdit->text().toUTF8().size() < 10 ){
                    infoText->setText("Yetersiz Açıklama");
                    return;
                }

                Soru soru;
                soru.setDocumentView(item.view());
                if( soru.addOnay(false,this->CurrentUser()->oid().value().to_string(),mGerekceTextEdit->text().toUTF8()) ){
                    if( this->UpdateItem(soru) ){
                        this->removeDialog(mDialog);
                        this->UpdateList();
                    }else{
                        this->warnDialog("Red Etme Yapılamadı, E:"+this->getLastError().toStdString());
                    }
                }else{
                    this->warnDialog(std::to_string(__LINE__)+" " + std::string(__FILE__) + " " + soru.lastError());
                }

            });

            mDialog->show();


        });


        for( const auto &vote : item.getOnayStruct() ){
            vLayout->addSpacing(2);
            User _user;
            _user.setOid(vote.owner);
            if( vote.Onay ){
                auto onay1Text = vLayout->addWidget(cpp14::make_unique<WText>(mUserManager->FindOneItem(_user).getAdSoyad()+" Onay +1"),0,AlignmentFlag::Justify);
                onay1Text->setTextAlignment(AlignmentFlag::Center);
                onay1Text->addStyleClass(Bootstrap::Label::Success);
            }else{
                if( vote.owner.size() > 0 ){
                    auto onay1Text = vLayout->addWidget(cpp14::make_unique<WText>("<p>"+mUserManager->FindOneItem(_user).getAdSoyad()+" Red -1</p><p>Gerekçe: "+vote.aciklama+"</p>"),0,AlignmentFlag::Justify);
                    onay1Text->setTextAlignment(AlignmentFlag::Center);
                    onay1Text->addStyleClass(Bootstrap::Label::Danger);
                }else{
                    auto onay1Text = vLayout->addWidget(cpp14::make_unique<WText>("Hatalı Oylama!!!!!"),0,AlignmentFlag::Justify);
                    onay1Text->setTextAlignment(AlignmentFlag::Center);
                    onay1Text->addStyleClass(Bootstrap::Label::Danger);
                }
            }
        }

        /// Soru Sahibi Adı Soyadı
        {
            User filter;
            filter.setOid(bsoncxx::oid{item.getOwner()});

            vLayout->addSpacing(WLength(20));

            auto ekleyenUser = this->mUserManager->FindOneItem(filter);
            auto text_adsoyad = vLayout->addWidget(cpp14::make_unique<WText>("Ekleyen: "+ekleyenUser.getAdSoyad()));
            text_adsoyad->addStyleClass(Bootstrap::Label::Primary);
            text_adsoyad->setAttributeValue(Style::style,Style::font::size::s12px);

            auto text_telefon = vLayout->addWidget(cpp14::make_unique<WText>("İletişim: "+ekleyenUser.getTelefon()));
            text_telefon->addStyleClass(Bootstrap::Label::Default);
            text_telefon->setAttributeValue(Style::style,Style::font::size::s11px);

            vLayout->addWidget(cpp14::make_unique<WText>("Kitap: "+item.getKitap()));

//            if( item.getKitap().empty() ){

//                Soru filter;
//                filter.setOid(item.oid().value().to_string());


//                if( ekleyenUser.getAdSoyad() == "E.Berna YANIK AKÇEHRE" ){
//                    filter.setKitap("Fatih-i Harbiye");
//                }else if( ekleyenUser.getAdSoyad() == "Deniz PİŞKİN" ){
//                    filter.setKitap("Acımak");
//                }else if( ekleyenUser.getAdSoyad() == "Ertan ALP" ){
//                    filter.setKitap("Mücella");
//                }else if( ekleyenUser.getAdSoyad() == "Şükriye PUSELİ" ){
//                    filter.setKitap("Deli Tarla");
//                }else if( ekleyenUser.getAdSoyad() == "Esra NAR" ){
//                    filter.setKitap("Deli Tarla");
//                }else if( ekleyenUser.getAdSoyad() == "İbrahim ETLİ" ){
//                    filter.setKitap("101 Deyim 101 Öykü");
//                }else if( ekleyenUser.getAdSoyad() == "Deniz GÜLER" ){
//                    filter.setKitap("Acımak");
//                }else if( ekleyenUser.getAdSoyad() == "Samet KAYA" ){
//                    filter.setKitap("Fatih-i Harbiye");
//                }else if( ekleyenUser.getAdSoyad() == "Hasan KARA" ){
//                    filter.setKitap("101 Deyim 101 Öykü");
//                }else if( ekleyenUser.getAdSoyad() == "Emine LAFAKOZ" ){
//                    filter.setKitap("Mücella");
//                }

//                if( this->UpdateItem(filter) ){

//                }
//            }
        }







    }

}

void SoruOnayPanel::initStatistic()
{


//    {
//        auto mSinavManager = new SinavManager(this->getDB());

//        auto istatistikContainer = this->Header()->addWidget(cpp14::make_unique<WContainerWidget>());
//        istatistikContainer->addStyleClass(Bootstrap::Grid::col_full_12);

//        auto rContainer = istatistikContainer->addWidget(cpp14::make_unique<WContainerWidget>());
//        rContainer->addStyleClass(Bootstrap::Grid::row);


//        QVector<std::string> sorulmusList;

//        auto sorulmusSoruList = mSinavManager->GetList(Sinav(),1000,0);
//        for( int i = 0 ; i < sorulmusSoruList.count() ; i++ ){
//            auto sorular  = sorulmusSoruList.at(i);
//            for( const auto &soruOid : sorular.soruOidList() ){
//                sorulmusList.push_back(soruOid);
//            }
//        }

//        auto List = this->GetList(Soru().setKitap("Mücella"),250,0);
//        for( const auto &item : List ){
//            if( item.isGecerli() ){
//                int sorulmaSayisi = 0;
//                for( const auto &sorulmusItem : sorulmusList ){
//                    if( item.oid().value().to_string() == sorulmusItem ){
//                        sorulmaSayisi++;
//                    }
//                }
//                auto bookNameContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
//                bookNameContainer->addStyleClass(Bootstrap::Grid::Large::col_lg_1);
//                bookNameContainer->addWidget(cpp14::make_unique<WText>("Mücella"));

//                auto SoruOidContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
//                SoruOidContainer->addStyleClass(Bootstrap::Grid::Large::col_lg_2);
//                SoruOidContainer->addWidget(cpp14::make_unique<WText>(item.oid().value().to_string() + WString(" : {1}").arg(sorulmaSayisi).toUTF8()));

//                auto SorulmaCountContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
//                SorulmaCountContainer->addStyleClass(Bootstrap::Grid::Large::col_lg_3);
//                SorulmaCountContainer->addWidget(cpp14::make_unique<WText>(WString("{1}").arg(sorulmaSayisi)));
//                SorulmaCountContainer->setPositionScheme(PositionScheme::Relative);

//                auto percentContainer = SorulmaCountContainer->addWidget(cpp14::make_unique<WContainerWidget>());
//                percentContainer->setPositionScheme(PositionScheme::Absolute);
//                percentContainer->setOffsets(0,Side::Top|Side::Left);
//                percentContainer->setHeight(WLength("100%"));

//                double dSayisi = static_cast<double>(sorulmaSayisi);

//                percentContainer->setWidth(WLength(WString("{1}%").arg(dSayisi/724.*100).toUTF8()));
//                percentContainer->setAttributeValue(Style::style,Style::background::color::color(Style::color::Red::LightCoral));
//            }
//        }


//    }









    this->setLimit(500);
    auto list = this->UpdateList();

    int onayliSoruAdedi = 0;
    int onaysizSoruAdedi = 0;
    int oylanmisSoruAdedi = 0;
    int yetersizOylamaSoruAdedi = 0;
    int iptalEdilenSoruAdedi = 0;


    for( const auto &item : qAsConst(list) ){
        auto onayList = item.getOnayStruct();

        if( item.voteCount() >= 3 ){
            oylanmisSoruAdedi++;
            if( item.isGecerli() ){
                onayliSoruAdedi++;
            }else{
                onaysizSoruAdedi++;
            }
        }else{
            yetersizOylamaSoruAdedi++;
        }

        if( item.isDeleted() ){
            iptalEdilenSoruAdedi++;
        }
    }

    {
        auto container_ = this->Header()->addWidget(cpp14::make_unique<WContainerWidget>());
        container_->setMargin(15,Side::Bottom);

        container_->addStyleClass(Bootstrap::Grid::col_full_12);
        auto hlayout = container_->setLayout(cpp14::make_unique<WHBoxLayout>());

        auto hepsitext = hlayout->addWidget(cpp14::make_unique<WText>(WString("Hepsi: {1}").arg(list.count())));
        hepsitext->setPadding(2,AllSides);
        hepsitext->setAttributeValue(Style::style,Style::background::color::color(Style::color::Grey::DarkSlateGray)+Style::color::color(Style::color::White::AliceBlue));
        hepsitext->clicked().connect([=](){
            mCurrentFilter = FILTER::NONE;
            this->UpdateList();
        });

        auto gecerliSoruText = hlayout->addWidget(cpp14::make_unique<WText>(WString("Geçerli: {1}").arg(list.count()-iptalEdilenSoruAdedi)));
        gecerliSoruText->setPadding(2,AllSides);
        gecerliSoruText->setAttributeValue(Style::style,Style::background::color::color(Style::color::Grey::SlateGray)+Style::color::color(Style::color::White::AliceBlue));
        gecerliSoruText->clicked().connect([=](){
            mCurrentFilter = FILTER::NONE;
            this->UpdateList();
        });

        auto onaylitext = hlayout->addWidget(cpp14::make_unique<WText>(WString("Onaylı: {1}").arg(onayliSoruAdedi)));
        onaylitext->setPadding(2,AllSides);
        onaylitext->setAttributeValue(Style::style,Style::background::color::color(Style::color::Green::DarkGreen)+Style::color::color(Style::color::White::AliceBlue));
        onaylitext->decorationStyle().setCursor(Cursor::PointingHand);
        onaylitext->clicked().connect([=](){
            mCurrentFilter = FILTER::ONAYLI;
            this->UpdateList();
        });

        auto onaysiztext = hlayout->addWidget(cpp14::make_unique<WText>(WString("Red: {1}").arg(onaysizSoruAdedi)));
        onaysiztext->setPadding(2,AllSides);
        onaysiztext->setAttributeValue(Style::style,Style::background::color::color(Style::color::Red::DarkRed)+Style::color::color(Style::color::White::AliceBlue));
        onaysiztext->decorationStyle().setCursor(Cursor::PointingHand);
        onaysiztext->clicked().connect([=](){
            mCurrentFilter = FILTER::ONAYSIZ;
            this->UpdateList();
        });

        auto oylanmistext = hlayout->addWidget(cpp14::make_unique<WText>(WString("Oylaması Tamamlanmış: {1}").arg(oylanmisSoruAdedi)));
        oylanmistext->setPadding(2,AllSides);
        oylanmistext->setAttributeValue(Style::style,Style::background::color::color(Style::color::Purple::RoyalBlue)+Style::color::color(Style::color::White::AliceBlue));
        oylanmistext->decorationStyle().setCursor(Cursor::PointingHand);
        oylanmistext->clicked().connect([=](){
            mCurrentFilter = FILTER::OYLAMATAMAM;
            this->UpdateList();
        });


        auto oylamadevamtext = hlayout->addWidget(cpp14::make_unique<WText>(WString("Oylaması Devam Eden: {1}").arg(yetersizOylamaSoruAdedi)));
        oylamadevamtext->setPadding(2,AllSides);
        oylamadevamtext->setAttributeValue(Style::style,Style::background::color::color(Style::color::Orange::DarkOrange)+Style::color::color(Style::color::White::AliceBlue));
        oylamadevamtext->decorationStyle().setCursor(Cursor::PointingHand);
        oylamadevamtext->clicked().connect([=](){
            mCurrentFilter = FILTER::OYLAMABEKLEYEN;
            this->UpdateList();
        });

        auto iptalEdilenText = hlayout->addWidget(cpp14::make_unique<WText>(WString("İptal: {1}").arg(iptalEdilenSoruAdedi)));
        iptalEdilenText->setPadding(2,AllSides);
        iptalEdilenText->setAttributeValue(Style::style,Style::background::color::color(Style::color::Grey::Black)+Style::color::color(Style::color::White::AliceBlue));
        iptalEdilenText->decorationStyle().setCursor(Cursor::PointingHand);
        iptalEdilenText->clicked().connect([=](){
            mCurrentFilter = FILTER::IPTAL;
            this->UpdateList();
        });
    }

    {
        auto container_ = this->Header()->addWidget(cpp14::make_unique<WContainerWidget>());
        container_->addStyleClass(Bootstrap::Grid::col_full_12);
        container_->setAttributeValue(Style::style,Style::background::color::color(Style::color::Grey::DarkSlateGray)+Style::color::color(Style::color::White::AliceBlue)+Style::font::weight::bold);
        container_->addWidget(cpp14::make_unique<WText>("Soru Onaylayanlar Listesi"));
        Soru filter;

        //        filter.UnDelete();


        auto list = this->GetList(filter,500,0);

        std::set<std::string> ekleyenList;

        for( const auto &item : list ){
            if( !item.isDeleted() ){
                ekleyenList.insert(item.getEkleyen());
            }
        }

        std::vector<User> userList;


        User userfilter;

        auto userList_ = this->getDB()->find(userfilter,100,0);

        if( userList_ ){
            for( const auto &user : userList_.value() ){
                User userItem;
                userItem.setDocumentView(user);
                userList.push_back(userItem);
            }
        }






        for( const auto &userItem : userList ){

            if( userItem.getYetki().contains(Yetki::soruonay) ){



                    int oysayisi = 0;
                    int redsayisi = 0;
                    int onaySayisi = 0;
                    int iptalEdilen = 0;
                    for( const auto &ekleyenOid : list ){

                        if( ekleyenOid.isDeleted() ){
                            iptalEdilen++;
                        }

                        for( const auto &onay : ekleyenOid.getOnayStruct() ){

                            if( onay.owner == userItem.oid().value().to_string() && !ekleyenOid.isDeleted() ){
                                oysayisi++;
                                if( onay.Onay ){
                                    onaySayisi++;
                                }else{
                                    redsayisi++;
                                }
                            }
                        }
                    }

                    auto addThumbnail = [=](const std::string &text,const std::string &color , const std::string &backColor, const std::string &bootstrap){

                        auto container = this->Header()->addWidget(cpp14::make_unique<WContainerWidget>());
                        container->setAttributeValue(Style::style,Style::color::color(color)+Style::background::color::color(backColor));
                        container->addWidget(cpp14::make_unique<WText>(text));
                        container->addStyleClass(bootstrap);


                    };


                    addThumbnail(userItem.getAdSoyad()+" "+userItem.getTelefon(),"white",Style::color::Grey::DimGray,Bootstrap::Grid::Large::col_lg_3+Bootstrap::Grid::Medium::col_md_3+Bootstrap::Grid::Small::col_sm_6+Bootstrap::Grid::ExtraSmall::col_xs_12);
                    addThumbnail("Kalan Oylama: "+std::to_string(list.size()-iptalEdilen-oysayisi),"white",(list.size()-iptalEdilen-oysayisi) > 0 ? Style::color::Red::FireBrick : Style::color::Green::DarkGreen ,Bootstrap::Grid::Large::col_lg_3+Bootstrap::Grid::Medium::col_md_3+Bootstrap::Grid::Small::col_sm_6+Bootstrap::Grid::ExtraSmall::col_xs_12);
                    addThumbnail("Oylanan: " + std::to_string(oysayisi),"white",Style::color::Grey::DarkGray,Bootstrap::Grid::Large::col_lg_2+Bootstrap::Grid::Medium::col_md_2+Bootstrap::Grid::Small::col_sm_4+Bootstrap::Grid::ExtraSmall::col_xs_12);
                    addThumbnail("Red: " + std::to_string(redsayisi),"white",Style::color::Red::FireBrick,Bootstrap::Grid::Large::col_lg_2+Bootstrap::Grid::Medium::col_md_2+Bootstrap::Grid::Small::col_sm_4+Bootstrap::Grid::ExtraSmall::col_xs_12);
                    addThumbnail("Onaylanan: " + std::to_string(onaySayisi),"white",Style::color::Green::DarkGreen,Bootstrap::Grid::Large::col_lg_2+Bootstrap::Grid::Medium::col_md_2+Bootstrap::Grid::Small::col_sm_4+Bootstrap::Grid::ExtraSmall::col_xs_12);


                    auto container = this->Header()->addWidget(cpp14::make_unique<WContainerWidget>());
                    container->addStyleClass(Bootstrap::Grid::col_full_12);
                    container->setHeight(5);

            }

        }





        auto container__ = this->Header()->addWidget(cpp14::make_unique<WContainerWidget>());
        container__->addStyleClass(Bootstrap::Grid::col_full_12);
        container__->setAttributeValue(Style::style,Style::background::color::color(Style::color::Grey::DarkSlateGray)+Style::color::color(Style::color::White::AliceBlue)+Style::font::weight::bold);
        container__->addWidget(cpp14::make_unique<WText>("Soru Ekleyenler Listesi"));
        container__->setMargin(25,Side::Top);











        std::map<std::string,int> totalSoruEkleyen;





        ///////////////////////////////////////////////////////////
        ///Onaylama Listesi
        int indexCounter = 1;
        for( const auto &userItem : userList ){

            if( userItem.getYetki().contains(Yetki::soruekle) ){
                bool ekli = false;
                for( const auto &item : ekleyenList ){
                    int soruCount = 0;
                    int iptalEdilenSoruCount = 0;
                    int onaylanmis = 0;
                    int redEdilmis = 0;
                    for( const auto &ekleyenOid : list ){
                        if( ekleyenOid.getEkleyen() == item ){
                            soruCount++;
                            if( ekleyenOid.isDeleted() ){
                                iptalEdilenSoruCount++;
                            }
                            if( ekleyenOid.isGecerli() ){
                                onaylanmis++;
                            }
                            if( ekleyenOid.redCount() ){
                                redEdilmis++;
                            }
                        }
                    }
                    if( item == userItem.oid().value().to_string() ){
                        totalSoruEkleyen.insert(std::make_pair(userItem.getAdSoyad(),soruCount));

                        auto container = this->Header()->addWidget(cpp14::make_unique<WContainerWidget>());
                        container->addStyleClass(Bootstrap::Grid::col_full_12);
                        container->setHeight(20);
                        if( soruCount < 25 && soruCount > 0 ){
                            container->setAttributeValue(Style::style,Style::background::color::color(Style::color::Orange::DarkOrange)+Style::color::color(Style::color::White::AliceBlue)+Style::font::weight::bold);
                            container->addWidget(cpp14::make_unique<WText>(std::to_string(indexCounter)+WString(". {1}-{2} : {3} Adet  EKSİK!  iptal:{4} onaylı:{5} red:{6}")
                                                                           .arg(userItem.getAdSoyad())
                                                                           .arg(userItem.getTelefon())
                                                                           .arg(soruCount)
                                                                           .arg(iptalEdilenSoruCount)
                                                                           .arg(onaylanmis)
                                                                           .arg(redEdilmis)));
                        }else if( soruCount >= 25 ){
                            container->setAttributeValue(Style::style,Style::background::color::color(Style::color::Green::DarkGreen)+Style::color::color(Style::color::White::AliceBlue)+Style::font::weight::bold);
                            container->addWidget(cpp14::make_unique<WText>(std::to_string(indexCounter)+WString(". {1}-{2} : {3} Adet  Tamamlandı  iptal:{4} onaylı:{5} red:{6}")
                                                                           .arg(userItem.getAdSoyad())
                                                                           .arg(userItem.getTelefon())
                                                                           .arg(soruCount)
                                                                           .arg(iptalEdilenSoruCount)
                                                                           .arg(onaylanmis)
                                                                           .arg(redEdilmis)));
                        }else{

                        }

                        if( soruCount > 0 ){
                            ekli = true;
                        }
                        container->setContentAlignment(AlignmentFlag::Left);
                        container->setMargin(2,Side::Top);
                    }
                }

                if( !ekli ){
                    auto container = this->Header()->addWidget(cpp14::make_unique<WContainerWidget>());
                    container->addStyleClass(Bootstrap::Grid::col_full_12);
                    container->setHeight(20);
                    container->setContentAlignment(AlignmentFlag::Left);
                    container->setMargin(2,Side::Top);
                    container->setAttributeValue(Style::style,Style::background::color::color(Style::color::Red::DarkRed)+Style::color::color(Style::color::White::AliceBlue)+Style::font::weight::bold);
                    container->addWidget(cpp14::make_unique<WText>(std::to_string(indexCounter)+WString(". {1}-{2} : {3} Adet SORU YOK").arg(userItem.getAdSoyad()).arg(userItem.getTelefon()).arg(0)));

                }

                indexCounter++;
            }

        }




        // Kitap Soru Dağılımı
        {

            Soru filter;

            filter.setKitap("Deli Tarla");
            filter.UnDelete();
            {
                auto sayi = this->countItem(filter);
                auto container = this->Header()->addWidget(cpp14::make_unique<WContainerWidget>());
                container->addStyleClass(Bootstrap::Grid::col_full_12);
                container->setHeight(20);
                container->setContentAlignment(AlignmentFlag::Left);
                container->setMargin(2,Side::Top);
                container->setAttributeValue(Style::style,Style::background::color::color(Style::color::Red::DarkRed)+Style::color::color(Style::color::White::AliceBlue)+Style::font::weight::bold);
                container->addWidget(cpp14::make_unique<WText>(WString("{1}-{2}").arg(filter.getKitap()).arg(sayi)));
            }

            filter.setKitap("Mücella");
            {
                auto sayi = this->countItem(filter);
                auto container = this->Header()->addWidget(cpp14::make_unique<WContainerWidget>());
                container->addStyleClass(Bootstrap::Grid::col_full_12);
                container->setHeight(20);
                container->setContentAlignment(AlignmentFlag::Left);
                container->setMargin(2,Side::Top);
                container->setAttributeValue(Style::style,Style::background::color::color(Style::color::Red::DarkRed)+Style::color::color(Style::color::White::AliceBlue)+Style::font::weight::bold);
                container->addWidget(cpp14::make_unique<WText>(WString("{1}-{2}").arg(filter.getKitap()).arg(sayi)));
            }

            filter.setKitap("101 Deyim 101 Öykü");
            {
                auto sayi = this->countItem(filter);
                auto container = this->Header()->addWidget(cpp14::make_unique<WContainerWidget>());
                container->addStyleClass(Bootstrap::Grid::col_full_12);
                container->setHeight(20);
                container->setContentAlignment(AlignmentFlag::Left);
                container->setMargin(2,Side::Top);
                container->setAttributeValue(Style::style,Style::background::color::color(Style::color::Red::DarkRed)+Style::color::color(Style::color::White::AliceBlue)+Style::font::weight::bold);
                container->addWidget(cpp14::make_unique<WText>(WString("{1}-{2}").arg(filter.getKitap()).arg(sayi)));
            }

            filter.setKitap("Acımak");
            {
                auto sayi = this->countItem(filter);
                auto container = this->Header()->addWidget(cpp14::make_unique<WContainerWidget>());
                container->addStyleClass(Bootstrap::Grid::col_full_12);
                container->setHeight(20);
                container->setContentAlignment(AlignmentFlag::Left);
                container->setMargin(2,Side::Top);
                container->setAttributeValue(Style::style,Style::background::color::color(Style::color::Red::DarkRed)+Style::color::color(Style::color::White::AliceBlue)+Style::font::weight::bold);
                container->addWidget(cpp14::make_unique<WText>(WString("{1}-{2}").arg(filter.getKitap()).arg(sayi)));
            }

            filter.setKitap("Fatih-i Harbiye");
            {
                auto sayi = this->countItem(filter);
                auto container = this->Header()->addWidget(cpp14::make_unique<WContainerWidget>());
                container->addStyleClass(Bootstrap::Grid::col_full_12);
                container->setHeight(20);
                container->setContentAlignment(AlignmentFlag::Left);
                container->setMargin(2,Side::Top);
                container->setAttributeValue(Style::style,Style::background::color::color(Style::color::Red::DarkRed)+Style::color::color(Style::color::White::AliceBlue)+Style::font::weight::bold);
                container->addWidget(cpp14::make_unique<WText>(WString("{1}-{2}").arg(filter.getKitap()).arg(sayi)));
            }



        }




    }


}
