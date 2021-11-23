#include "baskanimizcontainer.h"

BaskanimizContainer::BaskanimizContainer()
{
    this->setId("baskanid");
    auto container = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
    container->addStyleClass(Bootstrap::Grid::col_full_12);

    container->setAttributeValue(Style::style,Style::background::color::rgba(75,125,175,0.9));
    container->setPadding(50,Side::Top|Side::Bottom);

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


    auto titlebaskanText = textContainer->addWidget(cpp14::make_unique<WText>("<h3><p><b>Enver APUTKAN</b></p><p>SERİK BELEDİYE BAŞKANI</p></h3>"));
//    titlebaskanText->setMargin(75,Side::Top);
    titlebaskanText->setTextAlignment(AlignmentFlag::Center);
//    titlebaskanText->setPadding(50,Side::Right);
    titlebaskanText->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue));

}
