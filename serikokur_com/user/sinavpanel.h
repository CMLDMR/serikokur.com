#ifndef SINAVPANEL_H
#define SINAVPANEL_H

#include "root/user.h"
#include "BaseClass/containerwiget.h"
#include "root/sinav.h"
#include "root/basvuruitem.h"
#include <algorithm>


class SinavSorusuWidget : public ContainerWidget
{
public:
    SinavSorusuWidget(const long long &baslangicTime, const QVector<Soru> &_mSoruList , const QVector<Soru> &_mExistList = QVector<Soru>());


    Signal<int,std::string> &Cevap();
    Signal<NoClass> &Cevaplandi();

private:
    QVector<Soru> mSoruList;
    QVector<Soru> mExistList;

    void ShowSoru( const int &index );

    const long long mBaslangicTime;

    Signal<NoClass> _cevaplandi;
    Signal<int,std::string> _cevap;

    int cevapIndex = -1;
    std::string soruOid;
};



class SinavPanel : public ContainerWidget
{

    class BasvuruPreviewContainer : public ContainerWidget, public BasvuruItem
    {
    public:
        BasvuruPreviewContainer();
    };

public:
    SinavPanel(SerikBLDCore::DB* _mDB , const std::string &tcno );
    ~SinavPanel();


    void initMenu();


    void initSoruList();


    const std::string &tCNO() const;

private:
    SinavManager* mSinavManager;
    BasvuruManager* mBasvuruManager;
    SoruManager* mSoruManager;

    std::string mTCNO;

    BasvuruItem *mBasvuru;

    std::vector<std::string> mSoruList;
    std::unique_ptr<Sinav> mSinav;



    void SinavaBasla();

    int mSelectedIndex;
    std::string mSelectedOid;


};







#endif // SINAVPANEL_H
