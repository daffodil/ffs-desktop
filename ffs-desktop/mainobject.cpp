#include "mainobject.h"
#include "mp/mpmapwidget.h"
#include "launcher/launcherwindow.h"

#include <QCoreApplication>
#include <QtGui/QAction>
#include <QtGui/QMenu>
#include <QtGui/QCursor>

MainObject::MainObject(QObject *parent) :
    QObject(parent)
{

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

    actionMpMap = popupMenu->addAction(QIcon(":/icons/mpmap"), tr("Multiplayer Map"));
    connect(actionMpMap, SIGNAL(triggered()), this, SLOT(on_mpmap()));

    popupMenu->addSeparator();

    actionQuit = popupMenu->addAction(QIcon(":/icons/quit"), tr("Quit"));
    connect(actionQuit, SIGNAL(triggered()), this, SLOT(on_quit()));

    //** Setup
    trayIcon->show();
    //on_mpmap();
    on_launcher();
}

//** Launcher
void MainObject::on_launcher(){
    LauncherWindow *launcherWindow = new LauncherWindow();
    launcherWindow->show();
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
