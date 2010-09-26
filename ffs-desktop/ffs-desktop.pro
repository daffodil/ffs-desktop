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
    parse/aptdatparser.cpp \
    airports/airportswidget.cpp \
    db/airportsdb.cpp \
    slave/telnetslave.cpp \
    props/propstreewidget.cpp \
    launcher/controlbarwidget.cpp
HEADERS += launcher/launcherwindow.h \
    mp/mpmapwidget.h \
    aircraft/aircraftwidget.h \
    mainobject.h \
    mp/mpserverswidget.h \
    mp/mptelnet.h \
    settings/settingswidget.h \
    launcher/mainoptionswidget.h \
    map/googlemapwidget.h \
    parse/aptdatparser.h \
    airports/airportswidget.h \
    db/airportsdb.h \
    slave/telnetslave.h \
    props/propstreewidget.h \
    launcher/controlbarwidget.h
RESOURCES += icons/icons.qrc \
    map/map.qrc
