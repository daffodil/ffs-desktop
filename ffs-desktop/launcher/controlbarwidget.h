#ifndef CONTROLBARWIDGET_H
#define CONTROLBARWIDGET_H

#include "slave/telnetslave.h"

#include <QtGui/QWidget>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>

#include <QtNetwork/QAbstractSocket>


class ControlBarWidget : public QWidget
{
Q_OBJECT
public:
    explicit ControlBarWidget(QWidget *parent = 0);

    TelnetSlave *telnet;


    QPushButton *buttStart;
    QPushButton *buttPause;
    QPushButton *buttStop;

    QPushButton *buttTelnetConnect;
    QPushButton *buttTelnetDisconnect;

    QStatusBar *statusBarTelnet;

signals:

public slots:
    void do_telnet_connect();
    void do_telnet_disconnect();

    void on_telnet_error(QAbstractSocket::SocketError, QString);
    void on_telnet_connected(bool state);
};

#endif // CONTROLBARWIDGET_H
