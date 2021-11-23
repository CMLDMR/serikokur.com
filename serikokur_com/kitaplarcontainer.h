#ifndef KITAPLARCONTAINER_H
#define KITAPLARCONTAINER_H

#include "BaseClass/containerwiget.h"


class KitaplarContainer : public ContainerWidget
{
public:
    KitaplarContainer();
};


class KitapContainer : public ContainerWidget
{
public:
    KitapContainer(const std::string &name , const std::string &yazar, const std::string &url);

    void setBilgi(const std::string &newBilgi);

private:
    std::string mBilgi;
    std::string mTitle;
    std::string mYazar;
};

#endif // KITAPLARCONTAINER_H
