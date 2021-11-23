#ifndef USERPANELCONTAINER_H
#define USERPANELCONTAINER_H

#include "BaseClass/containerwiget.h"
#include "root/user.h"

class UserPanelContainer : public ContainerWidget
{
public:
    UserPanelContainer(SerikBLDCore::DB* _mDB );
};

#endif // USERPANELCONTAINER_H
