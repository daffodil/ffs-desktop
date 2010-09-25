

#include "telnetslave.h"

#include <QtCore/QByteArray>

#include <QtNetwork/QTcpSocket>


TelnetSlave::TelnetSlave(QObject *parent) :
    QObject(parent)
{
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(connected()), this, SLOT(on_telnet_connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(on_telnet_disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(on_telnet_ready_read()));
}

//*********************************************************************************************
 //** Set/Get Node
//*********************************************************************************************

QString TelnetSlave::getNode(QString path){
        //self.add_log("ls %s" % path)
    //socket->writeData(QString("ls %1\r\n").arg(path) );
    //return socket->recv(120000);
    return QString("foo");
 }
void TelnetSlave::setNode(QString path, QString value){
        //self.add_log("ls %s" % path)
    //socket->writeData( QByteArray(QString("ls %1\r\n").arg(path)) );
    //return QString("foo"); //self.socket.recv(120000);
 }



//*********************************************************************************************
 //** Socket Events
//*********************************************************************************************

void TelnetSlave::on_telnet_connected(){
   // qDebug("connected");


}


void TelnetSlave::on_telnet_ready_read(){
    //qDebug() << "READ < " << telnet_address;
   // qDebug() << socket->readAll();
   // telnet_reply.append( QString(socket->readAll()) );
}

void TelnetSlave::on_telnet_disconnected(){
    //qDebug() << "\n--------------------------------\non_telnet_disconnectedan-------------\n" ; //<< telnet_reply;
    //qDebug() << "DONE" << telnet_reply;

    //QString


    //emit telnet_data(telnet_address, telnet_reply); //, telnet_reply);
}
