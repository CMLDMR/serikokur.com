#ifndef BASVURUYONETIMPANEL_H
#define BASVURUYONETIMPANEL_H

#include "root/basvuruitem.h"
#include "BaseClass/containerwiget.h"

class BasvuruYonetimPanel :public ContainerWidget, public BasvuruManager
{
public:
    BasvuruYonetimPanel(SerikBLDCore::DB* _mDB);

    void initController();

    virtual void onList(const QVector<BasvuruItem> *mlist) override;

    virtual void errorOccured(const std::string &errorText) override;
};


class IstatistikWidget :public ContainerWidget, public BasvuruManager
{
public:
    IstatistikWidget(SerikBLDCore::DB* _mDB);


    virtual void onList(const QVector<BasvuruItem> *mlist) override;

    virtual void errorOccured(const std::string &errorText) override;

    void initIstatistik();
};

#endif // BASVURUYONETIMPANEL_H
