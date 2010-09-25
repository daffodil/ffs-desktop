#ifndef TELNETSLAVE_H
#define TELNETSLAVE_H

#include <QObject>

#include <QtNetwork/QTcpSocket>
/*
void	connected ()
void	disconnected ()
void	error ( QAbstractSocket::SocketError socketError )
void	hostFound ()
void	proxyAuthenticationRequired ( const QNetworkProxy & proxy, QAuthenticator * authenticator )
void	stateChanged ( QAbstractSocket::SocketState socketState )
*/

class TelnetSlave : public QObject
{
Q_OBJECT
public:
    explicit TelnetSlave(QObject *parent = 0);


    QString getNode(QString path);
    void setNode(QString path, QString value);

    QString hostAddress;
    int port;

    void fg_connect();
    void fg_disconnect();
private:
    QTcpSocket *socket;


signals:
    void telnet_error(QAbstractSocket::SocketError, QString);
    void telnet_connected(bool);
public slots:
    void on_connected();
    void on_ready_read();
    void on_disconnected();
    void on_error(QAbstractSocket::SocketError);
    void on_host_found();
    void on_state_changed(QAbstractSocket::SocketState);
};

#endif // TELNETSLAVE_H
