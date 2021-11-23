#include "smsitem.h"

SerikBLDCore::SMS::SMSItem::SMSItem(SMSItem *other) : Item(Collection)
{
    if( other != nullptr )
    {
        this->setDocumentView (other->view ());
    }
}

SerikBLDCore::SMS::SMSItem::SMSItem(const SerikBLDCore::SMS::SMSItem &other) : Item(Collection)
{
    this->setDocumentView (other.view ());
}

SerikBLDCore::SMS::SMSItem::SMSItem(SerikBLDCore::SMS::SMSItem &&other) : Item(Collection)
{
    this->setDocumentView (other.view ());
}

SerikBLDCore::SMS::SMSItem &SerikBLDCore::SMS::SMSItem::operator=(const SerikBLDCore::SMS::SMSItem &other)
{
    this->setDocumentView (other.view ());
    return *this;
}

SerikBLDCore::SMS::SMSItem &SerikBLDCore::SMS::SMSItem::operator=(SerikBLDCore::SMS::SMSItem &&other)
{
    this->setDocumentView (other.view ());
    return *this;
}

SerikBLDCore::SMS::SMSItem &SerikBLDCore::SMS::SMSItem::setSMS(const QString &smsText)
{
    this->append(sms,smsText.toStdString ());
    return *this;
}

QString SerikBLDCore::SMS::SMSItem::smsText() const
{
    auto val = this->element (sms);
    if( val )
    {
#ifdef Q_CC_MSVC
        return QString::fromStdString (val.value ().get_utf8 ().value.to_string());
#endif
#ifdef Q_CC_GNU
        return QString::fromStdString (val.value ().get_utf8 ().value.data ());
#endif
    }
    return "";
}

SerikBLDCore::SMS::SMSItem &SerikBLDCore::SMS::SMSItem::setNumara(const QString &numaraText)
{
    this->append(numara,numaraText.toStdString ());
    return *this;
}

QString SerikBLDCore::SMS::SMSItem::numaraText() const
{
    auto val = this->element (numara);
    if( val )
    {
#ifdef Q_CC_MSVC
        return QString::fromStdString (val.value ().get_utf8 ().value.to_string());
#endif
#ifdef Q_CC_GNU
        return QString::fromStdString (val.value ().get_utf8 ().value.data ());
#endif
    }
    return "";
}

SerikBLDCore::SMS::SMSItem &SerikBLDCore::SMS::SMSItem::setID(const QString &smsIDText)
{
    this->append(smsID,smsIDText.toStdString ());
    return *this;
}

QString SerikBLDCore::SMS::SMSItem::idText() const
{
    auto val = this->element (smsID);
    if( val )
    {
#ifdef Q_CC_MSVC
        return QString::fromStdString (val.value ().get_utf8 ().value.to_string());
#endif
#ifdef Q_CC_GNU
        return QString::fromStdString (val.value ().get_utf8 ().value.data ());
#endif
    }
    return "";
}

SerikBLDCore::SMS::SMSItem &SerikBLDCore::SMS::SMSItem::setmSecStartOfDay(const int &mSecStartOfDay)
{
    this->append(mSecStartDay,mSecStartOfDay);
    return *this;
}

int SerikBLDCore::SMS::SMSItem::secStartOfDay() const
{
    auto val = this->element (mSecStartDay);
    if( val )
    {
        return val.value ().get_int32 ().value;
    }
    return -1;
}

SerikBLDCore::SMS::SMSItem &SerikBLDCore::SMS::SMSItem::setJulianDay(const int &julianDay)
{
    this->append(julianday,julianDay);
    return *this;
}

int SerikBLDCore::SMS::SMSItem::julianDay() const
{
    auto val = this->element (julianday);
    if( val )
    {
        return val.value ().get_int32 ().value;
    }
    return -1;
}

SerikBLDCore::SMS::SMSItem &SerikBLDCore::SMS::SMSItem::setRapor(const QString &raporText)
{
    this->append(raporKey,raporText.toStdString ());
    return *this;
}

QString SerikBLDCore::SMS::SMSItem::rapor() const
{
    auto val = this->element (raporKey);
    if( val )
    {
#ifdef Q_CC_MSVC
        return QString::fromStdString (val.value ().get_utf8 ().value.to_string());
#endif
#ifdef Q_CC_GNU
        return QString::fromStdString (val.value ().get_utf8 ().value.data ());
#endif

    }
    return "rapor yok";
}

SerikBLDCore::SMS::SMSItem &SerikBLDCore::SMS::SMSItem::setRaporID(const int &id)
{
    this->append(smsIDRapor,bsoncxx::types::b_int32{id});
    return *this;
}

int SerikBLDCore::SMS::SMSItem::raporID() const
{
    auto val = this->element (smsIDRapor);
    if( val )
    {
        return val.value ().get_int32 ().value;
    }
    return 0;
}

std::ostream &operator <<(std::ostream &streamer, const SerikBLDCore::SMS::SMSItem &item)
{
    streamer << "SMS: "<<item.smsText ().toStdString () << " NUMARA: " << item.numaraText ().toStdString () << " ID: " << item.idText ().toStdString () << " JulianDay: " << item.julianDay () << std::endl;
    return streamer;
}

std::ostream &operator <<(std::ostream &streamer, SerikBLDCore::SMS::SMSItem &item)
{
    streamer << "SMS: "<<item.smsText ().toStdString () << " NUMARA: " << item.numaraText ().toStdString () << " ID: " << item.idText ().toStdString () << " JulianDay: " << item.julianDay () << std::endl;
    return streamer;
}


