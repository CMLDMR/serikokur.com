#ifndef ILETISIMCONTAINER_H
#define ILETISIMCONTAINER_H


#include "BaseClass/containerwiget.h"
#include "db.h"
#include "root/iletisimformu.h"

class IletisimContainer : public ContainerWidget, public SerikBLDCore::DB
{
public:
    IletisimContainer(SerikBLDCore::DB* mDB);
};


class IletisimWidget : public ContainerWidget, public IletisimFormManager
{
public:
    IletisimWidget(SerikBLDCore::DB* _mDB );
};




#endif // ILETISIMCONTAINER_H
