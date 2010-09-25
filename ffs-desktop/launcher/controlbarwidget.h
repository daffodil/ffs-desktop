#ifndef CONTROLBARWIDGET_H
#define CONTROLBARWIDGET_H

#include "slave/telnetslave.h"
#include "mainobject.h"

#include <QtGui/QWidget>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>

#include <QtNetwork/QAbstractSocket>


class ControlBarWidget : public QWidget
{
Q_OBJECT
public:
    explicit ControlBarWidget(MainObject *mObject, QWidget *parent = 0);

//    TelnetSlave *telnet;
    MainObject *mainObject;

    QPushButton *buttStart;
    QPushButton *buttPause;
    QPushButton *buttStop;

    QPushButton *buttTelnetConnect;
    QPushButton *buttTelnetDisconnect;

    QStatusBar *statusBarTelnet;

signals:
    void telnet_cmd(QString cmd);

public slots:
    void do_telnet_connect();
    void do_telnet_disconnect();

    void on_telnet_error(QAbstractSocket::SocketError, QString);
    void on_telnet_connected(bool state);
};

#endif // CONTROLBARWIDGET_H
