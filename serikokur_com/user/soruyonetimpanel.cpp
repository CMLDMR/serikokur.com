#include "soruyonetimpanel.h"



SoruYonetimPanel::SoruYonetimPanel(DB *_mDB, User *_mUser)
    :SoruManager(_mDB,_mUser),mUserManager(new UserManager(_mDB))
{

    this->setLimit(100);
    {
        this->Header()->setMargin(25,Side::Top|Side::Bottom);
        auto container = this->Header()->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_6+Bootstrap::Grid::Medium::col_md_6+Bootstrap::Grid::Small::col_sm_6+Bootstrap::Grid::ExtraSmall::col_xs_6);
        auto ekleBtn = container->addWidget(cpp14::make_unique<WPushButton>("Listeyi Güncelle"));
        ekleBtn->addStyleClass(Bootstrap::Button::Primary);
        ekleBtn->clicked().connect([=](){
            Soru filter;
            filter.setOwner(this->CurrentUser()->oid().value().to_string());
            this->UpdateList(filter);
        });
    }

    {
        this->Header()->setMargin(25,Side::Top|Side::Bottom);
        auto container = this->Header()->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_6+Bootstrap::Grid::Medium::col_md_6+Bootstrap::Grid::Small::col_sm_6+Bootstrap::Grid::ExtraSmall::col_xs_6);
        auto ekleBtn = container->addWidget(cpp14::make_unique<WPushButton>("Yeni Soru Ekle"));
        ekleBtn->addStyleClass(Bootstrap::Button::Primary);
        ekleBtn->clicked().connect([=](){


//            QString metin = "Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.";
//            QString metin1 = "It is a long established fact that a reader will be distracted by the readable content of a page when looking at its layout. The point of using Lorem Ipsum is that it has a more-or-less normal distribution of letters, as opposed to using 'Content here, content here', making it look like readable English. Many desktop publishing packages and web page editors now use Lorem Ipsum as their default model text, and a search for 'lorem ipsum' will uncover many web sites still in their infancy. Various versions have evolved over the years, sometimes by accident, sometimes on purpose (injected humour and the like).";
//            QString metin2 = "There are many variations of passages of Lorem Ipsum available, but the majority have suffered alteration in some form, by injected humour, or randomised words which don't look even slightly believable. If you are going to use a passage of Lorem Ipsum, you need to be sure there isn't anything embarrassing hidden in the middle of text. All the Lorem Ipsum generators on the Internet tend to repeat predefined chunks as necessary, making this the first true generator on the Internet. It uses a dictionary of over 200 Latin words, combined with a handful of model sentence structures, to generate Lorem Ipsum which looks reasonable. The generated Lorem Ipsum is therefore always free from repetition, injected humour, or non-characteristic words etc";

//            QStringList metinList = metin2.split(" ");
//            metinList += metin.split(" ");
//            metinList += metin1.split(" ");

//            LOG << "Kelime Sayısı: " << metinList.count();

//            for( int i = 0 ; i < 250 ; i++ ){

//                Soru soru;

//                int soruKelimeSayisi = this->getRandom(20,75);

//                QString soruMetin;
//                for( int j = 0 ; j < soruKelimeSayisi ; j++ ){
//                    soruMetin += metinList.at(this->getRandom(0,metinList.count()-1)) + " ";
//                }

//                soru.setSoru(soruMetin.toStdString());
//                soru.setOwner(this->CurrentUser()->oid().value().to_string());

//                QStringList cevapList;

//                int cevapIndex = this->getRandom(1,8);
//                for( int j = 1 ; j <= 8 ; j++ ){
//                    if( j == cevapIndex ){
//                        soru.addCevap("Cevap",cevapIndex);
//                    }else{
//                        soru.addCevap(metinList.at(this->getRandom(0,metinList.count()-1)).toStdString(),j);
//                    }
//                }

//                soru.setCevapIndex(cevapIndex);
//                soru.setZorluk(this->getRandom(1,5));

//                if( this->InsertItem(soru).size() ){
//                    LOG << "Soru Eklendi " << i;
//                }else{
//                    LOG << "Eklenemedi. " << this->getLastError().toStdString();
//                }


////                std::this_thread::sleep_for(2000ms);
//            }






            this->Content()->clear();
            this->Content()->setContentAlignment(AlignmentFlag::Center);
            auto soruWidget = this->Content()->addWidget(cpp14::make_unique<SoruEkleWidget>(_mUser));
            soruWidget->setMaximumSize(1280,WLength::Auto);


            soruWidget->SaveSignal().connect([=](){


                Soru soru;
                soru.setDocumentView(soruWidget->getSoru().view());

                soru.setOwner(this->CurrentUser()->oid().value().to_string());


                if( this->InsertItem(soru).size() ){
                    this->informDialog("Soru Başarılı Bir Şekilde Eklendi");
                    Soru filter;
                    filter.setOwner(this->CurrentUser()->oid().value().to_string());

                    this->UpdateList(filter);
                }else{
                    this->criticDialog("Soru Eklenemedi: <b>" + this->getLastError().toStdString()+"</b>");
                }

            });



        });
    }
    Soru filter;
    filter.setOwner(this->CurrentUser()->oid().value().to_string());
    this->UpdateList(filter);
}

void SoruYonetimPanel::onList(const QVector<Soru> *mlist)
{

    this->Content()->clear();


    int soruCounter = 0;
    WContainerWidget* rContainer;
    for( const auto &item : *mlist ){

        if( soruCounter%4 == 0 ){
            rContainer = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
            rContainer->addStyleClass(Bootstrap::Grid::row);
            rContainer->addStyleClass(CSSStyle::Shadows::shadow8px+CSSStyle::Radius::radius3px);
            rContainer->setMargin(25,Side::Bottom|Side::Top);

        }

        soruCounter++;
        auto  container_ = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        container_->setMargin(15,Side::Bottom|Side::Top);

        container_->addStyleClass(Bootstrap::Grid::Large::col_lg_3+
                                  Bootstrap::Grid::Medium::col_md_6+
                                  Bootstrap::Grid::Small::col_sm_12+
                                  Bootstrap::Grid::ExtraSmall::col_xs_12);

        container_->setPositionScheme(PositionScheme::Relative);
        {



                auto editContainer = container_->addWidget(cpp14::make_unique<WContainerWidget>());
                editContainer->setPositionScheme(PositionScheme::Absolute);
                editContainer->setOffsets(0,Side::Right);
                editContainer->setOffsets(-20,Side::Top);
                auto hLayout = editContainer->setLayout(cpp14::make_unique<WHBoxLayout>());

            if( !item.isDeleted() ){
                auto editBtn = hLayout->addWidget(cpp14::make_unique<WText>("Düzenle"));
                editBtn->addStyleClass(Bootstrap::Button::Success);
                editBtn->setInline(true);
                editBtn->setPadding(5,Side::Left|Side::Right);
                editBtn->decorationStyle().setCursor(Cursor::PointingHand);

                editBtn->clicked().connect([=](){

                    this->Content()->clear();
                    this->Content()->setContentAlignment(AlignmentFlag::Center);
                    auto soruWidget = this->Content()->addWidget(cpp14::make_unique<SoruEkleWidget>(this->CurrentUser(),false));
                    soruWidget->setMaximumSize(1280,WLength::Auto);
                    soruWidget->setCurrentSoru(item);



                    soruWidget->UpdateSignal().connect([=](){
                        Soru soru;
                        soru.setDocumentView(soruWidget->getSoru().view());
                        soru.setOwner(this->CurrentUser()->oid().value().to_string());
                        if( this->UpdateItem(soru) ){
                            this->informDialog("Soru Başarılı Bir Şekilde Güncellendi");
                            Soru filter;
                            filter.setOwner(this->CurrentUser()->oid().value().to_string());
                            this->UpdateList(filter);
                        }else{
                            this->criticDialog("Soru Güncellenemedi: <b>" + this->getLastError().toStdString()+"</b>");
                        }
                    });
                });
            }






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


                deletedContainer->addWidget(cpp14::make_unique<WBreak>());
                auto silBtn = deletedContainer->addWidget(cpp14::make_unique<WPushButton>("Geri Al"));
                silBtn->addStyleClass(Bootstrap::Button::Primary);
//                silBtn->setPadding(5,Side::Left|Side::Right);

                silBtn->decorationStyle().setCursor(Cursor::PointingHand);

                silBtn->clicked().connect([=](){

                    auto confirmDialog = askConfirm("Geri Almak İstediğinize Eminmisiniz?");

                    confirmDialog->clicked().connect([=](){

                        Soru filter;
                        filter.setOid(item.oid().value().to_string());
                        filter.UnDelete();

                        if( this->UpdateItem(filter) ){
//                            this->informDialog("Başarılı Bir Şekilde Soru Geri Alında!");
                            filter.clear();
                            filter.setOwner(this->CurrentUser()->oid().value().to_string());
                            this->UpdateList(filter);
                        }else{
                            this->warnDialog("<p>Bir Hata Oluştu.</p><p>Error: " + this->getLastError().toStdString()+"</p>");
                        }

                    });

                });
            }else{
                auto silBtn = hLayout->addWidget(cpp14::make_unique<WText>("İptal Et"));
                silBtn->addStyleClass(Bootstrap::Button::Danger);
                silBtn->setPadding(5,Side::Left|Side::Right);
                silBtn->decorationStyle().setCursor(Cursor::PointingHand);

                silBtn->clicked().connect([=](){

                    auto confirmDialog = askConfirm("İptal Etmek İstediğinize Eminmisiniz?");

                    confirmDialog->clicked().connect([=](){

                        Soru filter;
                        filter.setOid(item.oid().value().to_string());
                        filter.Delete();

                        if( this->UpdateItem(filter) ){
//                            this->informDialog("Başarılı Bir Şekilde Soru İptal Edildi!");
                            filter.clear();
                            filter.setOwner(this->CurrentUser()->oid().value().to_string());
                            this->UpdateList(filter);
                        }else{
                            this->warnDialog("<p>Bir Hata Oluştu.</p><p>Error: " + this->getLastError().toStdString()+"</p>");
                        }

                    });

                });
            }





        }

        auto container = container_->addWidget(cpp14::make_unique<WContainerWidget>());


        container->addStyleClass(Bootstrap::ContextualBackGround::bg_info+Bootstrap::ImageShape::img_thumbnail);

        auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());

        vLayout->addWidget(cpp14::make_unique<WText>(item.getSoru()),0,AlignmentFlag::Left)->setTextAlignment(AlignmentFlag::Left);
        vLayout->addSpacing(2);
        auto cevapList = item.getShufledCevaplarStruct();

        int count = 1;
        for( const auto &cevapItem : cevapList ){
            if( cevapItem.index == item.getCevapIndex() ){
                std::string textSikBaslik = count == 1 ? "A) " : ( count == 2 ? "B) " : ( count == 3 ? "C) " : ( count == 4 ? "D) " : ( count == 5 ? "E) " : ( count == 6 ? "F) " : ( count == 7 ? "G) " : "H) " ) ) ) ) ) );

                auto text = vLayout->addWidget(cpp14::make_unique<WText>("<h5>"+textSikBaslik+cevapItem.Cevap+"</h5>"),0,AlignmentFlag::Left);
                if( !item.isDeleted() ) text->setAttributeValue(Style::style,Style::background::color::color(Style::color::Green::ForestGreen+Style::color::color(Style::color::White::AliceBlue)));
                text->setTextAlignment(AlignmentFlag::Left);
                text->addStyleClass(CSSStyle::Radius::radius3px);
                text->setInline(true);
                text->setPadding(5,Side::Right);
            }else{
                std::string textSikBaslik = count == 1 ? "A) " : ( count == 2 ? "B) " : ( count == 3 ? "C) " : ( count == 4 ? "D) " : ( count == 5 ? "E) " : ( count == 6 ? "F) " : ( count == 7 ? "G) " : "H) " ) ) ) ) ) );
                vLayout->addWidget(cpp14::make_unique<WText>(textSikBaslik+cevapItem.Cevap),0,AlignmentFlag::Left)->setTextAlignment(AlignmentFlag::Left);
            }
            count++;
        }



        for( const auto &vote : item.getOnayStruct() ){
            vLayout->addSpacing(2);
            User _user;
            _user.setOid(vote.owner);
            auto onaycontainer = vLayout->addWidget(cpp14::make_unique<WContainerWidget>(),0,AlignmentFlag::Justify);
            onaycontainer->setPositionScheme(PositionScheme::Relative);
            if( vote.Onay ){
                auto onay1Text = onaycontainer->addWidget(cpp14::make_unique<WText>(mUserManager->FindOneItem(_user).getAdSoyad()+" Onay +1"));
                onay1Text->setTextAlignment(AlignmentFlag::Center);
                onaycontainer->addStyleClass(Bootstrap::Label::Success);
            }else{
                if( vote.owner.size() > 0 ){
                    auto onay1Text = onaycontainer->addWidget(cpp14::make_unique<WText>("<p>"+mUserManager->FindOneItem(_user).getAdSoyad()+" Red -1</p><p>Gerekçe: "+vote.aciklama+"</p>"));
                    onay1Text->setTextAlignment(AlignmentFlag::Center);
                    onaycontainer->addStyleClass(Bootstrap::Label::Danger);

                    auto duzeltText = onaycontainer->addWidget(cpp14::make_unique<WText>("<h6>Bu Hata Düzeltildi<b>!!!</b></h6>"));
                    duzeltText->setPadding(1,AllSides);
                    duzeltText->setAttributeValue(Style::style,Style::background::color::color(Style::color::Green::DarkCyan)+Style::color::color(Style::color::White::AliceBlue));
                    duzeltText->decorationStyle().setCursor(Cursor::PointingHand);
                    duzeltText->clicked().connect([=](){

                        Soru filter;
                        filter.setOid(item.oid().value().to_string());
                        SerikBLDCore::Item _item("");
                        _item.append(SKey::Soru::Onay::aciklama,SerikBLDCore::Item("").append("$eq",vote.aciklama));

                        SerikBLDCore::Item _elemMatch("");
                        _elemMatch.append("$elemMatch",_item);

                        filter.append(SKey::Soru::onay,_elemMatch);


                        SerikBLDCore::Item setDoc("");
                        setDoc.append("$set",SerikBLDCore::Item("").append(SKey::Soru::onay+".$."+SKey::Soru::Onay::onay,true));

                        std::cout <<"\n"<< bsoncxx::to_json(filter.view()) << std::endl;

                        try {
                            auto upt = this->db()->collection(SKey::Soru::Collection).update_one(filter.view(),setDoc.view());
                            if( upt ){
                                if( upt.value().modified_count() ){
                                    filter.clear();
                                    filter.setOwner(this->CurrentUser()->oid().value().to_string());
                                    this->UpdateList(filter);
                                }else{
                                    this->warnDialog("Hata Oluştu");
                                }
                            }else{
                                this->warnDialog("Hata Oluştu");
                            }
                        } catch (mongocxx::exception &e) {
                            this->warnDialog(std::string("Hata: ")+e.what());
                        }


                    });


                }else{
                    auto onay1Text = vLayout->addWidget(cpp14::make_unique<WText>("Hatalı Oylama!!!!!"),0,AlignmentFlag::Justify);
                    onay1Text->setTextAlignment(AlignmentFlag::Center);
                    onaycontainer->addStyleClass(Bootstrap::Label::Danger);
                }
            }
            onaycontainer->addWidget(cpp14::make_unique<WBreak>());

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
        }
    }

}

SoruEkleWidget::SoruEkleWidget(User* _mUser, const bool &initNewSoru)
    :mUser(_mUser)
{

    if( initNewSoru ){
        this->setNewSoru();
    }

}

Signal<NoClass> &SoruEkleWidget::SaveSignal()
{
    return SoruSignal;
}

Signal<NoClass> &SoruEkleWidget::UpdateSignal()
{
    return _UpdateSignal;
}

Soru SoruEkleWidget::getSoru() const
{
    return mSoru;
}

void SoruEkleWidget::setCurrentSoru(const Soru &soru)
{


    {
        auto container = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_6+
                                 Bootstrap::Grid::Medium::col_md_6+
                                 Bootstrap::Grid::Small::col_sm_12+
                                 Bootstrap::Grid::ExtraSmall::col_xs_12);
        container->setContentAlignment(AlignmentFlag::Justify);

        container->addWidget(cpp14::make_unique<WText>("Soru Metni"));
        mSoruMetniEdit = container->addWidget(cpp14::make_unique<WTextArea>());
        mSoruMetniEdit->setHeight(250);
        mSoruMetniEdit->setText(soru.getSoru());

        container->addWidget(cpp14::make_unique<WText>("Soruyu Ekleyen"))->setMargin(25,Side::Top);
        container->addWidget(cpp14::make_unique<WBreak>());
        container->addWidget(cpp14::make_unique<WText>("<b>"+mUser->getAdSoyad()+"</b>"));

        container->addWidget(cpp14::make_unique<WBreak>());
        container->addWidget(cpp14::make_unique<WText>(mUser->oid().value().to_string()));
    }



    {
        auto container = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_6+
                                 Bootstrap::Grid::Medium::col_md_6+
                                 Bootstrap::Grid::Small::col_sm_12+
                                 Bootstrap::Grid::ExtraSmall::col_xs_12);
        container->setContentAlignment(AlignmentFlag::Justify);

        auto cevapList = soru.getCevaplarStruct();

        std::reverse(cevapList.begin(),cevapList.end());
        mCevap1 = this->addCevapWidget(container,"Cevap 1",cevapList[0].Cevap);
        mCevap2 = this->addCevapWidget(container,"Cevap 2",cevapList[1].Cevap);
        mCevap3 = this->addCevapWidget(container,"Cevap 3",cevapList[2].Cevap);
        mCevap4 = this->addCevapWidget(container,"Cevap 4",cevapList[3].Cevap);

        mCevap5 = this->addCevapWidget(container,"Cevap 5",cevapList[4].Cevap);
        mCevap6 = this->addCevapWidget(container,"Cevap 6",cevapList[5].Cevap);
        mCevap7 = this->addCevapWidget(container,"Cevap 7",cevapList[6].Cevap);
        mCevap8 = this->addCevapWidget(container,"Cevap 8",cevapList[7].Cevap);


        {
            auto cvp1Container = container->addWidget(cpp14::make_unique<WContainerWidget>());
            cvp1Container->addStyleClass(Bootstrap::ImageShape::img_thumbnail);
            cvp1Container->setWidth(WLength("100%"));

            cvp1Container->addWidget(cpp14::make_unique<WText>("Doğru Cevap İndeksi"));
            mCevapComboBox = cvp1Container->addWidget(cpp14::make_unique<WComboBox>());

            mCevapComboBox->addItem("Seçiniz...");
            mCevapComboBox->addItem("1");
            mCevapComboBox->addItem("2");
            mCevapComboBox->addItem("3");
            mCevapComboBox->addItem("4");
            mCevapComboBox->addItem("5");
            mCevapComboBox->addItem("6");
            mCevapComboBox->addItem("7");
            mCevapComboBox->addItem("8");
            mCevapComboBox->setCurrentIndex(soru.getCevapIndex());

            cvp1Container->setMargin(10,Side::Top|Side::Bottom);
            cvp1Container->addStyleClass(Bootstrap::ContextualBackGround::bg_primary);
        }

//        {
//            auto cvp1Container = container->addWidget(cpp14::make_unique<WContainerWidget>());
//            cvp1Container->addStyleClass(Bootstrap::ImageShape::img_thumbnail);
//            cvp1Container->setWidth(WLength("100%"));

//            cvp1Container->addWidget(cpp14::make_unique<WText>("Zorluk Seviyesi"));
//            mZorlukComboBox = cvp1Container->addWidget(cpp14::make_unique<WComboBox>());

//            mZorlukComboBox->addItem("Seçiniz...");
//            mZorlukComboBox->addItem("1");
//            mZorlukComboBox->addItem("2");
//            mZorlukComboBox->addItem("3");
//            mZorlukComboBox->addItem("4");
//            mZorlukComboBox->addItem("5");
//            mZorlukComboBox->setCurrentIndex(soru.getZorluk());

//            cvp1Container->setMargin(10,Side::Top|Side::Bottom);
//            cvp1Container->addStyleClass(Bootstrap::ContextualBackGround::bg_primary);
//        }




    }

    auto kaydetBtn = this->Content()->addWidget(cpp14::make_unique<WPushButton>("Güncelle"));
    kaydetBtn->addStyleClass(Bootstrap::Button::Danger);

    kaydetBtn->clicked().connect([=](){



        if( mSoruMetniEdit->text().toUTF8().size() < 25 ){
            this->warnDialog("Soru Metni Yetersiz");
            return;
        }

        if( mCevap1->text().toUTF8().size() < 2 ){
            this->warnDialog("Cevap 1 Yetersiz: ");
            return;
        }

        if( mCevap2->text().toUTF8().size() < 2 ){
            this->warnDialog("Cevap 2 Yetersiz");
            return;
        }

        if( mCevap3->text().toUTF8().size() < 2 ){
            this->warnDialog("Cevap 3 Yetersiz");
            return;
        }

        if( mCevap4->text().toUTF8().size() < 2 ){
            this->warnDialog("Cevap 4 Yetersiz");
            return;
        }

        if( mCevap4->text().toUTF8().size() < 2 ){
            this->warnDialog("Cevap 4 Yetersiz");
            return;
        }

        if( mCevapComboBox->currentText().toUTF8() == "Seçiniz..." ){
            this->warnDialog("<b>Cevap Seçmediniz</b>");
            return;
        }

//        if( mZorlukComboBox->currentText().toUTF8() == "Seçiniz..." ){
//            this->warnDialog("<b>Zorluk Seçmediniz</b>");
//            return;
//        }

        mSoru.clear();
        mSoru.setCevapIndex(mCevapComboBox->currentIndex());

        mSoru.addCevap(mCevap8->text().toUTF8(),8);
        mSoru.addCevap(mCevap7->text().toUTF8(),7);
        mSoru.addCevap(mCevap6->text().toUTF8(),6);
        mSoru.addCevap(mCevap5->text().toUTF8(),5);


        mSoru.addCevap(mCevap4->text().toUTF8(),4);
        mSoru.addCevap(mCevap3->text().toUTF8(),3);
        mSoru.addCevap(mCevap2->text().toUTF8(),2);
        mSoru.addCevap(mCevap1->text().toUTF8(),1);
        mSoru.setSoru(mSoruMetniEdit->text().toUTF8());
        mSoru.setOid(soru.oid().value().to_string());



//        mSoru.setZorluk(std::stoi(mZorlukComboBox->currentText().toUTF8()));


        _UpdateSignal.emit(NoClass());


    });

}

void SoruEkleWidget::setNewSoru()
{
    {
        auto container = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_6+
                                 Bootstrap::Grid::Medium::col_md_6+
                                 Bootstrap::Grid::Small::col_sm_12+
                                 Bootstrap::Grid::ExtraSmall::col_xs_12);
        container->setContentAlignment(AlignmentFlag::Justify);

        container->addWidget(cpp14::make_unique<WText>("Soru Metnini Giriniz"));
        mSoruMetniEdit = container->addWidget(cpp14::make_unique<WTextArea>());
        mSoruMetniEdit->setHeight(250);

        container->addWidget(cpp14::make_unique<WText>("Soruyu Ekleyen"))->setMargin(25,Side::Top);
        container->addWidget(cpp14::make_unique<WBreak>());
        container->addWidget(cpp14::make_unique<WText>("<b>"+mUser->getAdSoyad()+"</b>"));

        container->addWidget(cpp14::make_unique<WBreak>());
        container->addWidget(cpp14::make_unique<WText>(mUser->oid().value().to_string()));
    }



    {
        auto container = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_6+
                                 Bootstrap::Grid::Medium::col_md_6+
                                 Bootstrap::Grid::Small::col_sm_12+
                                 Bootstrap::Grid::ExtraSmall::col_xs_12);
        container->setContentAlignment(AlignmentFlag::Justify);


        mCevap1 = addCevapWidget(container,"Cevap 1");
        mCevap2 = addCevapWidget(container,"Cevap 2");
        mCevap3 = addCevapWidget(container,"Cevap 3");
        mCevap4 = addCevapWidget(container,"Cevap 4");
        mCevap5 = addCevapWidget(container,"Cevap 5");
        mCevap6 = addCevapWidget(container,"Cevap 6");
        mCevap7 = addCevapWidget(container,"Cevap 7");
        mCevap8 = addCevapWidget(container,"Cevap 8");


        {
            auto cvp1Container = container->addWidget(cpp14::make_unique<WContainerWidget>());
            cvp1Container->addStyleClass(Bootstrap::ImageShape::img_thumbnail);
            cvp1Container->setWidth(WLength("100%"));

            cvp1Container->addWidget(cpp14::make_unique<WText>("Doğru Cevap İndeksi"));
            mCevapComboBox = cvp1Container->addWidget(cpp14::make_unique<WComboBox>());

            mCevapComboBox->addItem("Seçiniz...");
            mCevapComboBox->addItem("1");
            mCevapComboBox->addItem("2");
            mCevapComboBox->addItem("3");
            mCevapComboBox->addItem("4");
            mCevapComboBox->addItem("5");
            mCevapComboBox->addItem("6");
            mCevapComboBox->addItem("7");
            mCevapComboBox->addItem("8");

            cvp1Container->setMargin(10,Side::Top|Side::Bottom);
            cvp1Container->addStyleClass(Bootstrap::ContextualBackGround::bg_primary);
        }

//        {
//            auto cvp1Container = container->addWidget(cpp14::make_unique<WContainerWidget>());
//            cvp1Container->addStyleClass(Bootstrap::ImageShape::img_thumbnail);
//            cvp1Container->setWidth(WLength("100%"));

//            cvp1Container->addWidget(cpp14::make_unique<WText>("Zorluk Seviyesi"));
//            mZorlukComboBox = cvp1Container->addWidget(cpp14::make_unique<WComboBox>());

//            mZorlukComboBox->addItem("Seçiniz...");
//            mZorlukComboBox->addItem("1");
//            mZorlukComboBox->addItem("2");
//            mZorlukComboBox->addItem("3");
//            mZorlukComboBox->addItem("4");
//            mZorlukComboBox->addItem("5");


//            cvp1Container->setMargin(10,Side::Top|Side::Bottom);
//            cvp1Container->addStyleClass(Bootstrap::ContextualBackGround::bg_primary);
//        }

    }
    auto kaydetBtn = this->Content()->addWidget(cpp14::make_unique<WPushButton>("Kaydet"));
    kaydetBtn->addStyleClass(Bootstrap::Button::Danger);

    kaydetBtn->clicked().connect([=](){

        if( mSoruMetniEdit->text().toUTF8().size() < 25 ){
            this->warnDialog("Soru Metni Yetersiz Min: 25 Karakter Olmalı");
            return;
        }

        if( mCevap1->text().toUTF8().size() < 2 ){
            this->warnDialog("Cevap 1 Yetersiz Min 2 Karakter");
            return;
        }

        if( mCevap2->text().toUTF8().size() < 2 ){
            this->warnDialog("Cevap 2 Yetersiz Min 2 Karakter");
            return;
        }

        if( mCevap3->text().toUTF8().size() < 2 ){
            this->warnDialog("Cevap 3 Yetersiz Min 2 Karakter");
            return;
        }

        if( mCevap4->text().toUTF8().size() < 2 ){
            this->warnDialog("Cevap 4 Yetersiz Min 2 Karakter");
            return;
        }

        if( mCevap5->text().toUTF8().size() < 2 ){
            this->warnDialog("Cevap 5 Yetersiz Min 2 Karakter");
            return;
        }

        if( mCevap6->text().toUTF8().size() < 2 ){
            this->warnDialog("Cevap 6 Yetersiz Min 2 Karakter");
            return;
        }

        if( mCevap7->text().toUTF8().size() < 2 ){
            this->warnDialog("Cevap 7 Yetersiz Min 2 Karakter");
            return;
        }

        if( mCevap8->text().toUTF8().size() < 2 ){
            this->warnDialog("Cevap 8 Yetersiz Min 2 Karakter");
            return;
        }

        if( mCevapComboBox->currentText().toUTF8() == "Seçiniz..." ){
            this->warnDialog("<b>Cevap Seçmediniz</b>");
            return;
        }

//        if( mZorlukComboBox->currentText().toUTF8() == "Seçiniz..." ){
//            this->warnDialog("<b>Zorluk Seçmediniz</b>");
//            return;
//        }





        mSoru.clear();
        mSoru.setCevapIndex(mCevapComboBox->currentIndex());
        mSoru.UnDelete();

        mSoru.addCevap(mCevap8->text().toUTF8(),8);
        mSoru.addCevap(mCevap7->text().toUTF8(),7);
        mSoru.addCevap(mCevap6->text().toUTF8(),6);
        mSoru.addCevap(mCevap5->text().toUTF8(),5);

        mSoru.addCevap(mCevap4->text().toUTF8(),4);
        mSoru.addCevap(mCevap3->text().toUTF8(),3);
        mSoru.addCevap(mCevap2->text().toUTF8(),2);
        mSoru.addCevap(mCevap1->text().toUTF8(),1);
        mSoru.setSoru(mSoruMetniEdit->text().toUTF8());

//        mSoru.setZorluk(std::stoi(mZorlukComboBox->currentText().toUTF8()));

        SoruSignal.emit(NoClass());


    });
}

WTextArea *SoruEkleWidget::addCevapWidget(WContainerWidget *parentContainer, const std::string &title, const std::string cevapMetni)
{

    auto cvp1Container = parentContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    cvp1Container->addStyleClass(Bootstrap::ImageShape::img_thumbnail);
    cvp1Container->setWidth(WLength("100%"));

    cvp1Container->addWidget(cpp14::make_unique<WText>(title));
    auto mCevap = cvp1Container->addWidget(cpp14::make_unique<WTextArea>());
    mCevap->setHeight(50);
    if( cevapMetni.size() ){
        mCevap->setText(cevapMetni);
    }
    cvp1Container->setMargin(10,Side::Top|Side::Bottom);
    cvp1Container->addStyleClass(Bootstrap::ContextualBackGround::bg_info);
    return mCevap;

}


