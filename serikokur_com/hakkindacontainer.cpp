#include "hakkindacontainer.h"

HakkindaContainer::HakkindaContainer()
{

    setId("hakkindaid");
    setAttributeValue(Style::style,Style::background::color::rgba(125,150,225));

    auto container = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());

    container->setPadding(50,Side::Top|Side::Bottom);


    auto titleText = container->addWidget(cpp14::make_unique<WText>("<h3>HAKKINDA</h3>"));
    titleText->setMargin(50,Side::Top);

    titleText->setAttributeValue(Style::style,Style::color::color(Style::color::Grey::Black));


    auto text = container->addWidget(cpp14::make_unique<WText>("<h4><p align=\"justify\">Serik ilçesi genelindeki yaşı ve eğitim düzeyi fark etmeksizin tüm vatandaşlara "
                                                                    "kitap okuma alışkanlığı kazandırmak ve okunan kitap sayısını arttırmaktır.</p>"
                                                                    "<p align=\"justify\">Aile bağlarının güçlenmesi, genç ve yetişkin fark etmeksizin aynı kitap üzerinde "
                                                                    "fikir alışverişi yapılabilmesi, ailenin sohbet bağlamının kültür ve edebiyat üzerine "
                                                                    "olarak dönüştürülmesi, sosyal medya ve televizyon gibi mavi ekranlardan uzakta vakit "
                                                                    "geçirilmesine yardımcı ve teşvik edici olması amaçlanmaktadır.</p></h4>"));
    text->setAttributeValue(Style::style,Style::color::color(Style::color::Grey::Black));
    text->setTextAlignment(AlignmentFlag::Justify);
    text->setMargin(40,Side::Top);
    text->setMargin(15,Side::Left|Side::Right);

}
