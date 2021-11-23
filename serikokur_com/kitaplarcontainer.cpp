#include "kitaplarcontainer.h"

KitaplarContainer::KitaplarContainer()
{
    this->setId("kitaplarid");

    setAttributeValue(Style::style,Style::background::color::rgba(25,75,140));

    this->setContentAlignment(AlignmentFlag::Center);
    this->Content()->setMaximumSize(1280,WLength::Auto);
    this->Content()->setContentAlignment(AlignmentFlag::Center);

    this->setPositionScheme(PositionScheme::Relative);

    {
        auto kapcontainer = this->addWidget(cpp14::make_unique<WContainerWidget>());
        kapcontainer->setPositionScheme(PositionScheme::Absolute);
        kapcontainer->setOffsets(0,Side::Bottom|Side::Right);
        kapcontainer->setHeight(200);
        kapcontainer->setWidth(300);
        kapcontainer->setAttributeValue(Style::style,Style::background::url("fold/parasut.png")+
                                        Style::background::size::contain+
                                        Style::background::repeat::norepeat+
                                        Style::background::position::center_center);
    }


    setPadding(40,Side::Bottom);

    auto container = this->Content()->addWidget(cpp14::make_unique<WContainerWidget>());
    //    container->setAttributeValue(Style::style,Style::background::color::rgba(75,75,75,0.9));
    //    container->setZIndex(999);
    container->addStyleClass(Bootstrap::Grid::col_full_12);

    container->setPadding(50,Side::Top|Side::Bottom);

    auto rContainer = container->addWidget(cpp14::make_unique<WContainerWidget>());
    rContainer->addStyleClass(Bootstrap::Grid::row);

    {
        auto kContainer = rContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        kContainer->addStyleClass(Bootstrap::Grid::col_full_12);
        kContainer->setContentAlignment(AlignmentFlag::Center);
        auto text = kContainer->addWidget(cpp14::make_unique<WText>("<h3><b>Kitaplar</b></h3>"));
        text->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue));
    }


    rContainer->addWidget(cpp14::make_unique<KitapContainer>("Deli Tarla","ŞERMİN YAŞAR","1.dc197a9a.jpg"))
            ->setBilgi( "<p>Bazen hayat gizler kendini… Sımsıkı çekilmiş perdelerin ardına saklanan"
                        " utangaç eviçlerinde, kapıların ardında, güneşin terk ettiği sokaklarda, "
                        "o bıyıkaltı gülüşlerde, mühürlenmiş ağızlarda, yüze düşen gölgelerde, ketum "
                        "yüreklerde, harflerin kıvrımlarında, kelimelerin dilsizliğinde, sonsuz susuşlarda,"
                        " hiç düşülmeyen yollarda, hep beklenen aşklarda, hiç beklenmedik sonlarda gizler kendini hayat…</p>"
                        "<p></p><p>Ta ki bir yazar onu bulup çıkarıncaya dek.</p>"
                        "<p>Ta ki bir yazar onu bize anlatıncaya dek.</p>"
                        "<p></p><p>Şermin Yaşar’dan “yeniden gülmeyi başarabilen insanların muamması” için öyküler. Deli Tarla gibi coşkulu, beklenmedik ve merhamete muhtaç…</p>");

    rContainer->addWidget(cpp14::make_unique<KitapContainer>("Fatih-i Harbiye","PEYAMİ SAFA","2.3ca6bb44.jpg"))
            ->setBilgi("Darülelhan'ın (Konservatuvarın) alaturka kısmında ud eğitimi alan Neriman, mensup olmakla iftihar ettiği Doğu kültürünü çok seven babası Faiz Bey'le on beş yaşından beri Fatih semtinde oturmaktadır. Yine bu semtte ta­nıştığı, babasına çok benzeyen ve Darülelhan'da kemençe eğitimi alan Şinasi ile yedi yıldır nişanlı­dır. Bütün mahalle, tahammül sınırlarını zorlayan bu nişanlılık ilişkisinin evlilikle bitmesini beklemektedir. Ancak Neriman'ın Darülelhan'da tanıştığı Macit, onun içinde yer etmiş Batılı bir hayat yaşama isteğini uyandırır. Neriman, Beyoğlu'nda, Harbiye'de yaşanan ışıltılı hayat tarzına imrenerek yaşadığı muhitten, evlerinden, babasın­dan, Şinasi'den ve hatta doğuyu temsil ettiğini düşündüğü kedisinden bile nefret etmeye başlar. Tramvay yoluyla birbirine bağlanan ama birbiriyle bağdaşması mümkün olmayan iki semt, Fatih ve Harbiye, aynı coğrafyada yaşanan bir kültür ve zihin geriliminin cepheleridir. Türk edebiyatının en üretken kalemi Peyami Safa, televizyon dizilerine de konu olan Fatih-Harbiye romanında toplumumuzun yaşadığı asrîleşme (çağdaşlaşma) sancılarına eşyalar, şahıslar, kurumlar ve mekânlar üzerinden ayna tutmaktadır.");

    rContainer->addWidget(cpp14::make_unique<KitapContainer>("Mücella","NAZAN BEKİROĞLU","3.a433b89d.jpg"))
            ->setBilgi("<p><b>Mücellâ</b>, genç Cumhuriyet’le yaşıt bir kızın, unutulmuş kumaşların, kokuların, "
"alışkanlıkların, iğne oyalarının, kimi yarım kalmış kimi tamamlanmış aşkların, hayatı seyretmekle yaşamak arasında gelip giden kadınların romanı.</p>"
"<p>Zamanın daha ağır aktığı, hayatın ritminin daha çok mahalle aralarında karar bulduğu vakitler. Gaz lâmbasının ışığında içilen nohut kahvesinin ağızda buruk bir tat bıraktığı dönemler.</p>"
"<p>Arka planda Türkiye, pek çok çalkantının içinden geçerken bile kendini bildi bileli çeyiz işleyen bir genç kız Mücellâ. Adım adım hayattan çekilirken bunu neredeyse hiç fark etmeyen... "
"Neyi beklediğini bilmeden bekleyen... Derken günün birinde, kıyısında kaldığı hayata son bir çabayla dönmek isteyen...</p>"
"<p>Sümbül kokulu bembeyaz yastık kılıfları, kanaviçe işli peçeteler, uçları fistolanmış havlular, çeyiz sandıkları arasında…</p>"
"<p>Hanımeli, yasemin ve leylâk kokulu yaz ikindileri gibi uzun kış gecelerinde de, ya çardağın altında ya hep o soldaki pencerenin içinde...</p>"
"<p>Mücellâ’nın dupduru ve çarpıcı hikâyesi.</p>");

    rContainer->addWidget(cpp14::make_unique<KitapContainer>("101 Deyim 101 Öykü","SÜLEYMAN BULUT","4.c6d96be5.jpg"))
            ->setBilgi("<p><b>Deyimlerin Öykülerini Merak Ediyor musunuz?</b></p>"
"<p>Süleyman Bulut tarafından yazılan 101 Deyim: 101 Öykü, keyifli içeriği "
"ile okuyucuların sıkılmadan okuyacakları eserler arasında yer alıyor. "
"Kitap, içerisinde 101 adet deyim bulunduruyor. İçinde bulunan 101 adet "
"deyimin nasıl çıktığını ve hangi olaylar esnasında kullanıldığını öykü "
"tadında anlatan eser, deyimlerin bir olay esnasında bir kahraman tarafından "
"kullanıldığını anlatıyor. Deyimlerin bugünkü hâllerine nasıl geldiğini, "
"hangi deyimlerin hangi olaylar sırasında nasıl kullanıldığını anlatan eser, "
"hem çocuklar hem de yetişkinler için mutlaka okunması; kitapseverlerin "
"kütüphanelerinde bulundurması gereken yayınlar arasında bulunuyor. Yazar "
"Süleyman Bulut, deyimlerin ortaya çıktığı olayları araştırmış, derlemiş, "
"toplamış ve yeniden kaleme alarak bu güzide eserin oluşmasın sağlamış. "
"Yazar, 101 adet deyimin 101 ilginç, keyifli ve eğlenceli hikâyesini "
"101 Deyim: 101 Öykü kitabında bir araya getirmiş ve okuyucuların deneyimine sunmuştur. "
"101 Deyim: 101 Öykü kitabı, genel olarak çocuklar adına yazılmış ve çocukların deyimleri "
"sıkılmadan okuyarak öğrenmesini, hafızalarında yer etmesini amaçlamıştır.</p>");

    rContainer->addWidget(cpp14::make_unique<KitapContainer>("Acımak","REŞAT NURİ GÜNTEKİN","9.c9233dac.jpg"))
            ->setBilgi( "<p><b>Acımayı Bilmeyen Bir Öğretmenin Romanı</b></p>"
                        "<p>Mektebin başmuallimi olan Zehra, yeni eğitim "
                        "öğretimin tüm gereklerini yerine getirirken aynı "
                        "zamanda öğrencileri ile birebir ilgilenir. Fakat, "
                        "öğrencilerin yaptıkları yanlışları asla affetmeden, "
                        "hiçbir koşulda acıma duygusu hissetmez. Bu durumun "
                        "farkına varan maarif müdürü Tevfik Hayri ve Vekil "
                        "Şerif Hayri Bey Zehra’nın okuluna giderek, babasının "
                        "hasta olduğunu söylediklerinde Zehra, İstanbul’a "
                        "babasını görmeye gitmemek için direnir. Sonrasında "
                        "fikrini değiştirerek İstanbul’a doğru yola çıkar ve "
                        "vardığında babasının öldüğünü öğrenir. Zehra’ya babasının "
                        "eşyalarının olduğu sandığın anahtarı verilir. Ve Zehra, "
                        "sandıktan bulduğu günlükte daha önce bildiği her şeyin tam "
                        "tersi olduğunu öğrenerek, acıma duygusunu öğrenir. Reşat Nuri "
                        "Güntekin, bu eserinde Cumhuriyet öncesinin toplumsal yapısını "
                        "açık bir şekilde ortaya koyarken, sosyal yaşamın çatışmalarını "
                        "da gözler önüne koyar. Acımak, aile ilişkilerini ve aile olmanın "
                        "getirdiği sorumlulukları adeta bir ders gibi okuyucuya anlatır.</p>");

}

KitapContainer::KitapContainer(const std::string &name, const std::string &yazar, const std::string &url)
    :mTitle(name),mYazar(yazar)
{
    this->clear();
    this->addStyleClass(Bootstrap::Grid::Large::col_lg_3+Bootstrap::Grid::Medium::col_md_3+Bootstrap::Grid::Small::col_sm_4+Bootstrap::Grid::ExtraSmall::col_xs_6);


    auto vLayout = this->setLayout(cpp14::make_unique<WVBoxLayout>());



    auto kapakContainer = vLayout->addWidget(cpp14::make_unique<WContainerWidget>());
    kapakContainer->setHeight(200);
    kapakContainer->setAttributeValue(Style::style,Style::background::url(url)+
                                      Style::background::size::contain+
                                      Style::background::position::center_center+
                                      Style::background::repeat::norepeat);
    kapakContainer->decorationStyle().setCursor(Cursor::PointingHand);
    kapakContainer->clicked().connect([=](){
        this->informDialog(mTitle + " - " + mYazar,mBilgi);
    });

    auto textContainer = vLayout->addWidget(cpp14::make_unique<WContainerWidget>());

    textContainer->addWidget(cpp14::make_unique<WText>("<h4><p align=\"center\"><b>"+name+"</b></p></h4>"
                                                       "<h5><p align=\"center\">"+yazar+"</p></h5>"));
    textContainer->setAttributeValue(Style::style,Style::color::color(Style::color::White::AliceBlue));


}

void KitapContainer::setBilgi(const std::string &newBilgi)
{
    mBilgi = newBilgi;
}
