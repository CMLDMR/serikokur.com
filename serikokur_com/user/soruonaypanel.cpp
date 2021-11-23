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
            if( item.voteCount() >= 3 && ( item.redCount() > item.onayCount() ) ){
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
        default:
            break;
        }
    }


    for( const auto &item : newList ){


        //        LOG << item.voteCount() << LOGEND;




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
        }




    }

}

void SoruOnayPanel::initStatistic()
{

    this->setLimit(250);
    auto list = this->UpdateList();

    int onayliSoruAdedi = 0;
    int onaysizSoruAdedi = 0;
    int oylanmisSoruAdedi = 0;
    int yetersizOylamaSoruAdedi = 0;


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
    }

    {
        auto container_ = this->Header()->addWidget(cpp14::make_unique<WContainerWidget>());
        container_->setMargin(15,Side::Bottom);

        container_->addStyleClass(Bootstrap::Grid::col_full_12);
        auto hlayout = container_->setLayout(cpp14::make_unique<WHBoxLayout>());

        auto hepsitext = hlayout->addWidget(cpp14::make_unique<WText>(WString("<h5>Hepsi: {1}</h5>").arg(list.count())));
        hepsitext->addStyleClass(Bootstrap::Label::Default);
        hepsitext->decorationStyle().setCursor(Cursor::PointingHand);
        hepsitext->clicked().connect([=](){
            mCurrentFilter = FILTER::NONE;
            this->UpdateList();
        });

        auto onaylitext = hlayout->addWidget(cpp14::make_unique<WText>(WString("<h5>Onaylı: {1}</h5>").arg(onayliSoruAdedi)));
        onaylitext->addStyleClass(Bootstrap::Label::Success);
        onaylitext->decorationStyle().setCursor(Cursor::PointingHand);
        onaylitext->clicked().connect([=](){
            mCurrentFilter = FILTER::ONAYLI;
            this->UpdateList();
        });

        auto onaysiztext = hlayout->addWidget(cpp14::make_unique<WText>(WString("<h5>Onaysız: {1}</h5>").arg(onaysizSoruAdedi)));
        onaysiztext->addStyleClass(Bootstrap::Label::Danger);
        onaysiztext->decorationStyle().setCursor(Cursor::PointingHand);
        onaysiztext->clicked().connect([=](){
            mCurrentFilter = FILTER::ONAYSIZ;
            this->UpdateList();
        });

        auto oylanmistext = hlayout->addWidget(cpp14::make_unique<WText>(WString("<h5>Oylaması Tamamlanmış: {1}</h5>").arg(oylanmisSoruAdedi)));
        oylanmistext->addStyleClass(Bootstrap::Label::info);
        oylanmistext->decorationStyle().setCursor(Cursor::PointingHand);
        oylanmistext->clicked().connect([=](){
            mCurrentFilter = FILTER::OYLAMATAMAM;
            this->UpdateList();
        });


        auto oylamadevamtext = hlayout->addWidget(cpp14::make_unique<WText>(WString("<h5>Oylaması Devam Eden: {1}</h5>").arg(yetersizOylamaSoruAdedi)));
        oylamadevamtext->addStyleClass(Bootstrap::Label::Warning);
        oylamadevamtext->decorationStyle().setCursor(Cursor::PointingHand);
        oylamadevamtext->clicked().connect([=](){
            mCurrentFilter = FILTER::OYLAMABEKLEYEN;
            this->UpdateList();
        });
    }

    {
        auto container_ = this->Header()->addWidget(cpp14::make_unique<WContainerWidget>());
        container_->addStyleClass(Bootstrap::Grid::col_full_12);
        container_->setAttributeValue(Style::style,Style::background::color::color(Style::color::Grey::DarkSlateGray)+Style::color::color(Style::color::White::AliceBlue)+Style::font::weight::bold);
        container_->addWidget(cpp14::make_unique<WText>("Soru Ekleyenler Listesi"));
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

        std::map<std::string,int> totalSoruEkleyen;


        int indexCounter = 1;
        for( const auto &userItem : userList ){

            if( userItem.getYetki().contains(Yetki::soruekle) ){
                bool ekli = false;
                for( const auto &item : ekleyenList ){
                    int soruCount = 0;
                    for( const auto &ekleyenOid : list ){
                        if( ekleyenOid.getEkleyen() == item ){
                            soruCount++;
                        }
                    }
                    if( item == userItem.oid().value().to_string() ){
                        totalSoruEkleyen.insert(std::make_pair(userItem.getAdSoyad(),soruCount));

                        auto container = this->Header()->addWidget(cpp14::make_unique<WContainerWidget>());
                        container->addStyleClass(Bootstrap::Grid::col_full_12);
                        container->setHeight(20);
                        if( soruCount < 25 && soruCount > 0 ){
                            container->setAttributeValue(Style::style,Style::background::color::color(Style::color::Orange::DarkOrange)+Style::color::color(Style::color::White::AliceBlue)+Style::font::weight::bold);
                            container->addWidget(cpp14::make_unique<WText>(std::to_string(indexCounter)+WString(". {1}-{2} : {3} Adet  EKSİK!").arg(userItem.getAdSoyad()).arg(userItem.getTelefon()).arg(soruCount)));
                        }else if( soruCount >= 25 ){
                            container->setAttributeValue(Style::style,Style::background::color::color(Style::color::Green::DarkGreen)+Style::color::color(Style::color::White::AliceBlue)+Style::font::weight::bold);
                            container->addWidget(cpp14::make_unique<WText>(std::to_string(indexCounter)+WString(". {1}-{2} : {3} Adet Tamamlandı").arg(userItem.getAdSoyad()).arg(userItem.getTelefon()).arg(soruCount)));
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

//        for( const auto &item : totalSoruEkleyen ){
//            LOG << item.first << " " << item.second << LOGEND;

//        }




    }


}
