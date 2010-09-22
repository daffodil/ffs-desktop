#include "mptelnet.h"

#include <QtCore/QIODevice>


MpTelnet::MpTelnet(QObject *parent) :
    QObject(parent)
{
    /*
    self.telnetSocket[host_address] = QtNetwork.QTcpSocket(self)
    #print "create sock"
    self.connect(self.telnetSocket[host_address], QtCore.SIGNAL("connected()"), lambda argg=host_address: self.on_telnet_connected(argg))
    self.connect(self.telnetSocket[host_address], QtCore.SIGNAL("disconnected()"), lambda argg=host_address: self.on_telnet_disconnected(argg))
    self.connect(self.telnetSocket[host_address], QtCore.SIGNAL("readyRead()"), lambda argg=host_address: self.on_telnet_ready_read(argg))
    #self.connect(self.telnetSocket, QtCore.SIGNAL("finished()"), self.on_socket_finished)
    if self.telnetSocket[host_address].state() == QtNetwork.QAbstractSocket.UnconnectedState:
    #print "connect,", host_address, "=", self.telnetSocket[host_address].state()
    self.telnetString[host_address] = ''
    self.telnetTimer[host_address] = QtCore.QTime.currentTime()
    self.telnetSocket[host_address].connectToHost(host_address, 5001, QtCore.QIODevice.ReadOnly)
    */
    telnet_reply =  QString("");
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(connected()), this, SLOT(on_telnet_connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(on_telnet_disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(on_telnet_ready_read()));

   // connect(this, SIGNAL(telnet_data(QString, QString)), this, SLOT(foo_telnet_data(QString, QString )));

}

void MpTelnet::get_info(QString ip_address){
    telnet_address = QString(ip_address);
    qDebug() << "GET INFO >>" << telnet_address;
    socket->connectToHost(telnet_address, 5001, QIODevice::ReadOnly);

}


void MpTelnet::on_telnet_connected(){
   // qDebug("connected");


}

void MpTelnet::on_telnet_ready_read(){
    //qDebug() << "READ < " << telnet_address;
   // qDebug() << socket->readAll();
    telnet_reply.append( QString(socket->readAll()) );
}

void MpTelnet::on_telnet_disconnected(){
    //qDebug() << "\n--------------------------------\non_telnet_disconnectedan-------------\n" ; //<< telnet_reply;
    //qDebug() << "DONE" << telnet_reply;

    //QString


    emit telnet_data(telnet_address, telnet_reply); //, telnet_reply);
}

//void MpTelnet::foo_telnet_data(QString ip_address, QString telnet_reply){
    //qDebug() << "CHK" << ip_address << telnet_reply;
//}


