#include "iletisimformu.h"

IletisimFormu::IletisimFormu()
    :SerikBLDCore::Item(SKey::IletisimForm::Collection)
{

}

IletisimFormu &IletisimFormu::setAdSoyad(const std::string &adsoyad)
{
    this->append(SKey::IletisimForm::adsoyad,adsoyad);
    return *this;
}

std::string IletisimFormu::getAdSoyad() const
{
    auto val = this->element(SKey::IletisimForm::adsoyad);
    if( val ){
        return val.value().get_utf8().value.to_string();
    }
    return "";
}



IletisimFormu &IletisimFormu::setEPosta(const std::string &eposta)
{
    this->append(SKey::IletisimForm::eposta,eposta);
    return *this;
}

std::string IletisimFormu::getEPosta() const
{
    auto val = this->element(SKey::IletisimForm::eposta);
    if( val ){
        return val.value().get_utf8().value.to_string();
    }
    return "";
}

IletisimFormu &IletisimFormu::setTelefon(const std::string &telefon)
{
    this->append(SKey::IletisimForm::telefon,telefon);
    return *this;
}

std::string IletisimFormu::getTelefon() const
{
    auto val = this->element(SKey::IletisimForm::telefon);
    if( val ){
        return val.value().get_utf8().value.to_string();
    }
    return "";
}

IletisimFormu &IletisimFormu::setMesaj(const std::string &mesaj)
{
    this->append(SKey::IletisimForm::mesaj,mesaj);
    return *this;
}

std::string IletisimFormu::getMesaj() const
{
    auto val = this->element(SKey::IletisimForm::mesaj);
    if( val ){
        return val.value().get_utf8().value.to_string();
    }
    return "";
}









IletisimFormManager::IletisimFormManager(DB *_mDB)
    :SerikBLDCore::ListItem<IletisimFormu>(_mDB)
{

}

void IletisimFormManager::onList(const QVector<IletisimFormu> *mlist)
{



}
