#ifndef LAUNCHERWINDOW_H
#define LAUNCHERWINDOW_H

#include <QtGui/QMainWindow>



#include <QtGui/QLabel>

#include <QtGui/QTabWidget>

#include "mainobject.h"

#include "aircraft/aircraftwidget.h"
#include "airports/airportswidget.h"

#include "mp/mpserverswidget.h"
#include "launcher/mainoptionswidget.h"
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

    AircraftWidget *aircraftWidget;
    AirportsWidget *airportsWidget;
    MpServersWidget *mpServersWidget;
    MainOptionsWidget *mainOptionsWidget;

    ControlBarWidget *controlBarWidget;

    void closeEvent(QCloseEvent *event);

public slots:
	void on_tab_changed(int);
};

#endif // LAUNCHERWINDOW_H
