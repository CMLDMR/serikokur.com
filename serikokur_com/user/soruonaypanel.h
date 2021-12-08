#ifndef SORUONAYPANEL_H
#define SORUONAYPANEL_H

#include "root/soru.h"
#include "BaseClass/containerwiget.h"
#include "root/css.h"
#include "root/user.h"

class SoruOnayPanel : public ContainerWidget, public SoruManager
{
public:
    SoruOnayPanel(SerikBLDCore::DB* _mDB , User* _mUser);

    virtual void onList(const QVector<Soru> *mlist) override;


    void initStatistic();
private:
    UserManager* mUserManager;

    enum class FILTER{
        ONAYLI = 0,
        ONAYSIZ,
        OYLAMATAMAM,
        OYLAMABEKLEYEN,
        IPTAL,
        NONE
    };

    FILTER mCurrentFilter = FILTER::NONE;

};

#endif // SORUONAYPANEL_H
