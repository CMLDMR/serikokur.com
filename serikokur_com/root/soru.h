#ifndef SORU_H
#define SORU_H

#include "item.h"
#include "listitem.h"
#include "root/user.h"
#include <random>
#include <algorithm>

namespace SKey {

namespace Soru {

static const std::string Collection{"Sorular"};
static const std::string soru{"soru"};
static const std::string cevaplar{"cevaplar"};
static const std::string cevapindex{"cevapindex"};
static const std::string ekleyen{"ekleyen"};
static const std::string onay{"onay"};
static const std::string zorluk{"zorluk"};
static const std::string deleted{"deleted"};
static const std::string kaynak{"kaynak"};
static const std::string kitap{"kitap"};



namespace Cevap {
static const std::string index{"index"};
static const std::string cevap{"cevap"};
}

namespace Onay {
static const std::string onay{"onay"};
static const std::string onaylayanoid{"onaylayanoid"};
static const std::string aciklama{"aciklama"};
}

}



}


class Soru : public SerikBLDCore::Item
{
public:
    Soru();

    struct cevap{
        int index;
        std::string Cevap;
    };

    struct onay{
        std::string owner;
        bool Onay;
        std::string aciklama;
    };

    Soru& setSoru( const std::string &soru);
    std::string getSoru() const;

    Soru& setOwner( const std::string &ownerOid);
    Soru& setCevapIndex( const int &cevapIndex );
    Soru& setZorluk( const std::int32_t &zorluk );
    Soru& Delete();
    Soru& UnDelete();
    Soru& setKaynak(const std::string &kaynak );
    Soru& setKitap( const std::string &kitap);

    bool addCevap( const std::string &cevap,const int &index);
    bool addOnay( const bool &onay, const std::string &onaylayanOid, const std::string &aciklama = "");


    std::map<std::string,int> getCevaplar() const;
    std::vector<cevap> getCevaplarStruct() const;
    std::vector<cevap> getShufledCevaplarStruct() const;

    std::vector<onay> getOnayStruct() const;

    std::string getEkleyen() const;
    std::string getOwner() const;

    int getCevapIndex() const;

    std::int32_t getZorluk() const;

    bool isDeleted() const;

    std::string getKaynak() const;
    std::string getKitap() const;



    int onayCount() const;
    int redCount() const;


    ///
    /// Oylama Sayisi Red + Onay
    /// \return
    ///
    int voteCount() const;

    ///
    /// Aciklama : Soru Yeterli Oy ve Yeterli Onay Almissa Soru Onaylanmistir.
    /// En az 3 Oy ve Onay > Red Olmasi Gerekli
    /// \return
    ///
    bool isGecerli() const;


    virtual void errorOccured(const std::string &errorText) override;

    const std::string &lastError() const;

private:
    std::string mLastError;
};




class SoruManager : public SerikBLDCore::ListItem<Soru>
{
public:
    SoruManager( SerikBLDCore::DB* _mDB, User* _mUser );

    virtual void onList(const QVector<Soru> *mlist) override;

    User* CurrentUser() const;
private:
    User* mUser;
};

#endif // SORU_H
