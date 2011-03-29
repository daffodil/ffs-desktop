# -------------------------------------------------
# Project created by QtCreator 2010-09-21T05:04:42
# -------------------------------------------------
QT += network \
    sql \
    webkit
CONFIG += qxt
QXT += core \
    gui
TARGET = ffs-desktop
TEMPLATE = app
SOURCES += main.cpp \
    launcher/launcherwindow.cpp \
    mp/mpmapwidget.cpp \
    aircraft/aircraftwidget.cpp \
    mainobject.cpp \
    mp/mpserverswidget.cpp \
    mp/mptelnet.cpp \
    settings/settingswidget.cpp \
    launcher/mainoptionswidget.cpp \
    map/googlemapwidget.cpp \
    airports/aptdatparser.cpp \
    airports/airportswidget.cpp \
    airports/importairportswidget.cpp \
    props/telnetslave.cpp \
    props/propstreewidget.cpp \
    launcher/controlbarwidget.cpp \
    xwidgets/xstatusbar.cpp \
    xobjects/xsettings.cpp \
    xobjects/xcalc.cpp \
    xobjects/latlng.cpp \
    nav/navdatparser.cpp \
    airports/airport.cpp \
    airports/tower.cpp \
    airports/runway.cpp \
    props/propeditwidget.cpp
HEADERS += launcher/launcherwindow.h \
    mp/mpmapwidget.h \
    aircraft/aircraftwidget.h \
    mainobject.h \
    mp/mpserverswidget.h \
    mp/mptelnet.h \
    settings/settingswidget.h \
    launcher/mainoptionswidget.h \
    map/googlemapwidget.h \
    airports/aptdatparser.h \
    airports/airportswidget.h \
    props/telnetslave.h \
    props/propstreewidget.h \
    launcher/controlbarwidget.h \
    airports/importairportswidget.h \
    xwidgets/xstatusbar.h \
    xobjects/xsettings.h \
    xobjects/xcalc.h \
    xobjects/latlng.h \
    nav/navdatparser.h \
    airports/airport.h \
    airports/tower.h \
    airports/runway.h \
    props/propeditwidget.h
RESOURCES += icons/icons.qrc \
    map/map.qrc
