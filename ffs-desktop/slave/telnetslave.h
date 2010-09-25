#ifndef TELNETSLAVE_H
#define TELNETSLAVE_H

#include <QObject>

#include <QtNetwork/QTcpSocket>


class TelnetSlave : public QObject
{
Q_OBJECT
public:
    explicit TelnetSlave(QObject *parent = 0);


    QString getNode(QString path);
    void setNode(QString path, QString value);

    void fg_connect();
private:
    QTcpSocket *socket;

signals:

public slots:
    void on_telnet_connected();
    void on_telnet_ready_read();
    void on_telnet_disconnected();
};

#endif // TELNETSLAVE_H
