#ifndef USERPANEL_H
#define USERPANEL_H

#include "root/user.h"
#include "BaseClass/containerwiget.h"

class UserList;

class UserPanel : public ContainerWidget, public UserManager
{
public:
    UserPanel(SerikBLDCore::DB* _mDB, const User _mUser);

    virtual void onList( const QVector<User> *mlist )override;

    UserList* mUserList;

    User *CurrentUser() const;

    void initMainPanel();

private:
    User* mCurrentUser;


};


class UserList : public ContainerWidget
{
public:
    UserList();


    Signal<User> &UserSaved();

    Signal<std::string> &DeleteReq();
    Signal<std::string> &RecoverReq();
    Signal<std::string,std::string> &RemoveYetki();
    Signal<std::string,std::string> &AddYetki();


    void setList( const QVector<User> *mList );

private:
    Signal<User> _userSaved;

    Signal<std::string> _deleteReq;
    Signal<std::string> _recoverReq;
    Signal<std::string,std::string> _removeYetki;
    Signal<std::string,std::string> _addYetki;


    std::vector<std::string> yetkiList;


};

#endif // USERPANEL_H
