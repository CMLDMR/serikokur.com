#include "sinav.h"

Sinav::Sinav()
    :SerikBLDCore::Item(SKey::Sinav::Collection)
{

}

void Sinav::errorOccured(const std::string &errorText)
{
    mError = errorText;
}

const std::string &Sinav::error() const
{
    return mError;
}

Sinav &Sinav::setSahibi(const std::string &tcno)
{
    this->append(SKey::Sinav::sahibi,tcno);
    return *this;
}

Sinav &Sinav::setBaslangicTime(const int64_t &time)
{
    this->append(SKey::Sinav::baslangicTime,bsoncxx::types::b_int64{time});
    return *this;
}

std::string Sinav::getSahibiTCNO() const
{
    auto val = this->element(SKey::Sinav::sahibi);
    if( val ){
        return val.value().get_utf8().value.to_string();
    }
    return "";
}

uint64_t Sinav::getBaslangic() const
{
    auto val = this->element(SKey::Sinav::baslangicTime);
    if( val ){
        return val->get_int64().value;
    }
    return -1;
}

Sinav &Sinav::setSoruOidList(const std::vector<std::string> &list)
{
    for( const auto &oid : list ){
        this->pushArray(SKey::Sinav::sorular,bsoncxx::oid{oid});
    }
    return *this;
}

std::vector<Sinav::CevapStruct> Sinav::getCevapList() const
{
    std::vector<Sinav::CevapStruct> cvpList;
    bool error_ = false;
    auto val = this->element(SKey::Sinav::cevaplar);
    if( val ){
        auto ar = val.value().get_array().value;
        for( const auto &item : ar ){
            CevapStruct cvp;
            try {
                cvp.cevapIndex = item.get_document().view()[SKey::Sinav::Cevaplar::cevapIndex].get_int32().value;
            } catch (bsoncxx::exception &e) {
                error_ = true;
                break;
            }

            try {
                cvp.soruOid = item.get_document().view()[SKey::Sinav::Cevaplar::soruOid].get_oid().value.to_string();
            } catch (bsoncxx::exception &e) {
                error_ = true;
                break;
            }

            try {
                cvp.timeStamp = item.get_document().view()[SKey::Sinav::Cevaplar::timeStamp].get_int64().value;
            } catch (bsoncxx::exception &e) {
                error_ = true;
                break;
            }

            if( !error_ ){
                cvpList.push_back(cvp);
            }
        }
    }
    return cvpList;
}



const std::vector<std::string> &Sinav::soruOidList()
{
    auto val = this->element(SKey::Sinav::sorular);
    if( val ){

        mSoruOidList.clear();
        auto ar = val.value().get_array().value;
        for( const auto &item : ar ){
            mSoruOidList.push_back(item.get_oid().value.to_string());
        }
    }
    return mSoruOidList;
}

SinavManager::SinavManager(DB *_mDB)
    :SerikBLDCore::ListItem<Sinav>(_mDB)
{
    mSoruManager = new SoruManager(_mDB,new User());
}

SinavManager::~SinavManager()
{
    delete mSoruManager;
}

void SinavManager::onList(const QVector<Sinav> *mlist)
{

}

SoruManager *SinavManager::soruManager() const
{
    return mSoruManager;
}
