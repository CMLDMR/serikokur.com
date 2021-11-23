#include "iletisimcontainer.h"

IletisimContainer::IletisimContainer(SerikBLDCore::DB *mDB)
    :SerikBLDCore::DB(mDB)
{

    setId("iletisimid");
    setAttributeValue(Style::style,Style::background::color::color(Style::color::Grey::DarkSlateGray));

    this->setContentAlignment(AlignmentFlag::Center);
    this->Content()->setMaximumSize(1280,WLength::Auto);
    this->Content()->setContentAlignment(AlignmentFlag::Center);
    this->setPadding(65,Side::Top|Side::Bottom);


    {
        auto container = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_2+Bootstrap::Grid::Medium::col_md_2+Bootstrap::Grid::Small::col_sm_12+Bootstrap::Grid::ExtraSmall::col_xs_12);
        container->setHeight(75);
        container->setAttributeValue(Style::style,Style::background::url("logoWhite.png")+Style::background::size::contain+Style::background::repeat::norepeat+Style::background::position::center_center);
    }

    //    {
    //        auto container = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
    //        container->addStyleClass(Bootstrap::Grid::Large::col_lg_2+Bootstrap::Grid::Medium::col_md_2+Bootstrap::Grid::Small::col_sm_6+Bootstrap::Grid::ExtraSmall::col_xs_6);
    //        container->setHeight(75);
    //        auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());
    //        auto text = vLayout->addWidget(cpp14::make_unique<WText>("Hakkımızda"),0,AlignmentFlag::Center|AlignmentFlag::Middle);
    //        text->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue)+Style::font::size::s20px);
    //    }

    {
        auto container = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_3+Bootstrap::Grid::Medium::col_md_3+Bootstrap::Grid::Small::col_sm_12+Bootstrap::Grid::ExtraSmall::col_xs_12);
        container->addStyleClass(Bootstrap::Grid::Offset::Large::col_lg_2+Bootstrap::Grid::Medium::col_md_2);
        container->setHeight(75);
        auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());
        auto text = vLayout->addWidget(cpp14::make_unique<WText>("Başkanımız"),0,AlignmentFlag::Center|AlignmentFlag::Middle);
        text->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue)+Style::font::size::s20px);
        container->clicked().connect([=](){
            container->doJavaScript("var elmnt = document.getElementById(\"baskanid\");"
                                    "if( elmnt ) { elmnt.scrollIntoView();}");
        });
    }

    {
        auto container = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_3+Bootstrap::Grid::Medium::col_md_3+Bootstrap::Grid::Small::col_sm_6+Bootstrap::Grid::ExtraSmall::col_xs_6);
        container->setHeight(75);
        auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());
        auto text = vLayout->addWidget(cpp14::make_unique<WText>("Kitaplar"),0,AlignmentFlag::Center|AlignmentFlag::Middle);
        text->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue)+Style::font::size::s20px);
        container->clicked().connect([=](){
            container->doJavaScript("var elmnt = document.getElementById(\"kitaplarid\");"
                                    "if( elmnt ) { elmnt.scrollIntoView();}");
        });
    }

    {
        auto container = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::Large::col_lg_3+Bootstrap::Grid::Medium::col_md_3+Bootstrap::Grid::Small::col_sm_6+Bootstrap::Grid::ExtraSmall::col_xs_6);
        container->setHeight(75);
        auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());
        auto text = vLayout->addWidget(cpp14::make_unique<WText>("Yarışma"),0,AlignmentFlag::Center|AlignmentFlag::Middle);
        text->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue)+Style::font::size::s20px);
        text->decorationStyle().setCursor(Cursor::PointingHand);
        container->clicked().connect([=](){
            container->doJavaScript("window.open(\"http://www.serikokuyor.com/serikokuyorsartname.pdf\", '_blank').focus();");
        });
    }

    //    {
    //        auto container = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
    //        container->addStyleClass(Bootstrap::Grid::Large::col_lg_2+Bootstrap::Grid::Medium::col_md_2+Bootstrap::Grid::Small::col_sm_4+Bootstrap::Grid::ExtraSmall::col_xs_6);
    //        container->setHeight(75);
    //        auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());
    //        auto text = vLayout->addWidget(cpp14::make_unique<WText>("İletişim"),0,AlignmentFlag::Center|AlignmentFlag::Middle);
    //        text->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue)+Style::font::size::s20px);
    //    }

    {
        auto container = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(Bootstrap::Grid::col_full_12);
        container->setMargin(50,Side::Top);
        auto hlaylaout = container->setLayout(cpp14::make_unique<WHBoxLayout>());

        hlaylaout->addStretch(1);

        {
            auto facecontainer = hlaylaout->addWidget(cpp14::make_unique<WContainerWidget>(),0,AlignmentFlag::Left);
            facecontainer->setHeight(30);
            facecontainer->setWidth(30);
            facecontainer->setMargin(10,Side::Left|Side::Right);
            facecontainer->decorationStyle().setCursor(Cursor::PointingHand);
            facecontainer->clicked().connect([=](){
                facecontainer->doJavaScript("window.open(\"https://www.facebook.com/Serik-Okuyor-100904992178812\", '_blank').focus();");
            });
            facecontainer->setAttributeValue(Style::style,Style::background::url("face.png")+Style::background::size::contain+Style::background::repeat::norepeat+Style::background::position::center_center);
        }
        {
            auto facecontainer = hlaylaout->addWidget(cpp14::make_unique<WContainerWidget>(),0,AlignmentFlag::Left);
            facecontainer->setHeight(30);
            facecontainer->setWidth(30);
            facecontainer->setMargin(10,Side::Left|Side::Right);
            facecontainer->decorationStyle().setCursor(Cursor::PointingHand);
            facecontainer->clicked().connect([=](){
                facecontainer->doJavaScript("window.open(\"https://twitter.com/SerikOkuyor\", '_blank').focus();");
            });
            facecontainer->setAttributeValue(Style::style,Style::background::url("twitter.png")+Style::background::size::contain+Style::background::repeat::norepeat+Style::background::position::center_center);
        }
        {
            auto facecontainer = hlaylaout->addWidget(cpp14::make_unique<WContainerWidget>(),0,AlignmentFlag::Left);
            facecontainer->setHeight(30);
            facecontainer->setWidth(30);
            facecontainer->setMargin(10,Side::Left|Side::Right);
            facecontainer->decorationStyle().setCursor(Cursor::PointingHand);
            facecontainer->clicked().connect([=](){
                facecontainer->doJavaScript("window.open(\"https://instagram.com/serikokuyor?utm_medium=copy_link\", '_blank').focus();");
            });
            facecontainer->setAttributeValue(Style::style,Style::background::url("instagram.png")+Style::background::size::contain+Style::background::repeat::norepeat+Style::background::position::center_center);
        }

        hlaylaout->addStretch(1);

    }


    {
        auto container = this->Content()->addWidget(cpp14::make_unique<IletisimWidget>(this->getDB()));
        container->addStyleClass(Bootstrap::Grid::col_full_12);
        container->setContentAlignment(AlignmentFlag::Center);
        //        auto hlaylaout = container->setLayout(cpp14::make_unique<WVBoxLayout>());

        //        hlaylaout->addStretch(1);

        //        {
        //            auto text = hlaylaout->addWidget(cpp14::make_unique<WText>("İletişim Formu"),0,AlignmentFlag::Center);
        //            text->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue)+Style::font::size::s20px);
        //        }
        //        {
        //            auto text = hlaylaout->addWidget(cpp14::make_unique<WText>("Yarışma ile ilgili sorularınızı bize iletebilirsiniz"),0,AlignmentFlag::Center);
        //            text->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue)+Style::font::size::s14px);
        //        }

        //        auto adsoyadLineEdit = hlaylaout->addWidget(cpp14::make_unique<WLineEdit>());
        //        adsoyadLineEdit->setPlaceholderText("AD SOYAD");

        //        auto epostaLineEdit = hlaylaout->addWidget(cpp14::make_unique<WLineEdit>());
        //        epostaLineEdit->setPlaceholderText("EPOSTA Adresiniz");

        //        auto telefonLineEdit = hlaylaout->addWidget(cpp14::make_unique<WLineEdit>());
        //        telefonLineEdit->setPlaceholderText("TELEFON Numaranız");

        //        auto iletiLineEdit = hlaylaout->addWidget(cpp14::make_unique<WTextArea>());
        //        iletiLineEdit->setHeight(250);
        //        hlaylaout->addStretch(1);

        //        auto applyBtn = hlaylaout->addWidget(cpp14::make_unique<WPushButton>("Gönder"));
        //        applyBtn->addStyleClass(Bootstrap::Button::info);
    }

}

IletisimWidget::IletisimWidget(DB *_mDB)
    :IletisimFormManager(_mDB)
{
    auto container = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
    container->addStyleClass(Bootstrap::Grid::col_full_12);
    container->setContentAlignment(AlignmentFlag::Center);
    auto hlaylaout = container->setLayout(cpp14::make_unique<WVBoxLayout>());

    hlaylaout->addStretch(1);

    {
        auto text = hlaylaout->addWidget(cpp14::make_unique<WText>("İletişim Formu"),0,AlignmentFlag::Center);
        text->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue)+Style::font::size::s20px);
    }
    {
        auto text = hlaylaout->addWidget(cpp14::make_unique<WText>("Yarışma ile ilgili sorularınızı bize iletebilirsiniz"),0,AlignmentFlag::Center);
        text->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue)+Style::font::size::s14px);
    }

    auto adsoyadLineEdit = hlaylaout->addWidget(cpp14::make_unique<WLineEdit>());
    adsoyadLineEdit->setPlaceholderText("AD SOYAD");

    auto epostaLineEdit = hlaylaout->addWidget(cpp14::make_unique<WLineEdit>());
    epostaLineEdit->setPlaceholderText("EPOSTA Adresiniz");

    auto telefonLineEdit = hlaylaout->addWidget(cpp14::make_unique<WLineEdit>());
    telefonLineEdit->setPlaceholderText("TELEFON Numaranız");

    auto iletiLineEdit = hlaylaout->addWidget(cpp14::make_unique<WTextArea>());
    iletiLineEdit->setHeight(250);
    hlaylaout->addStretch(1);

    auto applyBtn = hlaylaout->addWidget(cpp14::make_unique<WPushButton>("Gönder"));
    applyBtn->addStyleClass(Bootstrap::Button::info);

    applyBtn->clicked().connect([=](){

        if( adsoyadLineEdit->text().toUTF8().size() < 4 ){
            this->warnDialog("Ad Soyad Yetersiz.");
            return;
        }

        if( !QString::fromStdString(epostaLineEdit->text().toUTF8()).contains("@") ){
            this->warnDialog("ePosta Adresiniz Hatalı");
            return;
        }
        if( telefonLineEdit->text().toUTF8().size() < 11 || telefonLineEdit->text().toUTF8().size() > 11 ){
            this->warnDialog("Telefon Numarası Girmediniz");
            return;

        }else{
            if( QString::fromStdString(telefonLineEdit->text().toUTF8()).at(0) != "0" || (QString::fromStdString(telefonLineEdit->text().toUTF8()).at(1) != "5" && QString::fromStdString(telefonLineEdit->text().toUTF8()).at(1) != "2") ){
                this->warnDialog("Telefon Numarası Hatalı.");
                return;
            }
        }

        if( iletiLineEdit->text().toUTF8().size() < 20 ){
            this->warnDialog("Mesajınız Yetersiz yada Hatalı");
            return;
        }


        IletisimFormu form;
        form.setAdSoyad(adsoyadLineEdit->text().toUTF8());
        form.setEPosta(epostaLineEdit->text().toUTF8());
        form.setTelefon(telefonLineEdit->text().toUTF8());
        form.setMesaj(iletiLineEdit->text().toUTF8());

        if( this->InsertItem(form).size() ){

            this->informDialog("<p>İletiniz Alındı.</p>"
                                "<p>En Kısa Sürede Size Dönüş Yapacağınız.</p>");
            iletiLineEdit->setText("");
            telefonLineEdit->setText("");
            epostaLineEdit->setText("");
            adsoyadLineEdit->setText("");


        }else{
            this->warnDialog("İletiniz Kayıt Edilemedi.");
        }
    });
}
