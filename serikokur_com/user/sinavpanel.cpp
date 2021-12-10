#include "sinavpanel.h"

SinavPanel::SinavPanel(SerikBLDCore::DB *_mDB, const std::string &tcno)
    :mTCNO(tcno)
{

    mBasvuruManager = new BasvuruManager(_mDB);
    mSinavManager = new SinavManager(_mDB);
    mBasvuru = new BasvuruItem();

    mSoruManager = new SoruManager(_mDB,nullptr);

    mSinav = std::make_unique<Sinav>();

    BasvuruItem filter;
    filter.setTCNO(this->tCNO());


    std::cout << bsoncxx::to_json(filter.view()) << std::endl;

    auto val = this->mBasvuruManager->FindOneItem(filter);


    if( val.view().empty() ){
        auto container = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::col_full_12);
        container->setAttributeValue(Style::style,Style::background::color::color(Style::color::Red::Red)+Style::color::color(Style::color::White::AliceBlue));
        container->setContentAlignment(AlignmentFlag::Center);
        container->addWidget(cpp14::make_unique<WText>("<p>Bir Hata Oluştu</p><p>Lütfen Bizimle İletişime Geçiniz</p>"));
        return;
    }else{
        mBasvuru->setDocumentView(val.view());

        if( mBasvuru->getOnay() ){
            auto container = this->Header()->addWidget(cpp14::make_unique<WContainerWidget>());
            container->addStyleClass(Bootstrap::Grid::col_full_12);
            container->setContentAlignment(AlignmentFlag::Center);
            auto hLayout = container->setLayout(cpp14::make_unique<WHBoxLayout>());
            hLayout->addStretch(1);
            auto infoText = hLayout->addWidget(cpp14::make_unique<WText>("<p>Başvurunuz Onaylanmış<br><i>AdSoyad: "
                                                                         +mBasvuru->getAdSoyad()+"</i><br>TCNO: "
                                                                         +mBasvuru->getTCNO()+"</p>",TextFormat::UnsafeXHTML));
            infoText->addStyleClass(Bootstrap::Label::Success);
            infoText->setAttributeValue(Style::style,Style::font::size::s14px);
            infoText->setPadding(15,AllSides);
            infoText->setInline(true);


            hLayout->addStretch(1);

            this->initMenu();

        }else{
            auto rContainer = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
            rContainer->addStyleClass(Bootstrap::Grid::row);

            {
                auto infocontainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
                infocontainer->addStyleClass(Bootstrap::Grid::col_full_12);
                infocontainer->setContentAlignment(AlignmentFlag::Center);
                auto hLayout = infocontainer->setLayout(cpp14::make_unique<WHBoxLayout>());
                hLayout->addStretch(1);
                auto infoText = hLayout->addWidget(cpp14::make_unique<WText>("<p>Başvurunuz Red Edilmiş yada Henüz Onaylanmamış.<br>Başvuru Durumu Size SMS ile Bildirilecektir.</p>",TextFormat::UnsafeXHTML));
                infoText->addStyleClass(Bootstrap::Label::Danger);
                infoText->setAttributeValue(Style::style,Style::font::size::s14px);
                infoText->setMargin(15,Side::Left|Side::Right);
                infoText->setPadding(10,AllSides);
                infoText->setInline(true);
                hLayout->addStretch(1);
            }

            {
                auto infocontainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
                infocontainer->addStyleClass(Bootstrap::Grid::col_full_12);
                infocontainer->setContentAlignment(AlignmentFlag::Center);
                auto hLayout = infocontainer->setLayout(cpp14::make_unique<WHBoxLayout>());
                hLayout->addStretch(1);
                auto infoText = hLayout->addWidget(cpp14::make_unique<WText>("<b>Başvuru Bilgileriniz</b>",TextFormat::UnsafeXHTML));
                infoText->addStyleClass(Bootstrap::Label::info);
                infoText->setAttributeValue(Style::style,Style::font::size::s14px);
                infoText->setMargin(15,Side::Left|Side::Right);
                infoText->setPadding(10,AllSides);
                infoText->setInline(true);
                hLayout->addStretch(1);
                infocontainer->decorationStyle().setCursor(Cursor::PointingHand);
                infocontainer->clicked().connect([=](){

                    auto mDialog = createDialog("Bilgileriniz");

                    mDialog->contents()->addWidget(cpp14::make_unique<WText>("<b>Ad&Soyad:</b><i>"+mBasvuru->getAdSoyad()+"</i>",TextFormat::UnsafeXHTML));
                    mDialog->contents()->addWidget(cpp14::make_unique<WBreak>());
                    mDialog->contents()->addWidget(cpp14::make_unique<WText>("<b>Cep Tel:</b><i>"+mBasvuru->getCepNo()+"</i>",TextFormat::UnsafeXHTML));
                    mDialog->contents()->addWidget(cpp14::make_unique<WBreak>());
                    mDialog->contents()->addWidget(cpp14::make_unique<WText>("<b>TCNO:</b><i>"+mBasvuru->getTCNO()+"</i>",TextFormat::UnsafeXHTML));

                    mDialog->show();

                });
            }
        }

    }

    this->setMargin(50,Side::Top|Side::Bottom);
}

SinavPanel::~SinavPanel()
{
    delete mBasvuruManager;
    delete mSinavManager;
    delete mBasvuru;
}

void SinavPanel::initMenu()
{



    this->Content()->clear();

    auto container = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
    container->addStyleClass(Bootstrap::Grid::col_full_12);
    auto hLayout = container->setLayout(cpp14::make_unique<WHBoxLayout>());
    hLayout->addStretch(1);

    Sinav filter;
    filter.setSahibi(mTCNO);
    //    LOG << filter.getCollection() << "\n" << bsoncxx::to_json(filter.view()) << "\n";

    auto val = mSinavManager->FindOneItem(filter);

    if( val.view().empty() ){
        auto createContainer = hLayout->addWidget(cpp14::make_unique<WContainerWidget>());
        createContainer->addStyleClass(Bootstrap::Button::Primary);
        createContainer->addNew<WText>("Sınav Oluştur");
        createContainer->setPadding(10,Side::Top|Side::Bottom);
        createContainer->setPadding(8,Side::Left|Side::Right);
        createContainer->decorationStyle().setCursor(Cursor::PointingHand);

        createContainer->clicked().connect([=](){

            Sinav newSinav;
            newSinav.setSahibi(mTCNO);

            auto soruList = this->PrepareSoruList();;

//            std::cout << "\n SoruListCount: " << soruList.size() << "\n";
//            for( const auto &soru : soruList ){
////                std::cout << "\n SoruOid: " << soru;
//            }
            newSinav.setSoruOidList(soruList);
//            std::cout << "\n View: " << bsoncxx::to_json(newSinav.view()) << "\n";

            if( mSinavManager->InsertItem(newSinav).size() ){
                this->informDialog("Sınav Oluşturuldu");
                this->initMenu();
            }else{
                this->warnDialog("Sınav Oluşturulamadı. Lütfen Daha Sonra Tekrar Deneyiniz");
            }
        });
    }else{

        mSinav->setDocumentView(mSinavManager->FindOneItem(Sinav().setSahibi(mTCNO)).view());

        if( mSinav->getCevapList().size() == 25 ){
            auto createContainer = hLayout->addWidget(cpp14::make_unique<WContainerWidget>());
            createContainer->addStyleClass(Bootstrap::Grid::container_fluid);
            createContainer->addStyleClass(Bootstrap::Button::info);
            createContainer->addNew<WText>("<h4>Sınavınızı Başarılı Bir Şekilde Tamamladınız.<br>Sonuçlar İçin Lütfen Bekleyiniz</h4>",TextFormat::UnsafeXHTML);
            createContainer->setPadding(10,Side::Top|Side::Bottom);
            createContainer->setPadding(30,Side::Left|Side::Right);
            createContainer->setHeight(250);

        }else{
            auto createContainer = hLayout->addWidget(cpp14::make_unique<WContainerWidget>());
            createContainer->addStyleClass(Bootstrap::Button::info);
            createContainer->addNew<WText>("Sınavınız");
            createContainer->setPadding(10,Side::Top|Side::Bottom);
            createContainer->setPadding(8,Side::Left|Side::Right);
            createContainer->decorationStyle().setCursor(Cursor::PointingHand);



            mSoruList = mSinav->soruOidList();

            createContainer->clicked().connect(this,&SinavPanel::initSoruList);
        }
    }
    hLayout->addStretch(1);
}


void SinavPanel::initSoruList()
{

    //    LOG;
    if( mSoruList.empty() ){
        this->warnDialog("Sınav Sorularınız da Hata Var: " + std::to_string(mSoruList.size()));
        return;
    }

    //    LOG;
    this->Content()->clear();

    {
        auto container = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::col_full_12);
        container->setContentAlignment(AlignmentFlag::Center);

        auto container_ = container->addWidget(cpp14::make_unique<WContainerWidget>());
        container_->setMaximumSize(1024,WLength::Auto);
        auto text = container_->addWidget(cpp14::make_unique<WText>("<h3>Dikkat!</h3>"
                                                                    "<p>Sınava <b>Başla</b> Tuşuna Bastığınız Anda Süreniz Başlar.<br>"
                                                                    "Sınava Başlamadan Önce internet Bağlantınızın ve Bilgisayarınızın Sınav Sonuna Kadar<br>"
                                                                    "Kesintisiz Çalışacağından Emin Olunuz.</p>"
                                                                    "<p>Sorular Sırasıyla Gelecektir.<br>"
                                                                    "Cevap Verdiğiniz Sorulara Tekrar Geri Dönemezsiniz.<br></p>"
                                                                    "Soruları Pas Geçemezsiniz.<br></p>"
                                                                    "<p>Sınav Süreniz <b>30 Dakikadır</b></p>"
                                                                    "<p>Sınavın Sonuna Gelmeden de Sınavı Bırakabilirsiniz</p>",TextFormat::UnsafeXHTML));
        text->setTextAlignment(AlignmentFlag::Justify);
    }

    //LOG;
    {
        auto container = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::col_full_12);
        container->setContentAlignment(AlignmentFlag::Center);

        auto container_ = container->addWidget(cpp14::make_unique<WContainerWidget>());
        container_->setMaximumSize(1024,WLength::Auto);
        auto baslaBTN = container_->addWidget(cpp14::make_unique<WPushButton>("Başla"));
        baslaBTN->clicked().connect(this,[=](){
            //            LOG << QDateTime::currentSecsSinceEpoch();
            this->SinavaBasla();
        });
        baslaBTN->addStyleClass(Bootstrap::Button::Danger);

    }

    //LOG;
}

std::vector<std::string> SinavPanel::PrepareSoruList()
{

    std::vector<std::string> soruList;

    QVector<std::string> sorulmusList;

    auto sorulmusSoruList = mSinavManager->GetList(Sinav(),1000,0);
    for( int i = 0 ; i < sorulmusSoruList.count() ; i++ ){
        auto sorular  = sorulmusSoruList.at(i);
        for( const auto &soruOid : sorular.soruOidList() ){
            sorulmusList.push_back(soruOid);
        }
    }




    auto mucella_List = this->PrepareSoruPerBook("Mücella",sorulmusList,soruList);
    auto deyim_List = this->PrepareSoruPerBook("101 Deyim 101 Öykü",sorulmusList,soruList);
    auto fatih_List = this->PrepareSoruPerBook("Fatih-i Harbiye",sorulmusList,soruList);
    auto deli_List = this->PrepareSoruPerBook("Deli Tarla",sorulmusList,soruList);
    auto acimak_List = this->PrepareSoruPerBook("Acımak",sorulmusList,soruList);

    for( const auto &item : mucella_List ){
        soruList.push_back(item);
    }

    for( const auto &item : deyim_List ){
        soruList.push_back(item);
    }

    for( const auto &item : fatih_List ){
        soruList.push_back(item);
    }

    for( const auto &item : deli_List ){
        soruList.push_back(item);
    }

    for( const auto &item : acimak_List ){
        soruList.push_back(item);
    }

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(soruList.begin(), soruList.end(), g);

    return soruList;


}

std::vector<std::string> SinavPanel::PrepareSoruPerBook(const std::string &bookName, QVector<std::string> sorulmusList, std::vector<std::string> &sorulacakList)
{
    QVector<SiralamaItem> mList;
    std::vector<std::string> rList;

    auto List = mSoruManager->GetList(Soru().setKitap(bookName),250,0);
    for( const auto &item : List ){
        if( item.isGecerli() ){
            int sorulmaSayisi = 0;
            for( const auto &sorulmusItem : sorulmusList ){
                if( item.oid().value().to_string() == sorulmusItem ){
                    sorulmaSayisi++;
                }
            }
            mList.push_back(SiralamaItem{item.oid().value().to_string(),sorulmaSayisi});
        }
    }
    std::sort(mList.begin(),mList.end());
//    std::cout << "\n" << bookName << " SoruCount: " << mList.count() << "\n";
    mList.remove(15,mList.count()-15);
//    std::cout << "\n" << bookName << " SoruCount: " << mList.count() << "\n";

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(mList.begin(), mList.end(), g);

    for( int i = 0 ; i < mList.count() ; i++ ){
        rList.push_back(mList.at(i).soruOid);
//        std::cout << "\n" << bookName << " " << mList.at(i).soruOid;
        if( i >= 4 ){
            break;
        }
    }



    return rList;
}

const std::string &SinavPanel::tCNO() const
{
    return mTCNO;
}

void SinavPanel::SinavaBasla()
{


    Soru filter;

    bsoncxx::builder::basic::array oidList;

    for( const auto &oid : mSoruList ){
        oidList.append(make_document(kvp("_id",bsoncxx::oid{oid})));
    }

    filter.append("$or",oidList);

    auto list = mSoruManager->GetList(filter);

    this->Content()->clear();
    this->Content()->setContentAlignment(AlignmentFlag::Center);


    long long currentMSecFromEpoc;

    if( mSinav->getBaslangic() == -1 ){
        Sinav sinavFilter;
        sinavFilter.setOid(mSinav->oid().value());
        sinavFilter.setBaslangicTime(QDateTime::currentSecsSinceEpoch());

        currentMSecFromEpoc = QDateTime::currentSecsSinceEpoch();

        if( !mSinavManager->setField(Sinav().setOid(mSinav->oid().value()),SKey::Sinav::baslangicTime,currentMSecFromEpoc) ){
            this->warnDialog(mSinavManager->getLastError().toStdString());
            return;
        }
    }else{
        currentMSecFromEpoc = mSinav->getBaslangic();
    }


    if( QDateTime::currentSecsSinceEpoch() > (currentMSecFromEpoc+1800) ){
        auto text = this->Content()->addWidget(cpp14::make_unique<WText>("<h3>Süreniz Doldu!</h3>"));
        text->addStyleClass(Bootstrap::Grid::col_full_12);
        text->setAttributeValue(Style::style,Style::color::color(Style::color::Red::Crimson));
    }else{

        auto cvpList = this->mSinav.get()->getCevapList();


        QVector<Soru> newList;
        QVector<Soru> existList;

        for( const auto &sSoruItem : qAsConst(list) ){

            bool exist = false;

            for( const auto &cItem : cvpList ){
                if( cItem.soruOid == sSoruItem.oid().value().to_string() ){
                    exist = true;
                    LOG << "Exist: " << cItem.soruOid << " " << sSoruItem.oid().value().to_string();
                }
            }

            if( !exist ){
                newList.append(sSoruItem);
            }else{
                existList.append(sSoruItem);
            }
        }

//        LOG << "Exist List Size: " << existList.size();
//        LOG << "NewList Size: " << newList.size();

        if( existList.size() >= 25 ){

            this->warnDialog("Sınavınızı Tamamlamışsınız!");

            return;
        }

        auto text = this->Content()->addWidget(cpp14::make_unique<WText>("<h4>Sınavınız Başladı</h4>"));
        text->addStyleClass(Bootstrap::Grid::col_full_12);
        text->setAttributeValue(Style::style,Style::color::color(Style::color::Green::Green));


        auto soruWidget = this->Content()->addWidget(cpp14::make_unique<SinavSorusuWidget>(currentMSecFromEpoc,newList,existList));
        soruWidget->Cevap().connect([=]( const int &cevapIndex , const std::string &soruOid ){
            LOG << "Cevap Index: " << cevapIndex << " SoruOid: " << soruOid << "\n";
            mSelectedIndex = cevapIndex;
            mSelectedOid = soruOid;
        });

        soruWidget->Cevaplandi().connect([=]( ){
            LOG << "Cevap Saved Index: " << mSelectedIndex << " SoruOid: " << mSelectedOid << "\n";

            SerikBLDCore::Item item("");
            item.append(SKey::Sinav::Cevaplar::cevapIndex,bsoncxx::types::b_int32{mSelectedIndex});
            item.append(SKey::Sinav::Cevaplar::soruOid,bsoncxx::oid{mSelectedOid});
            item.append(SKey::Sinav::Cevaplar::timeStamp,bsoncxx::types::b_int64{QDateTime::currentSecsSinceEpoch()});

            auto val = mSinavManager->pushValue(Sinav().setOid(mSinav.get()->oid().value()),SKey::Sinav::cevaplar,item);
            if( val ){
                LOG << "Cevaplandı: "<<val.value().modified_count() << "\n";
            }else{
                LOG << "Error: " << mSinavManager->getLastError().toStdString() << "\n";
            }
        });
    }












}

SinavPanel::BasvuruPreviewContainer::BasvuruPreviewContainer()
{
    this->addStyleClass(Bootstrap::Grid::Large::col_lg_4+
                        Bootstrap::Grid::Medium::col_md_4+
                        Bootstrap::Grid::Small::col_sm_6+
                        Bootstrap::Grid::ExtraSmall::col_xs_6);

    this->setAttributeValue(Style::style,Style::background::color::rgb(this->getRandom(),this->getRandom(),this->getRandom()));
}

SinavSorusuWidget::SinavSorusuWidget(const long long &baslangicTime, const QVector<Soru> &_mSoruList, const QVector<Soru> &_mExistList)
    :mBaslangicTime(baslangicTime)
{
    this->setMaximumSize(1024,WLength::Auto);
    this->addStyleClass(Bootstrap::ImageShape::img_thumbnail);
    mSoruList.clear();
    mSoruList.append(_mSoruList);
    mExistList.clear();
    mExistList.append(_mExistList);



    this->ShowSoru(0);

}

Signal<int, std::string> &SinavSorusuWidget::Cevap()
{
    return _cevap;
}

Signal<NoClass> &SinavSorusuWidget::Cevaplandi()
{

    return _cevaplandi;

}

void SinavSorusuWidget::ShowSoru(const int &index)
{



    if( index < 0 || index >= mSoruList.size() ){
        return;
    }

    soruOid = "";
    cevapIndex = -1;


    this->Header()->clear();


    auto barContainer = this->Header()->addWidget(cpp14::make_unique<WContainerWidget>());
    barContainer->setPositionScheme(PositionScheme::Relative);
    barContainer->setHeight(25);
    barContainer->addStyleClass(Bootstrap::Grid::col_full_12);
    barContainer->setOverflow(Overflow::Hidden);

    auto percentBar = barContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    percentBar->setPositionScheme(PositionScheme::Absolute);
    percentBar->setOffsets(0,Side::Top|Side::Left|Side::Bottom);
    percentBar->setContentAlignment(AlignmentFlag::Center);
    auto percentText = percentBar->addWidget(cpp14::make_unique<WText>(WString("Cevaplanan {1}").arg(mExistList.size())));

//    LOG << "Exist List Size: " << mExistList.size() << "\n";
    double percent = static_cast<double>(mExistList.size()) / 25.0 * 100.0;
    percentBar->setWidth(WLength(std::to_string(percent)+"%"));
    percentBar->setAttributeValue(Style::style,Style::background::color::color(Style::color::Green::Chartreuse));



    auto bekleyenBar = barContainer->addWidget(cpp14::make_unique<WContainerWidget>());
    bekleyenBar->setPositionScheme(PositionScheme::Absolute);
    bekleyenBar->setOffsets(0,Side::Top|Side::Right|Side::Bottom);
    bekleyenBar->setContentAlignment(AlignmentFlag::Center);
    bekleyenBar->addWidget(cpp14::make_unique<WText>(WString("Bekleyen {1}").arg(25.0-mExistList.size())));
    bekleyenBar->setWidth(WLength(std::to_string(100-percent)+"%"));
    bekleyenBar->setAttributeValue(Style::style,Style::background::color::color(Style::color::Red::LightCoral));


    auto container = this->Header()->addWidget(cpp14::make_unique<WContainerWidget>());
    container->addStyleClass(Bootstrap::Grid::col_full_12);
    container->setOverflow(Overflow::Hidden);

    auto hLayout = container->setLayout(cpp14::make_unique<WHBoxLayout>());
    auto text_baslangic = hLayout->addWidget(cpp14::make_unique<WText>("Başlangıç: "+QDateTime::fromSecsSinceEpoch(mBaslangicTime).time().toString("hh:mm:ss").toStdString()));
    hLayout->addStretch(1);
    auto text_suan = hLayout->addWidget(cpp14::make_unique<WText>("Şuan: "+QDateTime::currentDateTime().time().toString("hh:mm:ss").toStdString()));
    hLayout->addStretch(1);
    auto text_bitis = hLayout->addWidget(cpp14::make_unique<WText>("Bitiş: "+QDateTime::fromSecsSinceEpoch(mBaslangicTime+1800).time().toString("hh:mm:ss").toStdString()));


    this->Content()->clear();

    this->Footer()->clear();

    std::random_device rd;
    std::mt19937 g(rd());

    auto currentSoru = mSoruList.at(index);
    this->Content()->setMargin(25,Side::Top|Side::Bottom);

    auto text = this->Content()->addWidget(cpp14::make_unique<WText>("<b>"+std::to_string(index+1)+ ".</b> " + currentSoru.getSoru()));
    text->addStyleClass(Bootstrap::Grid::col_full_12);
    text->setTextAlignment(AlignmentFlag::Left);
    text->setMargin(15,Side::Bottom);

    auto tempList = currentSoru.getShufledCevaplarStruct();
    std::vector<Soru::cevap> cvpList;

    for( const auto &cvpItem : tempList ){
        if( cvpItem.index != currentSoru.getCevapIndex() && cvpList.size() < 3 ){
            cvpList.push_back(cvpItem);
        }
    }

    for( const auto &cvpItem : tempList ){
        if( cvpItem.index == currentSoru.getCevapIndex() ){
            cvpList.push_back(cvpItem);
            break;
        }
    }





    std::shuffle(cvpList.begin(),cvpList.end(),g);

    std::vector<std::string> pList = {"D","C","B","A"};


    for( const auto &cvp : cvpList ){
        auto cvpText = this->Content()->addWidget(cpp14::make_unique<WText>(pList.back()+") "+cvp.Cevap));
        cvpText->addStyleClass(Bootstrap::Grid::col_full_12);
        cvpText->setTextAlignment(AlignmentFlag::Left);
        cvpText->setInline(false);

        cvpText->setPadding(5,AllSides);
        cvpText->addStyleClass("btn-Sec");
        cvpText->setId(std::to_string(cvp.index)+"cvp");
        cvpText->clicked().connect([=](){
            this->cevapIndex = cvp.index;
            this->soruOid = currentSoru.oid().value().to_string();
            for( const auto &item : cvpList ){
                auto w = this->Content()->findById(std::to_string(item.index)+"cvp");
                if( w->hasStyleClass("btn-Secilmis") ){
                    w->removeStyleClass("btn-Secilmis");
                }
            }
            cvpText->addStyleClass("btn-Secilmis");
            _cevap.emit(cevapIndex,soruOid);

        });
        pList.pop_back();
    }


    auto nextBTN = this->Footer()->addWidget(cpp14::make_unique<WPushButton>("İleri"));
    nextBTN->addStyleClass(Bootstrap::Button::Primary);
    nextBTN->clicked().connect([=](){

        if( this->cevapIndex < 1 || this->cevapIndex > 8 || this->soruOid.empty() ){
            this->warnDialog("Soruyu Cevaplamadan Geçemezsiniz!.<b>Lütfen Cevaplayınız</b>");
            return;
        }

        if( index < mSoruList.size() ){
            if( index == mSoruList.size()-1){

                _cevaplandi.emit(NoClass());
                mExistList.append(mSoruList.last());


                this->Footer()->clear();
                auto finishSinavBtn = this->Footer()->addWidget(cpp14::make_unique<WPushButton>("Sınavı Tamamla"));
                finishSinavBtn->addStyleClass(Bootstrap::Button::Danger);
                finishSinavBtn->clicked().connect([=](){
                    this->Content()->clear();
                    auto container = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
                    container->setHeight(150);
                    container->addStyleClass(Bootstrap::Grid::col_full_12+Bootstrap::ContextualBackGround::bg_success);

                    //                    container->setAttributeValue(Style::style,Style::background::color::color(Style::color::Green::DarkSeaGreen)+Style::color::color(Style::color::White::AliceBlue)+Style::font::size::s14px);
                    auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());

                    vLayout->addStretch(1);

                    auto text = vLayout->addWidget(cpp14::make_unique<WText>("<p>Tebrikler Sınavı Başarılı Bir Şekilde Tamamladınız.<br>"
                                                                             "Sonuçlar Yarın Saat 12:00'da www.serikokuyor.com Adresinde Yayınlanacaktır. ",TextFormat::UnsafeXHTML));

                    vLayout->addStretch(1);



                    this->Header()->clear();


                    auto barContainer_ = this->Header()->addWidget(cpp14::make_unique<WContainerWidget>());
                    barContainer_->setPositionScheme(PositionScheme::Relative);
                    barContainer_->setHeight(25);
                    barContainer_->addStyleClass(Bootstrap::Grid::col_full_12);

                    auto percentBar_ = barContainer_->addWidget(cpp14::make_unique<WContainerWidget>());
                    percentBar_->setPositionScheme(PositionScheme::Absolute);
                    percentBar_->setOffsets(0,Side::Top|Side::Left|Side::Bottom);
                    percentBar_->setContentAlignment(AlignmentFlag::Center);
                    percentBar_->addWidget(cpp14::make_unique<WText>(WString("Soruların Tamamını Cevapladınız")));
                    percentBar_->setWidth(WLength("100%"));
                    percentBar_->setAttributeValue(Style::style,Style::background::color::color(Style::color::Green::Chartreuse));
                    this->Footer()->removeWidget(finishSinavBtn);


                });
            }else{
                mExistList.append(mSoruList.at(index+1));
                this->ShowSoru(index+1);
                _cevaplandi.emit(NoClass());
            }

        }
    });


}
















