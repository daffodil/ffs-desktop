#ifndef LAUNCHERWINDOW_H
#define LAUNCHERWINDOW_H

#include <QtGui/QMainWindow>



#include <QtGui/QLabel>

#include <QtGui/QTabWidget>

#include "mainobject.h"

#include "launcher/aircraftwidget.h"
#include "launcher/airportswidget.h"

#include "launcher/mpserverswidget.h"
#include "launcher/settingswidget.h"
#include "launcher/mainoptionswidget.h"
#include "launcher/propstreewidget.h"
#include "launcher/controlbarwidget.h"

class LauncherWindow : public QMainWindow
{
    Q_OBJECT

public:
    LauncherWindow(MainObject *mainOb, QWidget *parent = 0);
    ~LauncherWindow();

    MainObject *mainObject;

    QLabel *headerLabel;

    QTabWidget *tabWidget;

    //MpMapWidget *mpMapWidget;
    AircraftWidget *aircraftWidget;
    AirportsWidget *airportsWidget;
    MpServersWidget *mpServersWidget;
    SettingsWidget *settingsWidget;
    MainOptionsWidget *mainOptionsWidget;

    PropsTreeWidget *propsTreeWidget;
    ControlBarWidget *controlBarWidget;
};

#endif // LAUNCHERWINDOW_H
