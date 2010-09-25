
#include "mainobject.h"
#include "launcher/launcherwindow.h"

#include "mp/mpmapwidget.h"
#include "map/googlemapwidget.h"


#include <QCoreApplication>
#include <QtGui/QAction>
#include <QtGui/QMenu>
#include <QtGui/QCursor>

MainObject::MainObject(QObject *parent) :
    QObject(parent)
{

    telnet = new TelnetSlave(this);
    connect(telnet, SIGNAL(telnet_connected(bool)), this, SLOT(on_telnet_connected(bool)));
        //void telnet_connected(bool);

    //***********************************
    //** Tray Icon
    trayIcon = new QSystemTrayIcon(QIcon(":/icons/favicon"), this);
    trayIcon->setToolTip("FlightGear Launcher");
    trayIcon->setVisible(true);
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(on_tray_icon(QSystemTrayIcon::ActivationReason)));


    //***********************************
    //** Menu and actions
    popupMenu = new QMenu();
    trayIcon->setContextMenu(popupMenu);

    actionCallsign = new QWidgetAction(this);
    lblCallsign = new QLabel();
    lblCallsign->setText("CALLSIGN");
    lblCallsign->setStyleSheet("font-family: monospace; background-color: black; color: white; padding: 5px; font-weight: bold;");
    actionCallsign->setDefaultWidget(lblCallsign);

    popupMenu->addAction(actionCallsign); //QIcon(":/icons/mpmap"), tr("Multiplayer Map"));

    actionMpMap = popupMenu->addAction(QIcon(":/icons/mpmap"), tr("Multiplayer Map"));
    connect(actionMpMap, SIGNAL(triggered()), this, SLOT(on_mpmap()));

    popupMenu->addSeparator();

    actionQuit = popupMenu->addAction(QIcon(":/icons/quit"), tr("Quit"));
    connect(actionQuit, SIGNAL(triggered()), this, SLOT(on_quit()));

    //** Setup
    trayIcon->show();
    //on_mpmap();
    on_launcher();
    //on_map();
}

//** Launcher
void MainObject::on_launcher(){
    LauncherWindow *launcherWindow = new LauncherWindow(this);
    launcherWindow->show();
}

//** Map
void MainObject::on_map(){
    GoogleMapWidget *gmapWidget = new GoogleMapWidget();
    gmapWidget->show();
}

//** MpMap
void MainObject::on_mpmap(){
    MpMapWidget *mpMapWidget = new MpMapWidget();
    mpMapWidget->show();
}

//** Quit
void MainObject::on_quit(){
    QCoreApplication::instance()->quit();
}

//** Tray Icon
void MainObject::on_tray_icon(QSystemTrayIcon::ActivationReason reason){   
    //* Right click will show the context Menu above system tray
    //* Following will popup menu with single click on Top LEFT ??
    if(reason == QSystemTrayIcon::Trigger){
        QPoint p = QCursor::pos();
        trayIcon->contextMenu()->popup(p);
    }
}




//** Telnet Events
void MainObject::on_telnet_connected(bool state){
    //telnet->fg_connect();
    qDebug("on_telnet_connected##");
    qDebug() << state;
    //statusBarTelnet->showMessage(state ? tr("Connected") : tr("Disconnected"), 4000);
    //buttTelnetConnect->setDisabled(state);
    //buttTelnetDisconnect->setDisabled(!state);
    trayIcon->setIcon(QIcon(state ? ":/icons/connect" : ":/icons/disconnect"));
}
