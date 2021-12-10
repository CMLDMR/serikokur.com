#ifndef BASVURUITEM_H
#define BASVURUITEM_H

#include "item.h"
#include "listitem.h"
#include <QString>


namespace SKey {

static const QString LetterSTR{"QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm123456789"};

namespace BasvuruItem {

static const std::string Collection{"basvuru"};
static const std::string adsoyad{"adsoyad"};
static const std::string tcno{"tcno"};
static const std::string cep{"cep"};
static const std::string mail{"mail"};
static const std::string adres{"adres"};
static const std::string cinsiyet{"cinsiyet"};
static const std::string egitim{"egitim"};
static const std::string yasaralik{"yasaralik"};
static const std::string aileKac{"aileKac"};
static const std::string arkadasKac{"arkadasKac"};
static const std::string nerdenduydunuz{"nerdenduydunuz"};
static const std::string nasilKatilirim{"nasilKatilirim"};
static const std::string onayli{"onayli"};
static const std::string password{"password"};

namespace Cinsiyet {
static const std::string kadin{"Kadın"};
static const std::string erkek{"Erkek"};
}

namespace YasAralik {
static const std::string yas10_14{"10-14"};
static const std::string yas15_18{"15-18"};
static const std::string yas19_25{"19-25"};
static const std::string yas26_35{"26-35"};
static const std::string yas36_50{"36-50"};
static const std::string yas50Uzeri{"50 Üzeri"};
}

namespace Egitim {
static const std::string ilkOkul{"İlkokul"};
static const std::string ortaOkul{"Ortaokul"};
static const std::string lise{"Lise"};
static const std::string onlisans{"Önlisans"};
static const std::string lisans{"Lisans"};
static const std::string yukselLisans{"Yüksek Lisans"};
static const std::string doktora{"Doktora"};
}

namespace Nerden {
static const std::string sosyalMedya{"Sosyal Medya"};
static const std::string okul{"Okul"};
static const std::string afis{"Afiş"};
static const std::string arkadas{"Arkadaş"};
}

namespace KatilimTuru {
static const std::string cevrimici{"Sınav Çevrim içi Yapılırsa Katılırım"};
static const std::string yuzyuze{"Sınav Yüzyüze Yapılırsa Katılırım"};
static const std::string herikisi{"Sınava İki Türlü de Katılabilirim"};
}

}


}


class BasvuruItem : public SerikBLDCore::Item
{
public:
    BasvuruItem();

    std::string getAdSoyad() const;
    std::string getTCNO() const;
    std::string getCepNo() const;
    std::string getMail() const;
    std::string getAdres() const;
    std::string getCinsiyet() const;
    std::string getEgitim() const;
    std::string getYasAralik() const;
    std::string getAileKatilim() const;
    std::string getArkadasKatilim() const;
    std::string getNereden() const;
    std::string getNasilKatilirim() const;
    bool getOnay() const;

    BasvuruItem& setOnay( const bool &onay );
    BasvuruItem& setCinsiyet(const bool &kadin = true );

    BasvuruItem& setYasAralik(const std::string &yasAralik );

    BasvuruItem& setEgitim( const std::string &egitim );

    BasvuruItem& setNerden( const std::string &nerden);

    BasvuruItem& setKatilimTuru( const std::string &katilimTuru);

    BasvuruItem& setTCNO( const std::string &tcno );

    BasvuruItem& setPassword( const std::string &password );

};



class BasvuruManager : public SerikBLDCore::ListItem<BasvuruItem>
{
public:
    BasvuruManager(SerikBLDCore::DB* _mDB);

    virtual void onList(const QVector<BasvuruItem> *mlist) override;

    virtual void errorOccured(const std::string &errorText) override;

    const std::string &lastError() const;

private:
    std::string mLastError;
};

#endif // BASVURUITEM_H
