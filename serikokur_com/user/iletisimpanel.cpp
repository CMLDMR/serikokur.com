#include "iletisimpanel.h"
#include "root/css.h"

IletisimPanel::IletisimPanel(DB *_mDB)
    : ContainerWidget("Mesajlar"),
      IletisimFormManager(_mDB)
{
    this->setMargin(25,Side::Top);
    this->setMargin(75,Side::Bottom);

    this->UpdateList();

}

void IletisimPanel::onList(const QVector<IletisimFormu> *mlist)
{

    this->Content()->clear();


    for( auto item : *mlist ){


        auto container = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
        container->setMargin(5,Side::Top|Side::Bottom);
        container->addStyleClass(Bootstrap::Grid::col_full_12);
        container->addStyleClass(CSSStyle::Radius::radius3px+CSSStyle::Shadows::shadow8px);
        container->addStyleClass(CSS::BackGround::LightBluePurple);


        auto rContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
        rContainer->addStyleClass(Bootstrap::Grid::row);

        {
            auto text = rContainer->addWidget(cpp14::make_unique<WText>(item.getAdSoyad()));
            text->addStyleClass(Bootstrap::Grid::Large::col_lg_4+
                                Bootstrap::Grid::Medium::col_md_4+
                                Bootstrap::Grid::Small::col_sm_3+
                                Bootstrap::Grid::ExtraSmall::col_xs_6);
        }

        {
            auto text = rContainer->addWidget(cpp14::make_unique<WText>(item.getTelefon()));
            text->addStyleClass(Bootstrap::Grid::Large::col_lg_4+
                                Bootstrap::Grid::Medium::col_md_4+
                                Bootstrap::Grid::Small::col_sm_3+
                                Bootstrap::Grid::ExtraSmall::col_xs_6);
        }

        {
            auto text = rContainer->addWidget(cpp14::make_unique<WText>(item.getEPosta()));
            text->addStyleClass(Bootstrap::Grid::Large::col_lg_4+
                                Bootstrap::Grid::Medium::col_md_4+
                                Bootstrap::Grid::Small::col_sm_6+
                                Bootstrap::Grid::ExtraSmall::col_xs_12);
        }

//        {
//            auto text = rContainer->addWidget(cpp14::make_unique<WText>(item.getDate()->toString("dd/MMM/yyyy").toStdString()));
//            text->addStyleClass(Bootstrap::Grid::Large::col_lg_2+
//                                Bootstrap::Grid::Medium::col_md_2+
//                                Bootstrap::Grid::Small::col_sm_6+
//                                Bootstrap::Grid::ExtraSmall::col_xs_6);
//        }

//        {
//            auto text = rContainer->addWidget(cpp14::make_unique<WText>(item.getTime()->toString("hh:mm").toStdString()));
//            text->addStyleClass(Bootstrap::Grid::Large::col_lg_2+
//                                Bootstrap::Grid::Medium::col_md_2+
//                                Bootstrap::Grid::Small::col_sm_6+
//                                Bootstrap::Grid::ExtraSmall::col_xs_6);
//        }

        {
            auto text = rContainer->addWidget(cpp14::make_unique<WText>("<b>"+item.getMesaj()+"</b>"));
            text->addStyleClass(Bootstrap::Grid::col_full_12);
            text->setMargin(15,Side::Top|Side::Bottom);
        }
    }


}
