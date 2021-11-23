#ifndef SMSMANAGER_H
#define SMSMANAGER_H

#include <BaseClass/smsabstrackmanager.h>
#include "BaseClass/wtheaders.h"


class SMSManager : public SerikBLDCore::SMSAbstractManager
{
    bool mSMSGonderiliyor;
public:
    SMSManager( SerikBLDCore::DB* mDB );



    virtual bool insertAndSendSMS(const SerikBLDCore::SMS::SMSItem &item) override;


    virtual bool checkRapor(const SerikBLDCore::SMS::SMSItem &item) override;


    Signal<std::string> &smsSended();
    Signal<std::string> &ErrorOccured();
    Signal<std::string> &messageOccured();
private:
    Http::Client* mHttpClient;

    Signal<std::string> _smsSended;
    Signal<std::string> _errorOccured;
    Signal<std::string> _messageOccured;

    QString mLastCheckItemOid;
};

#endif // SMSMANAGER_H
