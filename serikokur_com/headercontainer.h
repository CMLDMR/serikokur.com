#ifndef HEADERCONTAINER_H
#define HEADERCONTAINER_H

#include "BaseClass/containerwiget.h"


class HeaderContainer : public ContainerWidget
{
public:
    HeaderContainer();


    Signal<NoClass> &MainClicked();
    Signal<NoClass> &BasvuruClicked();
private:
    Signal<NoClass> _mainClicked;
    Signal<NoClass> _basvuruClicked;
};

#endif // HEADERCONTAINER_H
