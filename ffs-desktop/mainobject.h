#ifndef MAINOBJECT_H
#define MAINOBJECT_H

#include <QObject>
#include <QtGui/QSystemTrayIcon>
#include <QtGui/QAction>
#include <QtGui/QMenu>

class MainObject : public QObject
{
Q_OBJECT
public:
    explicit MainObject(QObject *parent = 0);

    QSystemTrayIcon *trayIcon;
    QMenu *popupMenu;

    QAction *actionLauncher;
    QAction *actionMpMap;
    QAction *actionQuit;

signals:

public slots:
    void on_tray_icon(QSystemTrayIcon::ActivationReason reason);

    void on_mpmap();
    void on_launcher();
    void on_quit();
};

#endif // MAINOBJECT_H
