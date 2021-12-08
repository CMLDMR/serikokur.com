#include "soru.h"

Soru::Soru()
    :SerikBLDCore::Item(SKey::Soru::Collection)
{

}

Soru &Soru::setSoru(const std::string &soru)
{
    this->append(SKey::Soru::soru,soru);
    return *this;
}

std::string Soru::getSoru() const
{
    auto val = this->element(SKey::Soru::soru);
    if( val ){
        return val.value().get_utf8().value.to_string();
    }
    return "";
}

Soru &Soru::setOwner(const std::string &ownerOid)
{
    this->append(SKey::Soru::ekleyen,bsoncxx::oid{ownerOid});
    return *this;
}

Soru &Soru::setCevapIndex(const int &cevapIndex)
{
    this->append(SKey::Soru::cevapindex,bsoncxx::types::b_int32{cevapIndex});
    return *this;
}

Soru &Soru::setZorluk(const int32_t &zorluk)
{
    this->append(SKey::Soru::zorluk,bsoncxx::types::b_int32{zorluk});
    return *this;
}

Soru &Soru::Delete()
{
    this->append(SKey::Soru::deleted,true);
    return *this;
}

Soru &Soru::UnDelete()
{
    this->append(SKey::Soru::deleted,false);
    return *this;
}

Soru &Soru::setKaynak(const std::string &kaynak)
{
    this->append(SKey::Soru::kaynak,kaynak);
    return *this;
}

Soru &Soru::setKitap(const std::string &kitap)
{
    this->append(SKey::Soru::kitap,kitap);
    return *this;
}



bool Soru::addCevap(const std::string &cevap, const int &index)
{

    auto val = this->element(SKey::Soru::cevaplar);

    if( val ){
        auto cevaplist = val->get_array().value;

        auto count = std::distance(cevaplist.begin(),cevaplist.end());
        if( count < 8 ){
            SerikBLDCore::Item item("");
            item.append(SKey::Soru::Cevap::cevap,cevap);
            item.append(SKey::Soru::Cevap::index,bsoncxx::types::b_int32{index});
            this->pushArray(SKey::Soru::cevaplar,item);
            return false;
        }
        return false;
    }else{
        SerikBLDCore::Item item("");
        item.append(SKey::Soru::Cevap::cevap,cevap);
        item.append(SKey::Soru::Cevap::index,bsoncxx::types::b_int32{index});
        this->pushArray(SKey::Soru::cevaplar,item);
        return true;
    }
}

bool Soru::addOnay(const bool &onay, const std::string &onaylayanOid, const std::string &aciklama)
{
    bool onayExist = false;

    auto val = this->element(SKey::Soru::onay);
    if( val ){

        auto onayAr = val->get_array().value;
        for( const auto &onayItem : onayAr ){
            auto onayDoc = onayItem.get_document().value;
            if( onayDoc[SKey::Soru::Onay::onaylayanoid].get_oid().value.to_string() == onaylayanOid ){
                onayExist = true;
                break;
            }
        }

        if( onayExist ){
            this->errorOccured("Daha Önceden Oylaması Var");
            return false;
        }else{
            auto doc = document{};
            try {
                doc.append(kvp(SKey::Soru::Onay::onay,onay));
            } catch (bsoncxx::exception &e) {
                this->errorOccured(std::to_string(__LINE__) + " " + std::string(__FUNCTION__)+ " " + std::string(e.what()));
                return false;
            }
            try {
                doc.append(kvp(SKey::Soru::Onay::onaylayanoid,bsoncxx::oid{onaylayanOid}));
            } catch (bsoncxx::exception &e) {
                this->errorOccured(std::to_string(__LINE__) + " " + std::string(__FUNCTION__)+ " " + std::string(e.what()));
                return false;
            }

            try {
                doc.append(kvp(SKey::Soru::Onay::aciklama,aciklama));
            } catch (bsoncxx::exception &e) {
                this->errorOccured(std::to_string(__LINE__) + " " + std::string(__FUNCTION__)+ " " + std::string(e.what()));
                return false;
            }

            this->pushArray(SKey::Soru::onay,doc);
            return true;
        }


    }else{
        auto doc = document{};
        try {
            doc.append(kvp(SKey::Soru::Onay::onay,onay));
        } catch (bsoncxx::exception &e) {
            this->errorOccured(std::to_string(__LINE__) + " " + std::string(__FUNCTION__)+ " " + std::string(e.what()));
            return false;
        }
        try {
            doc.append(kvp(SKey::Soru::Onay::onaylayanoid,bsoncxx::oid{onaylayanOid}));
        } catch (bsoncxx::exception &e) {
            this->errorOccured(std::to_string(__LINE__) + " " + std::string(__FUNCTION__)+ " " + std::string(e.what()));
            return false;
        }

        try {
            doc.append(kvp(SKey::Soru::Onay::aciklama,aciklama));
        } catch (bsoncxx::exception &e) {
            this->errorOccured(std::to_string(__LINE__) + " " + std::string(__FUNCTION__)+ " " + std::string(e.what()));
            return false;
        }

        this->pushArray(SKey::Soru::onay,doc);
        return true;
    }


}

std::map<std::string, int> Soru::getCevaplar() const
{
    std::map<std::string,int> map;

    auto val = this->element(SKey::Soru::cevaplar);
    if( val ){
        auto ar = val->get_array().value;
        for(const auto &cevap : ar ){
            map.insert(std::make_pair<std::string,int>(cevap.get_document().view()[SKey::Soru::Cevap::cevap].get_utf8().value.to_string(),
                       cevap.get_document().view()[SKey::Soru::Cevap::index].get_int32().value));
        }
    }
    return map;
}

std::vector<Soru::cevap> Soru::getCevaplarStruct() const
{
    std::vector<Soru::cevap> map;

    auto val = this->element(SKey::Soru::cevaplar);
    if( val ){
        auto ar = val->get_array().value;
        for(const auto &cevap : ar ){
            Soru::cevap cvp;
            cvp.Cevap = cevap.get_document().view()[SKey::Soru::Cevap::cevap].get_utf8().value.to_string();
            cvp.index = cevap.get_document().view()[SKey::Soru::Cevap::index].get_int32().value;
            map.push_back(cvp);
        }
    }
    return map;
}

std::vector<Soru::cevap> Soru::getShufledCevaplarStruct() const
{

    std::vector<Soru::cevap> map;

    auto val = this->element(SKey::Soru::cevaplar);
    if( val ){
        auto ar = val->get_array().value;
        for(const auto &cevap : ar ){
            Soru::cevap cvp;
            cvp.Cevap = cevap.get_document().view()[SKey::Soru::Cevap::cevap].get_utf8().value.to_string();
            cvp.index = cevap.get_document().view()[SKey::Soru::Cevap::index].get_int32().value;
            map.push_back(cvp);
        }
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(map.begin(),
                 map.end(),
                 g);
    return map;

}

std::vector<Soru::onay> Soru::getOnayStruct() const
{
    std::vector<Soru::onay> map;

    auto val = this->element(SKey::Soru::onay);
    if( val ){
        auto ar = val->get_array().value;
        for(const auto &onay : ar ){
            Soru::onay ony;
            try {
                ony.Onay = onay.get_document().view()[SKey::Soru::Onay::onay].get_bool().value;
            }  catch (bsoncxx::exception &e) {
                ony.Onay = false;
            }

            try {
                ony.owner = onay.get_document().view()[SKey::Soru::Onay::onaylayanoid].get_oid().value.to_string();
            }  catch (bsoncxx::exception &e) {
                ony.owner = "";
            }

            try {
                ony.aciklama = onay.get_document().view()[SKey::Soru::Onay::aciklama].get_utf8().value.to_string();
            }  catch (bsoncxx::exception &e) {
                ony.aciklama = e.what();
            }
            map.push_back(ony);
        }
    }
    return map;
}

std::string Soru::getEkleyen() const
{
    auto val = this->element(SKey::Soru::ekleyen);
    if( val ){
        return val->get_oid().value.to_string();
    }
    return "";
}

std::string Soru::getOwner() const
{
    auto val = this->element(SKey::Soru::ekleyen);
    if( val ){
        return val->get_oid().value.to_string();
    }
    return "";
}



int Soru::getCevapIndex() const
{
    auto val = this->element(SKey::Soru::cevapindex);
    if( val ){
        return val->get_int32().value;
    }
    return 0;
}

int32_t Soru::getZorluk() const
{
    auto val = this->element(SKey::Soru::zorluk);
    if( val ){
        return val->get_int32().value;
    }
    return 0;
}

bool Soru::isDeleted() const
{
    auto val = this->element(SKey::Soru::deleted);
    if( val ){
        return val.get().get_bool().value;
    }
    return false;
}

std::string Soru::getKaynak() const
{
    auto val = this->element(SKey::Soru::kaynak);
    if( val ){
        return val.value().get_utf8().value.to_string();
    }
    return "";
}

std::string Soru::getKitap() const
{
    auto val = this->element(SKey::Soru::kitap);
    if( val ){
        return val.value().get_utf8().value.to_string();
    }
    return "";
}


int Soru::onayCount() const
{
    auto val = this->element(SKey::Soru::onay);
    if( val ){
        auto ar = val->get_array().value;
        int onaycount = 0;
        for( const auto &onay : ar ){
            if( onay.get_document().view()[SKey::Soru::Onay::onay].get_bool().value ){
                onaycount++;
            }
        }
        return onaycount;
    }
    return 0;

}

int Soru::redCount() const
{
    auto val = this->element(SKey::Soru::onay);
    if( val ){
        auto ar = val->get_array().value;
        int redcount = 0;
        for( const auto &onay : ar ){
            if( !onay.get_document().view()[SKey::Soru::Onay::onay].get_bool().value ){
                redcount++;
            }
        }
        return redcount;
    }
    return 0;
}

int Soru::voteCount() const
{
    return onayCount() + redCount();
}

bool Soru::isGecerli() const
{
    if( isDeleted() ) return false;
    if( redCount() ) return false;

    if( ( voteCount() >= 3 ) && ( onayCount() > redCount() ) ){
        return true;
    }else {
        return false;
    }
}

void Soru::errorOccured(const std::string &errorText)
{
    this->mLastError = errorText;
}

const std::string &Soru::lastError() const
{
    return mLastError;
}



SoruManager::SoruManager(DB *_mDB, User *_mUser)
    :SerikBLDCore::ListItem<Soru>(_mDB),
      mUser(_mUser)
{

}

void SoruManager::onList(const QVector<Soru> *mlist)
{

}

User *SoruManager::CurrentUser() const
{
    return mUser;
}
