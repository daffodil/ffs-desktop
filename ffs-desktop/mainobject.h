#ifndef MAINOBJECT_H
#define MAINOBJECT_H

#include "slave/telnetslave.h"

#include <QObject>
#include <QtGui/QSystemTrayIcon>
#include <QtGui/QAction>
#include <QtGui/QMenu>
#include <QtGui/QLabel>
#include <QtGui/QWidgetAction>

class MainObject : public QObject
{
Q_OBJECT
public:
    explicit MainObject(QObject *parent = 0);

    //** Objects
    TelnetSlave *telnet;

    //* Widgets
    QSystemTrayIcon *trayIcon;
    QMenu *popupMenu;
    QWidgetAction *actionCallsign;
    QLabel *lblCallsign;

    QAction *actionLauncher;
    QAction *actionMpMap;
    QAction *actionQuit;

signals:

public slots:
    void on_tray_icon(QSystemTrayIcon::ActivationReason reason);

    void on_telnet_connected(bool);

    void on_launcher();
    void on_mpmap();
    void on_map();
    void on_quit();
};

#endif // MAINOBJECT_H
