#ifndef ILETISIMPANEL_H
#define ILETISIMPANEL_H

#include "root/iletisimformu.h"
#include "BaseClass/containerwiget.h"


class IletisimPanel : public ContainerWidget, public IletisimFormManager
{
public:
    IletisimPanel(SerikBLDCore::DB* _mDB);

    virtual void onList(const QVector<IletisimFormu> *mlist) override;
};

#endif // ILETISIMPANEL_H
