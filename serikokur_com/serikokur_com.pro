QT += gui core xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


CONFIG += c++17 console
CONFIG -= app_bundle

CONFIG += no_keywords

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        BaseClass/basewidget.cpp \
        BaseClass/containerwiget.cpp \
        BaseClass/databasewidget.cpp \
        BaseClass/dbclass.cpp \
        BaseClass/dialog.cpp \
        BaseClass/itembase.cpp \
        BaseClass/smsabstrackmanager.cpp \
        BaseClass/smsitem.cpp \
        baskanimizcontainer.cpp \
        duyuruetkinlikcontainer.cpp \
        hakkindacontainer.cpp \
        headercontainer.cpp \
        iletisimcontainer.cpp \
        kitaplarcontainer.cpp \
        main.cpp \
        mainapplication.cpp \
        maincontainer.cpp \
        odullercontainer.cpp \
        root/basvuruitem.cpp \
        root/iletisimformu.cpp \
        root/sinav.cpp \
        root/smsmanager.cpp \
        root/soru.cpp \
        root/user.cpp \
        user/basvuruyonetimpanel.cpp \
        user/iletisimpanel.cpp \
        user/robotimage.cpp \
        user/sinavpanel.cpp \
        user/soruonaypanel.cpp \
        user/soruyonetimpanel.cpp \
        user/userpanel.cpp \
        userpanelcontainer.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


INCLUDEPATH += C:/boost/boost
DEPENDPATH += C:/boost/boost


message("msvc 2017 x64")

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lbsoncxx
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lbsoncxxd
else:unix: LIBS += -L$$PWD/lib/ -lbsoncxx

INCLUDEPATH += $$PWD/include/bsoncxx/v_noabi
DEPENDPATH += $$PWD/include/bsoncxx/v_noabi



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lmongocxx
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lmongocxxd
else:unix: LIBS += -L$$PWD/lib/ -lmongocxx

INCLUDEPATH += $$PWD/include/mongocxx/v_noabi
DEPENDPATH += $$PWD/include/mongocxx/v_noabi


win32: LIBS += -LC:/Wt_4.3.1_msvc2017_x64/lib/ -lwt

INCLUDEPATH += C:/Wt_4.3.1_msvc2017_x64/include
DEPENDPATH += C:/Wt_4.3.1_msvc2017_x64/include

win32: LIBS += -LC:/Wt_4.3.1_msvc2017_x64/lib/ -lwthttp

win32: LIBS += -LC:/Wt_4.3.1_msvc2017_x64/lib/ -llibhpdf


win32: LIBS += -LC:/SerikBLDCoreRelease/MSVC2017X64/lib/ -lSerikBLDCore

INCLUDEPATH += C:/SerikBLDCoreRelease/MSVC2017X64/include
DEPENDPATH += C:/SerikBLDCoreRelease/MSVC2017X64/include

INCLUDEPATH += $$PWD/../../../Comman
DEPENDPATH += $$PWD/../../../Comman

HEADERS += \
    ../../../Comman/CSSCustom.h \
    ../../../Comman/bootstrap.h \
    ../../../Comman/inlinestyle.h \
    ../../../Comman/mongoheaders.h \
    BaseClass/basewidget.h \
    BaseClass/containerwiget.h \
    BaseClass/databasewidget.h \
    BaseClass/dbclass.h \
    BaseClass/dialog.h \
    BaseClass/itembase.h \
    BaseClass/smsabstrackmanager.h \
    BaseClass/smsitem.h \
    BaseClass/wtheaders.h \
    baskanimizcontainer.h \
    duyuruetkinlikcontainer.h \
    hakkindacontainer.h \
    headercontainer.h \
    iletisimcontainer.h \
    kitaplarcontainer.h \
    mainapplication.h \
    maincontainer.h \
    odullercontainer.h \
    response.hpp \
    root/basvuruitem.h \
    root/css.h \
    root/iletisimformu.h \
    root/sinav.h \
    root/smsmanager.h \
    root/soru.h \
    root/user.h \
    user/basvuruyonetimpanel.h \
    user/iletisimpanel.h \
    user/robotimage.h \
    user/sinavpanel.h \
    user/soruonaypanel.h \
    user/soruyonetimpanel.h \
    user/userpanel.h \
    userpanelcontainer.h
