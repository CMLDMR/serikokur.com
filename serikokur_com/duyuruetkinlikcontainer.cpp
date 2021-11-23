#include "duyuruetkinlikcontainer.h"

DuyuruEtkinlikContainer::DuyuruEtkinlikContainer()
{
    this->setId("duyuruid");
    this->initDuyurular();

    this->initEtkinlik();

    this->setPositionScheme(PositionScheme::Relative);

    {
        auto kapcontainer = this->addWidget(cpp14::make_unique<WContainerWidget>());
        kapcontainer->setPositionScheme(PositionScheme::Absolute);
        kapcontainer->setOffsets(0,Side::Bottom);
        kapcontainer->setOffsets(WLength("40%"),Side::Left);
        kapcontainer->setHeight(200);
        kapcontainer->setWidth(300);
        kapcontainer->setAttributeValue(Style::style,Style::background::url("fold/cam.png")+
                                        Style::background::size::contain+
                                        Style::background::repeat::norepeat+
                                        Style::background::position::center_center);
    }
}

void DuyuruEtkinlikContainer::initDuyurular()
{
    auto container = this->Content()->addWidget(cpp14::make_unique<DuyuruContainer>());
    container->addStyleClass(Bootstrap::Grid::Large::col_lg_6+
                             Bootstrap::Grid::Medium::col_md_6+
                             Bootstrap::Grid::Small::col_sm_12+
                             Bootstrap::Grid::ExtraSmall::col_xs_12);

    container->setHeight(600);
    container->setAttributeValue(Style::style,Style::background::color::color(Style::color::Green::Chartreuse));
}

void DuyuruEtkinlikContainer::initEtkinlik()
{
    auto container = this->Content()->addWidget(cpp14::make_unique<EtkinlikContainer>());
    container->addStyleClass(Bootstrap::Grid::Large::col_lg_6+
                             Bootstrap::Grid::Medium::col_md_6+
                             Bootstrap::Grid::Small::col_sm_12+
                             Bootstrap::Grid::ExtraSmall::col_xs_12);

    container->setHeight(600);
    container->setAttributeValue(Style::style,Style::background::color::color(Style::color::Green::DarkSeaGreen));
}

DuyuruContainer::DuyuruContainer()
{

    this->Header()->setContentAlignment(AlignmentFlag::Center);
    this->Header()->addWidget(cpp14::make_unique<WText>("<h3>Duyurular</h3>"));

}

EtkinlikContainer::EtkinlikContainer()
{
    this->Header()->setContentAlignment(AlignmentFlag::Center);
    this->Header()->addWidget(cpp14::make_unique<WText>("<h3>Etkinlikler</h3>"));
}
