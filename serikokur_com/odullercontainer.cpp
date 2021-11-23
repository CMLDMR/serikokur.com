#include "odullercontainer.h"

OdullerContainer::OdullerContainer()
{
    //        setAttributeValue(Style::style,Style::background::color::rgba(125,180,15));

    this->setContentAlignment(AlignmentFlag::Center);
    this->Content()->setMaximumSize(1280,WLength::Auto);
    this->Content()->setContentAlignment(AlignmentFlag::Center);
    this->setPositionScheme(PositionScheme::Relative);
    this->setMargin(25,Side::Top);

    {
        auto kapcontainer = this->addWidget(cpp14::make_unique<WContainerWidget>());
        kapcontainer->setPositionScheme(PositionScheme::Absolute);
        kapcontainer->setOffsets(0,Side::Bottom|Side::Left);
        kapcontainer->setHeight(107);
        kapcontainer->setWidth(145);
        kapcontainer->setAttributeValue(Style::style,Style::background::url("fold/kaplumbaga.png")+
                                        Style::background::size::contain+
                                        Style::background::repeat::norepeat+
                                        Style::background::position::center_center);
    }


    setPadding(75,Side::Bottom);

    auto container = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
    //    container->setMaximumSize(1280,WLength::Auto);
    container->addStyleClass(Bootstrap::Grid::col_full_12);
    container->setAttributeValue(Style::style,Style::background::url("oduller.png")+Style::background::repeat::norepeat+Style::background::position::center_center+Style::background::size::contain);
    container->setPadding(50,Side::Top|Side::Bottom);
    container->setHeight(50);


    {
        auto odul1 = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
        //            odul1->addStyleClass(Bootstrap::ImageShape::img_thumbnail);
        odul1->addStyleClass(Bootstrap::Grid::Large::col_lg_4+Bootstrap::Grid::Medium::col_md_4+Bootstrap::Grid::Small::col_sm_4+Bootstrap::Grid::ExtraSmall::col_xs_12);
        odul1->setAttributeValue(Style::style,Style::background::url("fold/1.png")+Style::background::size::contain+Style::background::repeat::norepeat+Style::background::position::center_center);
        odul1->setHeight(250);
    }

    {
        auto odul1 = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
        //            odul1->addStyleClass(Bootstrap::ImageShape::img_thumbnail);
        odul1->addStyleClass(Bootstrap::Grid::Large::col_lg_4+Bootstrap::Grid::Medium::col_md_4+Bootstrap::Grid::Small::col_sm_4+Bootstrap::Grid::ExtraSmall::col_xs_6);
        odul1->setAttributeValue(Style::style,Style::background::url("fold/2.png")+Style::background::size::contain+Style::background::repeat::norepeat+Style::background::position::center_center);
        odul1->setHeight(250);
    }

    {
        auto odul1 = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
        //            odul1->addStyleClass(Bootstrap::ImageShape::img_thumbnail);
        odul1->addStyleClass(Bootstrap::Grid::Large::col_lg_4+Bootstrap::Grid::Medium::col_md_4+Bootstrap::Grid::Small::col_sm_4+Bootstrap::Grid::ExtraSmall::col_xs_6);
        odul1->setAttributeValue(Style::style,Style::background::url("fold/3.png")+Style::background::size::contain+Style::background::repeat::norepeat+Style::background::position::center_center);
        odul1->setHeight(250);
    }

    {
        auto odul1 = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
        odul1->addStyleClass(Bootstrap::ImageShape::img_thumbnail);
        odul1->addStyleClass(Bootstrap::Grid::Large::col_lg_4+Bootstrap::Grid::Medium::col_md_4+Bootstrap::Grid::Small::col_sm_4+Bootstrap::Grid::ExtraSmall::col_xs_12);
        odul1->setHeight(175);
        odul1->setMargin(20,Side::Top);
        auto vLayout = odul1->setLayout(cpp14::make_unique<WVBoxLayout>());
        vLayout->addStretch(1);
        vLayout->addWidget(cpp14::make_unique<WText>("<h2>4. - 10. Arası</h2>"))->setAttributeValue(Style::style,Style::color::color(Style::color::Grey::Black));
        auto tlText = vLayout->addWidget(cpp14::make_unique<WText>("<h2><b>1000 ₺</b></h2>"));
        tlText->setAttributeValue(Style::style,Style::color::color(Style::color::Grey::Black)+Style::background::color::rgb(234,165,56));
//        tlText->setPadding(10,Side::Top|Side::Bottom);
        vLayout->addStretch(1);
    }

    {
        auto odul1 = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
        odul1->addStyleClass(Bootstrap::ImageShape::img_thumbnail);
        odul1->addStyleClass(Bootstrap::Grid::Large::col_lg_4+Bootstrap::Grid::Medium::col_md_4+Bootstrap::Grid::Small::col_sm_4+Bootstrap::Grid::ExtraSmall::col_xs_6);
        odul1->setHeight(175);
        odul1->setMargin(20,Side::Top);
        auto vLayout = odul1->setLayout(cpp14::make_unique<WVBoxLayout>());
        vLayout->addStretch(1);
        vLayout->addWidget(cpp14::make_unique<WText>("<h2>11. - 20. Arası</h2>"))->setAttributeValue(Style::style,Style::color::color(Style::color::Grey::Black));
        auto tlText = vLayout->addWidget(cpp14::make_unique<WText>("<h2><b>750 ₺</b></h2>"));
        tlText->setAttributeValue(Style::style,Style::color::color(Style::color::Grey::Black)+Style::background::color::rgb(234,165,56));
//        tlText->setPadding(10,Side::Top|Side::Bottom);
        vLayout->addStretch(1);
    }

    {
        auto odul1 = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
        odul1->addStyleClass(Bootstrap::ImageShape::img_thumbnail);
        odul1->addStyleClass(Bootstrap::Grid::Large::col_lg_4+Bootstrap::Grid::Medium::col_md_4+Bootstrap::Grid::Small::col_sm_4+Bootstrap::Grid::ExtraSmall::col_xs_6);
        odul1->setHeight(175);
        odul1->setMargin(20,Side::Top);
        auto vLayout = odul1->setLayout(cpp14::make_unique<WVBoxLayout>());
        vLayout->addStretch(1);
        vLayout->addWidget(cpp14::make_unique<WText>("<h2>21. - 30. Arası</h2>"))->setAttributeValue(Style::style,Style::color::color(Style::color::Grey::Black));
        auto tlText = vLayout->addWidget(cpp14::make_unique<WText>("<h2><b>500 ₺</b></h2>"));
        tlText->setAttributeValue(Style::style,Style::color::color(Style::color::Grey::Black)+Style::background::color::rgb(234,165,56));
//        tlText->setPadding(10,Side::Top|Side::Bottom);
        vLayout->addStretch(1);
    }


}
