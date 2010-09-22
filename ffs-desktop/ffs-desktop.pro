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
    mpmapwidget.cpp \
    flightgear/aircraftwidget.cpp
HEADERS += mainwindow.h \ # mapwidget.h \
    mpmapwidget.h \
    flightgear/aircraftwidget.h
RESOURCES += icons/icons.qrc
