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
    mainobject.cpp
HEADERS += launcher/launcherwindow.h \
    mp/mpmapwidget.h \
    launcher/aircraftwidget.h \
    mainobject.h
RESOURCES += icons/icons.qrc
