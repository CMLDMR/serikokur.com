#ifndef DUYURUETKINLIKCONTAINER_H
#define DUYURUETKINLIKCONTAINER_H

#include "BaseClass/containerwiget.h"


class DuyuruEtkinlikContainer : public ContainerWidget
{
public:
    DuyuruEtkinlikContainer();

    void initDuyurular();

    void initEtkinlik();
};



class DuyuruContainer : public ContainerWidget
{
public:
    DuyuruContainer();
};


class EtkinlikContainer : public ContainerWidget
{
public:
    EtkinlikContainer();
};



#endif // DUYURUETKINLIKCONTAINER_H
