# -------------------------------------------------
# Project created by QtCreator 2010-09-21T05:04:42
# -------------------------------------------------
QT += network \
    sql \
    webkit
TARGET = ffs-desktop
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \ # mapwidget.cpp \
    mp/mpmapwidget.cpp \
    flightgear/aircraftwidget.cpp \
    mainobject.cpp
HEADERS += mainwindow.h \ # mapwidget.h \
    mp/mpmapwidget.h \
    flightgear/aircraftwidget.h \
    mainobject.h
RESOURCES += icons/icons.qrc
