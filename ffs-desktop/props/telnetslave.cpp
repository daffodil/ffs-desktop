
/*

  ?
 */

#include "telnetslave.h"

#include <QtCore/QByteArray>
#include <QtCore/QStringList>

#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>




TelnetSlave::TelnetSlave(QObject *parent) :
    QObject(parent)
{

    current_node_path = "";
    in_request = false;

	hostAddress = QString("127.0.0.1");
	//hostAddress = QString("192.168.5.23");
	port = 5500;

    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(on_error( QAbstractSocket::SocketError))
    );
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this, SLOT(on_state_changed(QAbstractSocket::SocketState))
    );
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

void TelnetSlave::set_node(QString path, QString value){
    //TODO
 }


//*********************************************************************************************
 //** Get Node
//********************************************************************************************
void TelnetSlave::get_node(QString node_path){
    if( !socket->isOpen() ){
        qDebug() << "not open";
        return;
    }
    current_node_path = node_path; // << store the "node_path" in the current_node_path vars
    QByteArray command = QByteArray("ls ").append(node_path).append("\r\n");
    //** Send request to telnet socket
    if(in_request){
        qDebug() << "IN_REQUEST";
        qDebug() << socket->bytesToWrite();
        return;
    }
    in_request = true;
    socket->write( command );
 }


//************************************************************
//*** READ READY

void TelnetSlave::on_ready_read(){

    QString reply(socket->readAll());
    QStringList lines = reply.split("\r\n");

   // qDebug() << reply;
    for(int i = 0; i < lines.size(); ++i){
        QString line = lines.at(i).trimmed();
       // qDebug() << "line=" << line;
        //* end line is /> so skip
        if(line == "/>"){
            qDebug("END");
        }else if( line.endsWith("/") ){
            emit props_path(current_node_path, line);
        }else{
            if(line.count("chat") > 0){
                 qDebug() << "CHAT=" << line << "=" << line.count("chat") ;
            }
            // check the = sign is there.
            if( line.count("=") > 0 ){
                //* eg right-aileron-pos-norm =\t'0.02699490675'\t(double)
                //QString val_part = line.section("=", 0, 0).trimmed();
                //* Split the values on a tab
                QStringList val_parts = line.split("\t");
                //ssqDebug() << val_parts;

                //TODO - maybe some regex
                //** the node_name ends with " =" so remove eg "my-node ="
                QString node_name = val_parts[0].left( val_parts[0].length() - 2 );

                //** node value in enclosed in ' so remove eg "'true'"
                QString node_value = val_parts.size() == 1 ?
                                     "" :
                                     val_parts[1].replace("'","");

                //** the node_type is encodes in () eg "(double)"
                QString node_type = val_parts.size() == 2 ?
                                    "" :
                                    val_parts[2].mid(1, val_parts[2].length() - 2);

               // QString node_name = val_parts[0].trimmed();
                //qDebug() << "VAL=" << node_name << " = " << node_value << "=" << node_type;
                //qDebug();
                emit props_node(current_node_path, node_name, node_value, node_type);
            }else{
                qDebug() << "UMM=" << line << "=" << line.count("=") ;
                 //qDebug() << reply;
            }
        }
    } /* for */
    in_request = false;
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
