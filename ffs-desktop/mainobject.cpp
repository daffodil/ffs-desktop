#include "mainobject.h"

#include <QCoreApplication>
#include <QtGui/QAction>
#include <QtGui/QMenu>
#include <QtGui/QCursor>

MainObject::MainObject(QObject *parent) :
    QObject(parent)
{

    trayIcon = new QSystemTrayIcon(QIcon(":/icons/favicon"), this);
    trayIcon->setToolTip("FlightGear Launcher");
    trayIcon->setVisible(true);
    //trayIcon->setContextMenu(popupMenu);
    //
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(on_tray_icon(QSystemTrayIcon::ActivationReason)));


    qDebug("Popup Menu");

    //***********************************
    //** Menu and actions
    popupMenu = new QMenu();
    trayIcon->setContextMenu(popupMenu);

    actionQuit = popupMenu->addAction(QIcon(":/icons/quit"), tr("Quit"));
    connect(actionQuit, SIGNAL(triggered()), this, SLOT(on_quit()));



    trayIcon->show();
}

void MainObject::on_quit(){
    qDebug("EXIT");
   // qApp->quit();
    QCoreApplication::instance()->quit();
}

void MainObject::on_tray_icon(QSystemTrayIcon::ActivationReason reason){
    qDebug("on_tray_icon");
    //* Right click will show the context Menu above system tray

    //* Following will popup menu with single click on Top LEFT ??
    if(reason == QSystemTrayIcon::Trigger){
        qDebug("move");
        //po//pupMenu->move(trayIcon->)
        QPoint p = QCursor::pos();
        trayIcon->contextMenu()->popup(p);
    }
}

