
#include "mainobject.h"
#include "launcher/launcherwindow.h"

#include "mp/mpmapwidget.h"
#include "map/googlemapwidget.h"


#include <QCoreApplication>
#include <QtGui/QAction>
#include <QtGui/QMenu>
#include <QtGui/QCursor>

/*
  The Idea - me not a c++ coder but here are some thoughts.. and my problems

  This application needs to exist in the taskbar as a "shortcuut"

  The reasoning or this is the the application serves a few purporses such as
  1) only creating a telnet object is required
  2) only connecting to a database if requried
  3) creating "status windows" on demand eg chat or Vor fequencies.

  The design brief is to make the application as small as possible.
  But use the qt toolkit as the api to make it workable xpaltform.. a hunch..
  Ideally we want to be in a position where a widget and its code eg a FlightTracker
  can me avaialble as a widget and all its associated "data calls", whether online..

  As a dual screen user, or indeed slaving a laptop to a "full on instance"..
  and with a view to creating a motion platform and "buttons and knobs hardware" for around < £1k as a kit..

  Slaving is a wicked concept and I like that idea very much, and as such the idea of this app
  is to have it installed in a few machines, and used for various purposes..

  For example..
  Removing autopilot from Flightgear and replacing with an FMC here
  Chat by creating a dedicated intelligent chat wiget with Fg in the backround.
  ATC autocompletion
  Autopilot control with a virtual popup
  Instead of using mpMap, instead slave Google or any other mapping to fg as an app

  Just ideas ....
  */



MainObject::MainObject(QObject *parent) :
    QObject(parent)
{

    //TODO ? problem
    // I dont want to "create thsi object yet, as a socket might not be required
    // Hoewever I need a trick to create this object as required
    telnet = new TelnetSlave(this);
    connect(telnet, SIGNAL(telnet_connected(bool)), this, SLOT(on_telnet_connected(bool)));
        //void telnet_connected(bool);

    //QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("192.168.5.10");
    db.setUserName("root");
    db.setPassword("mash");
    db.setDatabaseName("ffs-desktop");
    //db.setDatabaseName("/home/ffs/ffs-desktop/data.db");



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

    QMenu *actionTelnetMenu = new QMenu();    
    popupMenu->addMenu(actionTelnetMenu);
    actionTelnetMenu->setTitle("Telnet");

    actionTelnetConnect = new QAction(actionTelnetMenu);
    actionTelnetMenu->addAction(actionTelnetConnect);
    actionTelnetConnect->setText(tr("Connect"));
    actionTelnetConnect->setIcon(QIcon(":/icons/connect"));
    connect(actionTelnetConnect, SIGNAL(triggered()),
            this, SLOT(on_telnet_connect_action())
    );

    actionTelnetDisconnect = new QAction(actionTelnetMenu);
    actionTelnetMenu->addAction(actionTelnetDisconnect);
    actionTelnetDisconnect->setText(tr("Disconnect"));
    actionTelnetDisconnect->setIcon(QIcon(":/icons/disconnect"));
    actionTelnetDisconnect->setDisabled(true);
    connect(actionTelnetConnect, SIGNAL(triggered()),
            this, SLOT(on_telnet_disconnect_action())
    );
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
//************************************************************
//** Telnet Actions
void MainObject::on_telnet_connect_action(){
    telnet->fg_connect();
}
void MainObject::on_telnet_disconnect_action(){

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


