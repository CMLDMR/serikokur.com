#include "user.h"

User::User()
    :SerikBLDCore::Item(SKey::User::Collection)
{

}

User &User::setUserName(const std::string &_username)
{
    this->append(SKey::User::username,_username);
    return *this;
}

std::string User::getUserName() const
{
    auto val = this->element(SKey::User::username);
    if( val ){
        return val.value().get_utf8().value.to_string();
    }
    return "";
}

User &User::setPassword(const std::string &_password)
{
    this->append(SKey::User::password,_password);
    return *this;
}

std::string User::getPassword() const
{
    auto val = this->element(SKey::User::password);
    if( val ){
        return val.value().get_utf8().value.to_string();
    }
    return "";
}

User &User::setAdSoyad(const std::string &_adsoyad)
{
    this->append(SKey::User::adsoyad,_adsoyad);
    return *this;
}

std::string User::getAdSoyad() const
{
    auto val = this->element(SKey::User::adsoyad);
    if( val ){
        return val.value().get_utf8().value.to_string();
    }
    return "";
}

User &User::setTelefon(const std::string &telefon)
{
    this->append(SKey::User::telefon,telefon);
    return *this;
}

std::string User::getTelefon() const
{
    auto val = this->element(SKey::User::telefon);
    if( val ){
        return val.value().get_utf8().value.to_string();
    }
    return "";
}

User &User::setDisable(const bool &disable)
{
    this->append(SKey::User::etkin,disable);
    return *this;
}

bool User::isDisabled() const
{
    auto val = this->element(SKey::User::etkin);
    if( val ){
        return val.value().get_bool().value;
    }
    return false;
}

//User &User::setYetki(const std::string &yetki)
//{
//    this->append(SKey::User::yetki,yetki);
//    return *this;
//}

QVector<std::string> User::getYetki() const
{
    QVector<std::string> vec;
    auto val = this->element(SKey::User::yetki);
    if( val ){
        auto arlist = val->get_array().value;
        for( auto item : arlist ){
            vec.push_back(item.get_utf8().value.to_string());
        }
    }
    return vec;
}

User &User::addYetki(const std::string &yetki)
{
    this->pushArray(SKey::User::yetki,yetki);
    return *this;
}

User &User::addYetki(const std::vector<std::string> &yetkilist)
{
    for(auto yetki : yetkilist ){
        this->pushArray(SKey::User::yetki,yetki);
    }
    return *this;
}



UserManager::UserManager(DB *_mDB)
    :SerikBLDCore::ListItem<User>(_mDB)
{

}

void UserManager::onList(const QVector<User> *mlist)
{

}

void UserManager::errorOccured(const std::string &errorText)
{

}
