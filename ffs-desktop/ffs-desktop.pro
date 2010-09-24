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
    launcher/aircraftwidget.cpp \
    mainobject.cpp \
    launcher/mpserverswidget.cpp \
    launcher/mptelnet.cpp \
    launcher/settingswidget.cpp \
    launcher/mainoptionswidget.cpp \
    map/googlemapwidget.cpp
HEADERS += launcher/launcherwindow.h \
    mp/mpmapwidget.h \
    launcher/aircraftwidget.h \
    mainobject.h \
    launcher/mpserverswidget.h \
    launcher/mptelnet.h \
    launcher/settingswidget.h \
    launcher/mainoptionswidget.h \
    map/googlemapwidget.h
RESOURCES += icons/icons.qrc \
    map/map.qrc
