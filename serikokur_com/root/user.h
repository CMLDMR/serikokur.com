#ifndef USER_H
#define USER_H

#include "item.h"
#include "listitem.h"


namespace Yetki {
static const std::string admin{"admin"};
static const std::string sorulist{"sorulist"};
static const std::string soruekle{"soruekle"};
static const std::string soruonay{"soruonay"};
static const std::string basvuru{"basvuru"};
static const std::string mesajlar{"mesajlar"};
}


namespace SKey {


namespace User {

static const std::string Collection{"Kullanicilar"};
static const std::string username{"username"};
static const std::string telefon{"telefon"};
static const std::string password{"password"};
static const std::string adsoyad{"adsoyad"};
static const std::string yetki{"yetki"};
static const std::string etkin{"etkin"};

}


}

class User : public SerikBLDCore::Item
{
public:
    User();


    User& setUserName( const std::string &_username );
    std::string getUserName() const;

    User& setPassword( const std::string &_password );
    std::string getPassword() const;

    User& setAdSoyad( const std::string &_adsoyad);
    std::string getAdSoyad() const;

    User& setTelefon( const std::string &telefon );
    std::string getTelefon() const;

    User& setDisable( const bool &disable = true );
    bool isDisabled() const;

//    User& setYetki( const std::string &yetki);
//    std::string getYetki() const;

    User& addYetki( const std::string &yetki);
    User& addYetki( const std::vector<std::string> &yetkilist );
    QVector<std::string> getYetki() const;
};



class UserManager : public SerikBLDCore::ListItem<User>
{
public:
    UserManager( SerikBLDCore::DB* _mDB );

    virtual void onList(const QVector<User> *mlist) override;

    virtual  void errorOccured(const std::string &errorText) override;

    static std::vector<std::string> Yetkiler(){
        std::vector<std::string> _yetkiList;
        _yetkiList.push_back("admin");
        _yetkiList.push_back("soruekle");
        _yetkiList.push_back("soruonay");
        _yetkiList.push_back("mesajlar");
        _yetkiList.push_back("basvuru");
        return _yetkiList;
    }

};



#endif // USER_H
