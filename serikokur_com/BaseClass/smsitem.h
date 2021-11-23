#ifndef SMSITEM_H
#define SMSITEM_H

#include "Config.h"
#include "item.h"
#include <QByteArray>
#include <QXmlStreamWriter>
#include <iostream>


namespace SerikBLDCore {


namespace SMS {


static const std::string Collection{"SMSCollection"};
static const std::string sms{"sms"};
static const std::string numara{"telefon"};
static const std::string smsID{"smsid"};
static const std::string mSecStartDay{"mSecStartDay"};
static const std::string julianday{"julianDay"};
static const std::string raporKey{"rapor"};
static const std::string smsIDRapor{"smsidrapor"};

/**
 * @brief The SMSItem class
 * Gönderilecek SMS Item
 */
class SMSItem : public SerikBLDCore::Item
{
public:
    explicit SMSItem( SMSItem* other = nullptr );

    /**
     * @brief SMSItem Copy Constructor
     * @param other
     */
    SMSItem( const SMSItem& other );

    /**
     * @brief SMSItem Move Constructor
     * @param other
     */
    SMSItem( SMSItem&& other );

    /**
     * @brief operator = Copy Assigment
     * @param other
     * @return
     */
    SMSItem& operator=( const SMSItem& other );

    /**
     * @brief operator = Move Assignment
     * @param other
     * @return
     */
    SMSItem& operator=( SMSItem&& other );

    /**
     * @brief setSMS SMS SetEder
     * @param smsText
     * @return
     */
    SMSItem& setSMS( const QString &smsText );

    /**
     * @brief smsText SMS Geri Döndürür
     * @return
     */
    QString smsText() const;

    /**
     * @brief setNumara Numarayı Set Eder
     * @param numaraText
     * @return
     */
    SMSItem& setNumara( const QString& numaraText );

    /**
     * @brief numaraText Numarayı Geri Döndürür
     * @return
     */
    QString numaraText() const;

    /**
     * @brief setID Gönderilen SMS ID'sini Set Eder
     * @param smsIDText
     * @return "ID:5445844"
     */
    SMSItem& setID( const QString& smsIDText );

    /**
     * @brief idText Gönderilen SMS IDsini Geri Döndürür
     * @return
     */
    QString idText() const;

    /**
     * @brief setmSecStartOfDay Günün Başlangıcından itibaren olan Saniyeyi Set Eder
     * @param mSecStartOfDay
     * @return
     */
    SMSItem& setmSecStartOfDay( const int& mSecStartOfDay );

    /**
     * @brief secStartOfDay Saniyeyi Geri Döndürür
     * @return
     */
    int secStartOfDay() const;

    /**
     * @brief setJulianDay Tarihi JulianDay Olarak Set Eder
     * @param julianday
     * @return
     */
    SMSItem& setJulianDay( const int& julianday );

    /**
     * @brief julianDay Tarih JulianDay Olarak Geri Döndürür
     * @return
     */
    int julianDay() const;


    SMSItem& setRapor( const QString &raporText);

    QString rapor() const;

    SMSItem& setRaporID( const int& id );

    int raporID() const;



    friend std::ostream& operator << (std::ostream& streamer, SMSItem& item);
    friend std::ostream& operator << (std::ostream& streamer, const SMSItem& item);
};

}

}



#endif // SMSITEM_H
