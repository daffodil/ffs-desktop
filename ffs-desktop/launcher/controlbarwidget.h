#ifndef CONTROLBARWIDGET_H
#define CONTROLBARWIDGET_H

#include <QtCore/QProcess>

#include <QtGui/QWidget>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>

#include <QtNetwork/QAbstractSocket>

#include "mainobject.h"

class ControlBarWidget : public QWidget
{
Q_OBJECT
public:
    explicit ControlBarWidget(MainObject *mObject, QWidget *parent = 0);


    MainObject *mainObject;
	QProcess processFgfs;

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

	void on_start();
	void on_stop();

};

#endif // CONTROLBARWIDGET_H
