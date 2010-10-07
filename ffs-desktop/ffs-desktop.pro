# -------------------------------------------------
# Project created by QtCreator 2010-09-21T05:04:42
# -------------------------------------------------
QT += network \
    sql \
    webkit
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
    airports/airportsdb.cpp \
    airports/importairportswidget.cpp \
    props/telnetslave.cpp \
    props/propstreewidget.cpp \
    launcher/controlbarwidget.cpp \
    xwidgets/xstatusbar.cpp
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
    airports/airportsdb.h \
    props/telnetslave.h \
    props/propstreewidget.h \
    launcher/controlbarwidget.h \
    airports/importairportswidget.h \
    xwidgets/xstatusbar.h
RESOURCES += icons/icons.qrc \
    map/map.qrc
