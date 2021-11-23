#ifndef SMSABSTRACTMANAGER_H
#define SMSABSTRACTMANAGER_H

#include "db.h"
#include "smsitem.h"
//#include <QNetworkAccessManager>
//#include <QNetworkReply>
//#include <QNetworkRequest>


namespace SerikBLDCore {

/**
 * @brief The SMSAbstractManager class
 * SMS Gönderimi , SMS item Güncelleme ve Gönderilen SMSleri Listeleme Yönetimi Sınıfı
 */
class SMSAbstractManager : public DB
{
    QString mLastSendedSMSID;
    bool mManagerValid;

public:
    SMSAbstractManager( DB* _db );
    SMSAbstractManager( const DB* _db );



    /**
     * @brief isManagerValid Eğer SMSManager Veritabanı Bağlantısı Yok ise Geçersiz Olur ve İşlem Yapmaz
     * @return
     */
    bool isManagerValid() const;

    /**
     * @brief canSend Verilen Numaraya SMS en az 5 Dakika Ara ile Gönderilmesi Gerekir.
     * Eğer Son 5 Dakika için de Sms Gönderilmişse Bu Numaraya SMS Göndermez
     * @param numara
     * @param kalanSure
     * @return
     */
    bool canSend( const QString& numara , int &kalanSure );

    /**
     * @brief listSMS Verilen Numaraya Gönderilen SMSleri listeler
     * @param numara
     * @return
     */
    QVector<SMS::SMSItem> listSMS( const QString& numara , const int& skip = 0 );


    /**
     * @brief insertAndSendSMS SMS Gönderir ve Sistemin Geri Döndürdüğü ID SMS Saklar
     * @param item
     * @return
     */
    virtual bool insertAndSendSMS( const SMS::SMSItem& item ) = 0;

    /**
     * @brief checkRapor: SMS iletilip iletilmediğini Sorgular
     * @param item
     * @return ileti raporu var mı kontrol eder.
     */
    virtual bool checkRapor( const SMS::SMSItem& item ) = 0;

    /**
     * @brief updateSMS Mevcut SMS Günceller
     * @param item
     * @return
     */
    bool updateSMS( const SMS::SMSItem& item );



    /**
     * @brief lastSendedSMSID Son Gönderilen SMS ID'sini Döndürür. Döndürtükten sonra siler
     * @return
     */
    QString lastSendedSMSID() const;

    /**
     * @brief setLastSendedSMSID Son Gönderilen SMS SetEder
     * @param lastSendedSMSID
     */
    void setLastSendedSMSID(const QString &lastSendedSMSID);



    /**
     * @brief confirmTelefonNumarasi
     * @param telefonNumarasi
     * @return
     */
    bool confirmTelefonNumarasi( const QString& telefonNumarasi );



private:
    QString __charList{"0123456789"};

};
}




#endif // SMSMANAGER_H
