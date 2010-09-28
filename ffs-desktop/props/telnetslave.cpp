

#include "telnetslave.h"

#include <QtCore/QByteArray>

#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>

TelnetSlave::TelnetSlave(QObject *parent) :
    QObject(parent)
{

    hostAddress = QString("127.0.0.1");
    port = 5555;

    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(on_error( QAbstractSocket::SocketError)));
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this, SLOT(on_state_changed(QAbstractSocket::SocketState)));

    connect(socket, SIGNAL(hostFound()), this, SLOT(on_host_found()));
    connect(socket, SIGNAL(connected()), this, SLOT(on_connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(on_disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(on_ready_read()));
}


void TelnetSlave::fg_connect(){
    qDebug("fg_connect()");


    socket->connectToHost(hostAddress, port);
        //self.add_log("ls %s" % path)
    //socket->writeData( QByteArray(QString("ls %1\r\n").arg(path)) );
    //return QString("foo"); //self.socket.recv(120000);
 }

void TelnetSlave::fg_disconnect(){
    qDebug("fg_disconnect()");


    socket->close();
        //self.add_log("ls %s" % path)
    //socket->writeData( QByteArray(QString("ls %1\r\n").arg(path)) );
    //return QString("foo"); //self.socket.recv(120000);
 }
//*********************************************************************************************
 //** Set/Get Node
//*********************************************************************************************

QString TelnetSlave::get_node(QString path){
        //self.add_log("ls %s" % path)
    //QString *s = QString("ls %1\r\n").arg(path);
    QByteArray ba = QByteArray("ls ").append(path).append("\r\n");
    //ba << "ls " << path << "\r\n";
    qDebug() << ba;
    socket->write( ba  );
    //return socket->
    return QString("foo");
 }
void TelnetSlave::set_node(QString path, QString value){
        //self.add_log("ls %s" % path)
    //socket->writeData( QByteArray(QString("ls %1\r\n").arg(path)) );
    //return QString("foo"); //self.socket.recv(120000);
 }



//*********************************************************************************************
 //** Socket Events
//*********************************************************************************************

void TelnetSlave::on_host_found(){
    qDebug("on_host_found");

}

void TelnetSlave::on_connected(){
    qDebug("on_telnet_connected");
    emit telnet_connected(true);
}
void TelnetSlave::on_disconnected(){
    //qDebug() << "\n--------------------------------\non_telnet_disconnectedan-------------\n" ; //<< telnet_reply;
    qDebug("on_telnet_disconnected"); // << "DONE" << telnet_reply;
    //emit telnet_data(telnet_address, telnet_reply); //, telnet_reply);
    emit telnet_connected(false);
}


void TelnetSlave::on_ready_read(){
    //qDebug() << "READ < " << telnet_address;
   // qDebug() << socket->readAll();
   // telnet_reply.append( QString(socket->readAll()) );
}

void TelnetSlave::on_error(QAbstractSocket::SocketError socketError){
    qDebug("on_error");
    qDebug() << socket->errorString();
    emit telnet_error(socketError, socket->errorString());
}



void TelnetSlave::on_state_changed(QAbstractSocket::SocketState socketState ){
      qDebug("on_state_changed");
      qDebug() << "state=" << socketState;
}
