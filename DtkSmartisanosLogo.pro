QT += core gui dtkwidget network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DtkSmartisanosLogo
TEMPLATE = app

CONFIG += c++11 link_pkgconfig

SOURCES += \
        main.cpp \
    smartisanoslogo.cpp

RESOURCES +=         resources.qrc

HEADERS += \
    smartisanoslogo.h

DISTFILES += \
    hyw.ico

RC_ICONS = hyw.ico
