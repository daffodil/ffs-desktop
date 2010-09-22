#ifndef LAUNCHERWINDOW_H
#define LAUNCHERWINDOW_H

#include <QtGui/QMainWindow>


#include <QtGui/QVBoxLayout>
#include <QtGui/QLabel>

#include <QtGui/QTabWidget>
#include <QtGui/QSystemTrayIcon>


//#include "mpmapwidget.h"
#include "launcher/aircraftwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QSystemTrayIcon *trayIcon;
    QVBoxLayout *mainVBox;
    QLabel *headerLabel;

    QTabWidget *tabWidget;

    //MpMapWidget *mpMapWidget;
    AircraftWidget *aircraftWidget;



};

#endif // LAUNCHERWINDOW_H
