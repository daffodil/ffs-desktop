#include "mainobject.h"

#include <QCoreApplication>
#include <QtGui/QAction>
#include <QtGui/QMenu>

MainObject::MainObject(QObject *parent) :
    QObject(parent)
{

    trayIcon = new QSystemTrayIcon(QIcon(":/icons/favicon"), this);
    trayIcon->setToolTip("FlightGear Launcher");
    trayIcon->setVisible(true);
    //trayIcon->setContextMenu(popupMenu);
    //connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
   //         this, SLOT(on_tray_icon()));


    qDebug("Popup Menu");

    popupMenu = new QMenu();
    trayIcon->setContextMenu(popupMenu);

    actionQuit = popupMenu->addAction(QIcon(":/icons/quit"), tr("Quit"));
    connect(actionQuit, SIGNAL(triggered()), this, SLOT(on_quit()));
    //, on_quit());


    trayIcon->show();
}

void MainObject::on_quit(){
    qDebug("EXIT");
   // qApp->quit();
    QCoreApplication::instance()->quit();
}

void MainObject::on_tray_icon(){
    qDebug("on_tray_icon");
   // qApp->quit();
//    /QCoreApplication::instance()->quit();
}

