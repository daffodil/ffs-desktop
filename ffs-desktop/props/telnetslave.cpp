

#include "telnetslave.h"

#include <QtCore/QByteArray>
#include <QtCore/QStringList>

#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>

TelnetSlave::TelnetSlave(QObject *parent) :
    QObject(parent)
{

    current_path = "";

    //hostAddress = QString("127.0.0.1");
    hostAddress = QString("192.168.5.16");
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

//*********************************************************************************************
 //** Connect / Disconnect
//********************************************************************************************
void TelnetSlave::fg_connect(){
    socket->connectToHost(hostAddress, port);
}

void TelnetSlave::fg_disconnect(){
    socket->close();
}

//*********************************************************************************************
 //** Set/Get Node
//********************************************************************************************
void TelnetSlave::get_node(QString path){
    if(!socket->isOpen()){
        fg_connect();
    }
    current_path = path;
    QByteArray command = QByteArray("ls ").append(path).append("\r\n");
    //qDebug() << command;
    socket->write( command );
    //while(socket->waitForReadyRead()){
     //   qDebug() << "idel";
    //}
    //qDebug() << "YES";
 }

void TelnetSlave::set_node(QString path, QString value){
    //TODO
 }

//************************************************************
//*** READ READY

void TelnetSlave::on_ready_read(){
    QString reply(socket->readAll());
    QStringList lines = reply.split("\n");
    for(int i = 0; i < lines.size(); ++i){
        QString line = lines.at(i).trimmed();
        if( line.endsWith("/") ){
            emit props_path(current_path, line);
        }
    }
}

//*********************************************************************************************
 //** Socket Events
//*********************************************************************************************

void TelnetSlave::on_host_found(){
}

void TelnetSlave::on_connected(){
    //qDebug("on_telnet_connected");
    emit telnet_connected(true);
}

void TelnetSlave::on_disconnected(){
    //qDebug("on_telnet_disconnected"); // << "DONE" << telnet_reply;
    emit telnet_connected(false);
}

void TelnetSlave::on_error(QAbstractSocket::SocketError socketError){
    qDebug("on_error");
    qDebug() << socket->errorString();
    emit telnet_error(socketError, socket->errorString());
}



void TelnetSlave::on_state_changed(QAbstractSocket::SocketState socketState ){
      //qDebug("on_state_changed");
     // qDebug() << "state=" << socketState;
}
