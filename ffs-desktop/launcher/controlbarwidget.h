#ifndef CONTROLBARWIDGET_H
#define CONTROLBARWIDGET_H

#include "slave/telnetslave.h"

#include <QtGui/QWidget>
#include <QtGui/QPushButton>
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

signals:

public slots:
    void on_telnet_connect();
    void on_telnet_disconnect();
};

#endif // CONTROLBARWIDGET_H
