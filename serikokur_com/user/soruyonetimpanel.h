#ifndef SORUYONETIMPANEL_H
#define SORUYONETIMPANEL_H

#include "root/soru.h"
#include "BaseClass/containerwiget.h"
#include "root/css.h"
#include "root/user.h"
#include <thread>
#include <chrono>

class SoruYonetimPanel : public ContainerWidget, public SoruManager
{
public:
    SoruYonetimPanel(SerikBLDCore::DB* _mDB , User* _mUser);

    virtual void onList(const QVector<Soru> *mlist) override;


private:


    UserManager* mUserManager;

};








class SoruEkleWidget : public ContainerWidget
{
public:
    SoruEkleWidget(User *_mUser, const bool &initNewSoru = true );


    Signal<NoClass> &SaveSignal();
    Signal<NoClass> &UpdateSignal();

    Soru getSoru() const;

    void setCurrentSoru( const Soru& soru);
    void setNewSoru();

private:
    User* mUser;

    Soru mSoru;

    WTextArea* mSoruMetniEdit;
    WTextArea* mCevap1;
    WTextArea* mCevap2;
    WTextArea* mCevap3;
    WTextArea* mCevap4;
    WTextArea* mCevap5;
    WTextArea* mCevap6;
    WTextArea* mCevap7;
    WTextArea* mCevap8;
    WComboBox* mCevapComboBox;
//    WComboBox* mKitap;

//    WComboBox* mZorlukComboBox;
//    WLineEdit* mKaynakKitap;

    WTextArea* addCevapWidget(WContainerWidget* parentContainer, const std::string &title, const std::string cevapMetni = "");


    Signal<NoClass> SoruSignal;
    Signal<NoClass> _UpdateSignal;

};

#endif // SORUYONETIMPANEL_H
