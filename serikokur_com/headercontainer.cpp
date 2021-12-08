#include "headercontainer.h"

HeaderContainer::HeaderContainer()
{
    //    setHeight(100);
    //    setAttributeValue(Style::style,Style::background::color::color(Style::color::Green::DarkGreen));
    setMaximumSize(1280,WLength::Auto);
    setContentAlignment(AlignmentFlag::Center);
    auto boostrapStr = Bootstrap::Grid::Large::col_lg_2+Bootstrap::Grid::Medium::col_md_2+Bootstrap::Grid::Small::col_sm_4+Bootstrap::Grid::ExtraSmall::col_xs_6;
    {
        auto container = Content()->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(boostrapStr);
        auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());
        vLayout->addWidget(cpp14::make_unique<WText>("<b>SerikOkuyor</b>"));
        container->addStyleClass("button");
        container->setAttributeValue(Style::style,Style::background::color::rgb(53,175,251));
        container->clicked().connect([=]() {
            _mainClicked.emit(NoClass());
        });
    }

    {
        auto container = Content()->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(boostrapStr);
        auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());
        vLayout->addWidget(cpp14::make_unique<WText>("<b>Başkanımız</b>"));
        container->addStyleClass("button");
        container->setAttributeValue(Style::style,Style::background::color::rgb(8,119,238));
        container->clicked().connect([=](){
            container->doJavaScript("var elmnt = document.getElementById(\"baskanid\");"
                                    "if( elmnt ) { elmnt.scrollIntoView();}");
        });
    }

    {
        auto container = Content()->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(boostrapStr);
        auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());
        vLayout->addWidget(cpp14::make_unique<WText>("<b>Hakkında</b>"));
        container->addStyleClass("button");
        container->setAttributeValue(Style::style,Style::background::color::rgb(53,175,251));
        container->clicked().connect([=](){
            container->doJavaScript("var elmnt = document.getElementById(\"hakkindaid\");"
                                    "if( elmnt ) { elmnt.scrollIntoView();}");
        });
    }

    {
        auto container = Content()->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(boostrapStr);
        auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());
        vLayout->addWidget(cpp14::make_unique<WText>("<b>İletişim</b>"));
        container->addStyleClass("button");
        container->setAttributeValue(Style::style,Style::background::color::rgb(8,119,238));
        container->clicked().connect([=](){
            container->doJavaScript("var elmnt = document.getElementById(\"iletisimid\");"
                                    "if( elmnt ) { elmnt.scrollIntoView();}");
        });
    }

    {
        auto container = Content()->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(boostrapStr);
        auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());
        auto text = vLayout->addWidget(cpp14::make_unique<WText>("<b>Kitaplar</b>"));
        container->addStyleClass("button");
        container->setAttributeValue(Style::style,Style::background::color::rgb(53,175,251));
        container->clicked().connect([=](){
            container->doJavaScript("var elmnt = document.getElementById(\"kitaplarid\");"
                                    "if( elmnt ) { elmnt.scrollIntoView();}");
        });
    }

    {
        auto container = Content()->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass(boostrapStr);
        auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());
        vLayout->addWidget(cpp14::make_unique<WText>("<b>Başvuru</b>"));
        container->addStyleClass("button");
        container->setAttributeValue(Style::style,Style::background::color::rgb(255,174,0));
        container->clicked().connect([=](){

            if( WDate::currentDate().toJulianDay() >= WDate(2021,12,1).toJulianDay() ){
                this->informDialog("Başvurular Sona Erdi");
            }else{
                _basvuruClicked.emit(NoClass());
            }
        });



    }


}

Signal<NoClass> &HeaderContainer::MainClicked()
{
    return _mainClicked;
}

Signal<NoClass> &HeaderContainer::BasvuruClicked()
{
    return _basvuruClicked;
}
