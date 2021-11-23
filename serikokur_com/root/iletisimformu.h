#ifndef ILETISIMFORMU_H
#define ILETISIMFORMU_H


#include "item.h"
#include "listitem.h"


namespace SKey {


namespace IletisimForm {

const std::string Collection{"iletisimForm"};
static const std::string adsoyad{"adsoyad"};
static const std::string eposta{"eposta"};
static const std::string telefon{"telefon"};
static const std::string mesaj{"mesaj"};

}


}


class IletisimFormu : public SerikBLDCore::Item
{
public:
    IletisimFormu();

    IletisimFormu& setAdSoyad( const std::string &adsoyad);
    std::string getAdSoyad() const;


    IletisimFormu& setEPosta( const std::string &eposta );
    std::string getEPosta() const;


    IletisimFormu& setTelefon( const std::string &telefon );
    std::string getTelefon() const;

    IletisimFormu& setMesaj( const std::string &mesaj);
    std::string getMesaj() const;






    virtual void errorOccured(const std::string &errorText) override{

    }
};


class IletisimFormManager : public SerikBLDCore::ListItem<IletisimFormu>
{
public:
    IletisimFormManager( SerikBLDCore::DB* _mDB );

    virtual void onList(const QVector<IletisimFormu> *mlist) override;
};

#endif // ILETISIMFORMU_H
