#ifndef LAUNCHERWINDOW_H
#define LAUNCHERWINDOW_H

#include <QtGui/QMainWindow>



#include <QtGui/QLabel>

#include <QtGui/QTabWidget>

#include "launcher/aircraftwidget.h"
#include "launcher/mpserverswidget.h"
#include "launcher/settingswidget.h"

class LauncherWindow : public QMainWindow
{
    Q_OBJECT

public:
    LauncherWindow(QWidget *parent = 0);
    ~LauncherWindow();

    QLabel *headerLabel;

    QTabWidget *tabWidget;

    //MpMapWidget *mpMapWidget;
    AircraftWidget *aircraftWidget;
    MpServersWidget *mpServersWidget;
    SettingsWidget *settingsWidget;


};

#endif // LAUNCHERWINDOW_H
