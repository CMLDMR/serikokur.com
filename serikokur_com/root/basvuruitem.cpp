#include "basvuruitem.h"

BasvuruItem::BasvuruItem()
    :SerikBLDCore::Item(SKey::BasvuruItem::Collection)
{

}

std::string BasvuruItem::getAdSoyad() const
{
    auto val = this->element(SKey::BasvuruItem::adsoyad);
    if( val ){
        return val->get_utf8().value.to_string();
    }
    return "";
}

std::string BasvuruItem::getCinsiyet() const
{
    auto val = this->element(SKey::BasvuruItem::cinsiyet);
    if( val ){
        return val->get_utf8().value.to_string();
    }
    return "";
}

std::string BasvuruItem::getEgitim() const
{
    auto val = this->element(SKey::BasvuruItem::egitim);
    if( val ){
        return val->get_utf8().value.to_string();
    }
    return "";
}

std::string BasvuruItem::getYasAralik() const
{
    auto val = this->element(SKey::BasvuruItem::yasaralik);
    if( val ){
        return val->get_utf8().value.to_string();
    }
    return "";
}

std::string BasvuruItem::getAileKatilim() const
{
    auto val = this->element(SKey::BasvuruItem::aileKac);
    if( val ){
        return std::to_string(val->get_int32().value);
    }
    return "";
}

std::string BasvuruItem::getArkadasKatilim() const
{
    auto val = this->element(SKey::BasvuruItem::arkadasKac);
    if( val ){
        return std::to_string(val->get_int32().value);
    }
    return "";
}

std::string BasvuruItem::getNereden() const
{
    auto val = this->element(SKey::BasvuruItem::nerdenduydunuz);
    if( val ){
        return val->get_utf8().value.to_string();
    }
    return "";
}

std::string BasvuruItem::getNasilKatilirim() const
{
    auto val = this->element(SKey::BasvuruItem::nasilKatilirim);
    if( val ){
        return val->get_utf8().value.to_string();
    }
    return "";
}

bool BasvuruItem::getOnay() const
{
    auto val = this->element(SKey::BasvuruItem::onayli);
    if( val ){
        return val->get_bool().value;
    }
    return false;
}

BasvuruItem &BasvuruItem::setOnay(const bool &onay)
{
    this->append(SKey::BasvuruItem::onayli,onay);
    return *this;
}

BasvuruItem &BasvuruItem::setCinsiyet(const bool &kadin)
{
    this->append(SKey::BasvuruItem::cinsiyet,kadin ? "Kadın" : "Erkek");
    return *this;
}

BasvuruItem &BasvuruItem::setYasAralik(const std::string &yasAralik)
{
    this->append(SKey::BasvuruItem::yasaralik,yasAralik);
    return *this;
}

BasvuruItem &BasvuruItem::setEgitim(const std::string &egitim)
{
    this->append(SKey::BasvuruItem::egitim,egitim);
    return *this;
}

BasvuruItem &BasvuruItem::setNerden(const std::string &nerden)
{
    this->append(SKey::BasvuruItem::nerdenduydunuz,nerden);
    return *this;
}

BasvuruItem &BasvuruItem::setKatilimTuru(const std::string &katilimTuru)
{
    this->append(SKey::BasvuruItem::nasilKatilirim,katilimTuru);
    return *this;
}

BasvuruItem &BasvuruItem::setTCNO(const std::string &tcno)
{
    this->append(SKey::BasvuruItem::tcno,tcno);
    return *this;
}

BasvuruItem &BasvuruItem::setPassword(const std::string &password)
{
    this->append(SKey::BasvuruItem::password,password);
    return *this;
}

std::string BasvuruItem::getTCNO() const
{
    auto val = this->element(SKey::BasvuruItem::tcno);
    if( val ){
        return val->get_utf8().value.to_string();
    }
    return "";
}

std::string BasvuruItem::getCepNo() const
{
    auto val = this->element(SKey::BasvuruItem::cep);
    if( val ){
        return val->get_utf8().value.to_string();
    }
    return "";
}

std::string BasvuruItem::getMail() const
{
    auto val = this->element(SKey::BasvuruItem::mail);
    if( val ){
        return val->get_utf8().value.to_string();
    }
    return "";
}

std::string BasvuruItem::getAdres() const
{
    auto val = this->element(SKey::BasvuruItem::adres);
    if( val ){
        return val->get_utf8().value.to_string();
    }
    return "";
}

BasvuruManager::BasvuruManager(DB *_mDB)
    :SerikBLDCore::ListItem<BasvuruItem>(_mDB)
{

}

void BasvuruManager::onList(const QVector<BasvuruItem> *mlist)
{


}

void BasvuruManager::errorOccured(const std::string &errorText)
{
    this->mLastError = errorText;
}

const std::string &BasvuruManager::lastError() const
{
    return mLastError;
}
