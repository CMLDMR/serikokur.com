#ifndef SINAV_H
#define SINAV_H

#include "listitem.h"
#include "root/user.h"
#include "soru.h"
#include "root/basvuruitem.h"
#include <vector>

namespace SKey {


namespace Sinav {
static const std::string Collection{"Sinav"};

static const std::string sahibi{"sahibi"};


static const std::string baslangicTime{"baslangicTime"};
static const std::string gecenTime{"gecenTime"};


static const std::string sorular{"sorular"};
static const std::string cevaplar{"UserCevap"};


namespace Soru {
static const std::string soruOid{"soruOid"};
}

namespace Cevaplar {
static const std::string soruOid{"soruOid"};
static const std::string cevapIndex{"cevapIndex"};
static const std::string timeStamp{"timeStamp"};
}

}

}

class Sinav : public SerikBLDCore::Item
{
public:
    Sinav();

    struct CevapStruct{
        std::string soruOid;
        int cevapIndex;
        std::uint64_t timeStamp;

        bool operator>( const CevapStruct &other){
            if( this->timeStamp > other.timeStamp ){
                return true;
            }else{
                return false;
            }
        }

        bool operator<( const CevapStruct &other){
            if( this->timeStamp > other.timeStamp ){
                return false;
            }else{
                return true;
            }
        }

        bool operator==( const CevapStruct &other){
            if( this->timeStamp == other.timeStamp ){
                return true;
            }else{
                return false;
            }
        }

    };


    virtual void errorOccured(const std::string &errorText) override;

    const std::string &error() const;

    Sinav& setSahibi( const std::string &tcno );
    Sinav& setBaslangicTime( const std::int64_t &time );

    std::string getSahibiTCNO() const;
    std::uint64_t getBaslangic() const;

    Sinav& setSoruOidList( const std::vector<std::string> &list );

    std::vector<CevapStruct> getCevapList() const;

    const std::vector<std::string> &soruOidList();

private:
    std::string mError;

    std::vector<std::string> mSoruOidList;
};



class SinavManager : public SerikBLDCore::ListItem<Sinav>
{
public:
    SinavManager( SerikBLDCore::DB* _mDB );
    ~SinavManager();

    virtual void onList(const QVector<Sinav> *mlist) override;

    SoruManager *soruManager() const;

private:

    SoruManager* mSoruManager;

};

#endif // SINAV_H
