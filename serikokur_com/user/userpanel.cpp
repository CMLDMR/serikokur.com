#include "userpanel.h"
#include "root/css.h"
#include "root/iletisimformu.h"
#include "iletisimpanel.h"
#include "basvuruyonetimpanel.h"
#include "soruyonetimpanel.h"
#include "soruonaypanel.h"


UserPanel::UserPanel(SerikBLDCore::DB *_mDB, const User _mUser)
    : UserManager(_mDB),
      mCurrentUser( new User(_mUser))
{

    this->setMargin(50,Side::Top);

    this->Content()->setMargin(75,Side::Bottom);

    this->Header()->addStyleClass(Bootstrap::ContextualBackGround::bg_danger);



    {
        auto container = this->Header()->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_2+Bootstrap::Grid::Medium::col_md_2+Bootstrap::Grid::Small::col_sm_3+Bootstrap::Grid::ExtraSmall::col_xs_4);
        auto vlayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());
        auto btn = vlayout->addWidget(cpp14::make_unique<WPushButton>("Ana Menü"),0,AlignmentFlag::Left);
        btn->addStyleClass(Bootstrap::Button::Primary);
        //        container->addStyleClass(Bootstrap::Button::info);
        //        container->decorationStyle().setCursor(Cursor::PointingHand);
        //        container->setHeight(75);
        btn->clicked().connect([=](){
            this->initMainPanel();
        });
    }

    {
        auto container = this->Header()->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_10+Bootstrap::Grid::Medium::col_md_10+Bootstrap::Grid::Small::col_sm_9+Bootstrap::Grid::ExtraSmall::col_xs_8);
        auto vlayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());
        vlayout->addWidget(cpp14::make_unique<WPushButton>(mCurrentUser->getAdSoyad()),0,AlignmentFlag::Right)->addStyleClass(Bootstrap::Button::Danger);
        //        container->addStyleClass(Bootstrap::Button::Danger);
        //        container->setHeight(75);
    }

    this->initMainPanel();

}

void UserPanel::onList(const QVector<User> *mlist)
{
    mUserList->setList(mlist);
}

User *UserPanel::CurrentUser() const
{
    return mCurrentUser;
}

void UserPanel::initMainPanel()
{

    this->Content()->clear();

    // Giriş Buttonları // Admin Yetkisi
    if( this->mCurrentUser->getYetki().contains(Yetki::admin) ){
        auto container = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_2+Bootstrap::Grid::Medium::col_md_3+Bootstrap::Grid::Small::col_sm_4+Bootstrap::Grid::ExtraSmall::col_xs_6);
        container->addWidget(cpp14::make_unique<WText>("Kullanıcı Yönetimi"))->addStyleClass(CSS::Button::LightBlueGrad);
        container->clicked().connect([=](){
            this->Content()->clear();
            mUserList = this->Content()->addWidget(cpp14::make_unique<UserList>());
            mUserList->UserSaved().connect([=]( const User &user){
                auto ins = this->InsertItem(user);
                if( ins.size() ){
                    this->informDialog("Kayıt Başarılı");
                    this->UpdateList();
                }
            });

            mUserList->DeleteReq().connect([=]( const std::string &oid){

                User filter;
                filter.setOid(oid);
                filter.setDisable();

                if( this->UpdateItem(filter) ){
                    this->UpdateList();
                }else{
                    this->warnDialog("DeAktif İşlemi Başarısız. " + this->getLastError().toStdString());
                }

            });

            mUserList->RecoverReq().connect([=]( const std::string &oid){

                User filter;
                filter.setOid(oid);
                filter.setDisable(false);

                if( this->UpdateItem(filter) ){
                    this->UpdateList();
                }else{
                    this->warnDialog("Aktif Etme İşlemi Başarısız");
                }

            });

            mUserList->RemoveYetki().connect([=](const std::string &yetki, const std::string &oid){

                User filter;
                filter.setOid(oid);
                auto pul = this->pullValue(filter,SKey::User::yetki,yetki);
                if( pul.value().modified_count() ){
                    this->UpdateList();
                }else{
                    this->warnDialog("Yetki Kaldırma İşlemi Başarısız");
                }

            });

            mUserList->AddYetki().connect([=](const std::string &yetki, const std::string &oid){

                User filter;
                filter.setOid(oid);
                auto pul = this->pushValue(filter,SKey::User::yetki,yetki);
                if( pul.value().modified_count() ){
                    this->UpdateList();
                }else{
                    this->warnDialog("Yetki Ekleme İşlemi Başarısız");
                }

            });


            this->UpdateList();
        });

    }



    //    // SoruGörme Yetkisi
    //    if( this->mCurrentUser->getYetki().contains(Yetki::sorulist) || this->mCurrentUser->getYetki().contains(Yetki::admin) ){
    //        auto container = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
    //        container->addStyleClass(Bootstrap::Grid::Large::col_lg_2+Bootstrap::Grid::Medium::col_md_3+Bootstrap::Grid::Small::col_sm_4+Bootstrap::Grid::ExtraSmall::col_xs_6);
    //        container->addWidget(cpp14::make_unique<WText>("Sorular"))->addStyleClass(CSS::Button::LightBlueGrad);
    //        container->clicked().connect([=](){
    //            this->Content()->clear();

    //        });
    //    }


    // SoruEkleme Yetkisi
    if( this->mCurrentUser->getYetki().contains(Yetki::soruekle) || this->mCurrentUser->getYetki().contains(Yetki::admin) ){
        auto container = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_2+Bootstrap::Grid::Medium::col_md_3+Bootstrap::Grid::Small::col_sm_4+Bootstrap::Grid::ExtraSmall::col_xs_6);
        container->addWidget(cpp14::make_unique<WText>("Soru Ekle/Değiştir"))->addStyleClass(CSS::Button::LightBlueGrad);
        container->clicked().connect([=](){
            this->Content()->clear();
            this->Content()->addWidget(cpp14::make_unique<SoruYonetimPanel>(this->getDB(),this->CurrentUser()));

        });
    }

    // SoruOnaylama Yetkisi
    if( this->mCurrentUser->getYetki().contains(Yetki::soruonay) || this->mCurrentUser->getYetki().contains(Yetki::admin) ){
        auto container = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_2+Bootstrap::Grid::Medium::col_md_3+Bootstrap::Grid::Small::col_sm_4+Bootstrap::Grid::ExtraSmall::col_xs_6);
        container->addWidget(cpp14::make_unique<WText>("Soru Onaylama"))->addStyleClass(CSS::Button::LightBlueGrad);
        container->clicked().connect([=](){
            this->Content()->clear();
            LOG << "Current User: "<<this->CurrentUser()->oid()->to_string() ;
            this->Content()->addWidget(cpp14::make_unique<SoruOnayPanel>(this->getDB(),this->CurrentUser()));
        });
    }

    // Başvurular Yetkisi
    if( this->mCurrentUser->getYetki().contains(Yetki::basvuru) || this->mCurrentUser->getYetki().contains(Yetki::admin) ){
        auto container = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_2+Bootstrap::Grid::Medium::col_md_3+Bootstrap::Grid::Small::col_sm_4+Bootstrap::Grid::ExtraSmall::col_xs_6);
        container->addWidget(cpp14::make_unique<WText>("Başvurular"))->addStyleClass(CSS::Button::LightBlueGrad);
        container->clicked().connect([=](){
            this->Content()->clear();
            this->Content()->addWidget(cpp14::make_unique<BasvuruYonetimPanel>(this->getDB()));
        });
    }

    // Mesajlar Yetkisi
    if( this->mCurrentUser->getYetki().contains(Yetki::mesajlar) || this->mCurrentUser->getYetki().contains(Yetki::admin) ){
        auto container = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_2+Bootstrap::Grid::Medium::col_md_3+Bootstrap::Grid::Small::col_sm_4+Bootstrap::Grid::ExtraSmall::col_xs_6);
        container->addWidget(cpp14::make_unique<WText>("Mesajlar"))->addStyleClass(CSS::Button::LightBlueGrad);
        container->clicked().connect([=](){
            this->Content()->clear();
            this->Content()->addWidget(cpp14::make_unique<IletisimPanel>(this->getDB()));
        });
    }


}

UserList::UserList() : ContainerWidget("Kullanıcı Listesi")
{
    this->addStyleClass(Bootstrap::Grid::col_full_12);
    this->addStyleClass("yeniKullanici");
    //    this->setHeight(350);
    this->addStyleClass(CSSStyle::Radius::radius3px+CSSStyle::Shadows::shadow8px);
    this->setMargin(15,Side::Bottom|Side::Top);

    auto yeniEkleBtn = this->Footer()->addWidget(cpp14::make_unique<WPushButton>("Yeni Kullanıcı Ekle+"));
    yeniEkleBtn->addStyleClass(Bootstrap::Button::Danger);
    yeniEkleBtn->setMargin(50,Side::Top);

    yetkiList.clear();

    yeniEkleBtn->clicked().connect([=](){

        auto mDialog = this->createDialog("Yeni Kullanıcı Ekle");


        auto adsoyadLineEdit = mDialog->contents()->addWidget(cpp14::make_unique<WLineEdit>());
        adsoyadLineEdit->setPlaceholderText("Ad Soyad Giriniz");

        auto telefonLineEdit = mDialog->contents()->addWidget(cpp14::make_unique<WLineEdit>());
        telefonLineEdit->setPlaceholderText("Telefon Giriniz");

        auto passLineEdit = mDialog->contents()->addWidget(cpp14::make_unique<WLineEdit>());
        passLineEdit->setPlaceholderText("Şifre Tanımlayınız");


        auto yetkiComboBox = mDialog->contents()->addWidget(cpp14::make_unique<WComboBox>());
        yetkiComboBox->addItem(Yetki::admin);
        yetkiComboBox->addItem(Yetki::sorulist);
        yetkiComboBox->addItem(Yetki::soruekle);
        yetkiComboBox->addItem(Yetki::soruonay);
        yetkiComboBox->addItem(Yetki::basvuru);
        yetkiComboBox->addItem(Yetki::mesajlar);




        auto yetkiEkle = mDialog->contents()->addWidget(cpp14::make_unique<WPushButton>("Ekle"));



        auto yetkiListContainer = mDialog->contents()->addWidget(cpp14::make_unique<WContainerWidget>());

        yetkiEkle->clicked().connect([=](){

            std::string _yetki = yetkiComboBox->currentText().toUTF8();
            bool exist = false;

            for( const auto &item : yetkiList ){
                if( item == _yetki ){
                    exist = true;
                    break;
                }
            }


            if( !exist ){
                yetkiList.push_back(yetkiComboBox->currentText().toUTF8());
                yetkiListContainer->clear();
                for( auto item : yetkiList ){
                    yetkiListContainer->addWidget(cpp14::make_unique<WText>(item));
                    yetkiListContainer->addWidget(cpp14::make_unique<WBreak>());
                }
            }

        });


        auto saveBtn = mDialog->footer()->addWidget(cpp14::make_unique<WPushButton>("Kaydet"));
        saveBtn->addStyleClass(Bootstrap::Button::Primary);

        saveBtn->clicked().connect([=](){

            User mUser;
            mUser.setAdSoyad(adsoyadLineEdit->text().toUTF8());
            mUser.setPassword(passLineEdit->text().toUTF8());
            mUser.setTelefon(telefonLineEdit->text().toUTF8());
            mUser.addYetki(yetkiList);

            _userSaved.emit(mUser);

            this->removeDialog(mDialog);

        });



    });
}



Signal<User> &UserList::UserSaved()
{
    return _userSaved;
}

Signal<std::string> &UserList::DeleteReq()
{
    return _deleteReq;
}

Signal<std::string> &UserList::RecoverReq()
{
    return _recoverReq;

}

Signal<std::string, std::string> &UserList::RemoveYetki()
{
    return _removeYetki;
}

Signal<std::string, std::string> &UserList::AddYetki()
{
    return _addYetki;
}



void UserList::setList(const QVector<User> *mList)
{
    this->Content()->clear();

    for( const auto &user : *mList ){
        auto container_ = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
        container_->addStyleClass(Bootstrap::Grid::Large::col_lg_2+Bootstrap::Grid::Medium::col_md_2+Bootstrap::Grid::Small::col_sm_3+Bootstrap::Grid::ExtraSmall::col_xs_4);
        container_->setMargin(20,Side::Top);
        container_->setOverflow(Overflow::Hidden);


        auto container = container_->addWidget(cpp14::make_unique<WContainerWidget>());

        if( user.isDisabled() ){
            container_->setPositionScheme(PositionScheme::Relative);
            auto _container = container_->addWidget(cpp14::make_unique<WContainerWidget>());
            _container->setPositionScheme(PositionScheme::Absolute);
            //            _container->setWidth(WLength("100%"));
            //            _container->setHeight(WLength("100%"));
            _container->setZIndex(100);
            _container->setOffsets(10,Side::Top|Side::Bottom);
            _container->setOffsets(20,Side::Left|Side::Right);

            _container->setAttributeValue(Style::style,Style::background::color::rgba(255,0,0)
                                          +Style::color::color(Style::color::White::AliceBlue));
            auto _vLayout = _container->setLayout(cpp14::make_unique<WVBoxLayout>());
            _vLayout->addStretch(1);
            auto text = _vLayout->addWidget(cpp14::make_unique<WText>("Giriş Kapalı"));
            text->setAttributeValue(Style::style,Style::font::size::s20px);
            auto enableBtn = _vLayout->addWidget(cpp14::make_unique<WPushButton>("Aktif Et"));
            enableBtn->addStyleClass(Bootstrap::Button::Primary);
            text->setAttributeValue(Style::dataoid,user.oid().value().to_string());

            enableBtn->clicked().connect([=](){
                _recoverReq.emit(text->attributeValue(Style::dataoid).toUTF8());
            });

            _vLayout->addStretch(1);

        }




        container->addStyleClass(CSSStyle::Radius::radius3px+CSSStyle::Shadows::shadow8px);
        container->setAttributeValue(Style::style,Style::background::color::rgba(this->getRandom(50,75),this->getRandom(75,100),this->getRandom(75,125))
                                     +Style::color::color(Style::color::White::AliceBlue));

        auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());


        vLayout->addWidget(cpp14::make_unique<WText>(user.getTelefon()),0,AlignmentFlag::Center);
        vLayout->addWidget(cpp14::make_unique<WText>(user.getAdSoyad()),0,AlignmentFlag::Center);

        vLayout->addWidget(cpp14::make_unique<WText>("<b>-------Yetkiler-------</b>",TextFormat::UnsafeXHTML),0,AlignmentFlag::Center);


        for( const auto &item : user.getYetki() ){
            auto text = vLayout->addWidget(cpp14::make_unique<WText>(item));
            text->decorationStyle().setCursor(Cursor::PointingHand);
            text->clicked().connect([=](){
               _removeYetki.emit(item,user.oid().value().to_string());
            });
        }

        if( !user.isDisabled() ){
            auto deltext = vLayout->addWidget(cpp14::make_unique<WText>("<b> DeAktif </b>"));
            deltext->addStyleClass(Bootstrap::Button::Danger);
            deltext->decorationStyle().setCursor(Cursor::PointingHand);
            deltext->setAttributeValue(Style::dataoid,user.oid().value().to_string());
            deltext->clicked().connect([=](){
                _deleteReq.emit(deltext->attributeValue(Style::dataoid).toUTF8());
            });
            deltext->setMargin(15,Side::Top|Side::Bottom);
        }

        auto yetkiler = UserManager::Yetkiler();
        for( const auto &item : yetkiler ){

            bool exist = false;
            for( const auto &_item : user.getYetki() ){
                if( item == _item ){
                    exist = true;
                    break;
                }
            }


            if( !exist ){
                auto text = vLayout->addWidget(cpp14::make_unique<WText>(item));
                text->decorationStyle().setCursor(Cursor::PointingHand);
                text->addStyleClass(Bootstrap::Label::Success);
                text->setAttributeValue(Style::style,Style::font::size::s12px);
                text->clicked().connect([=](){
                   _addYetki.emit(item,user.oid().value().to_string());
                });
            }

        }


    }
}
