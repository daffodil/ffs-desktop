#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>


#include <QtGui/QVBoxLayout>
#include <QtGui/QLabel>

#include <QtGui/QTabWidget>
#include <QtGui/QSystemTrayIcon>


//#include "mpmapwidget.h"
#include "flightgear/aircraftwidget.h"

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

#endif // MAINWINDOW_H
