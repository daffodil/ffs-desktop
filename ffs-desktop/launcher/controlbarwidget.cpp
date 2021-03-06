

#include <QtGui/QHBoxLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QLabel>
#include <QtGui/QMessageBox>

#include "controlbarwidget.h"

/* the control bar widget is the stop across the bottom with
   * telent connection
   * launch controls
   ** the idea is to be able to start, pause and abort the sim
   ** maybe also replay
*/


ControlBarWidget::ControlBarWidget(MainObject *mOb, QWidget *parent) :
    QWidget(parent)
{

    mainObject = mOb;
    //telnet = new TelnetSlave(this);
    connect(mainObject->telnet, SIGNAL(telnet_error(QAbstractSocket::SocketError,QString)),
            this, SLOT(on_telnet_error(QAbstractSocket::SocketError, QString)));
    connect(mainObject->telnet, SIGNAL(telnet_connected(bool)),
            this, SLOT(on_telnet_connected(bool)));

    QHBoxLayout *mainLayout = new QHBoxLayout();
    setLayout(mainLayout);

    //**********************************************************
    //** Telnet Buttons

    QGroupBox *grpTelnet = new QGroupBox();
    mainLayout->addWidget(grpTelnet);

    QString styleX = QString("QGroupBox{ background-color: black; border:2px solid gray;border-radius:5px;  margin-top: 1ex;} QGroupBox::title{subcontrol-origin: margin;subcontrol-position:top center;padding:0 3px;}");
    grpTelnet->setStyleSheet(styleX);
    //QWidget *aeroPanelWidget = new QWidget();
    //aeroLayout->addWidget(aeroPanelWidget);
    //aeroPanelWidget->setStyleSheet("border: 1px solid red; background-color: black;");


    QGridLayout *layoutTelnet = new QGridLayout();
    grpTelnet->setLayout(layoutTelnet);

    QLabel *lblTelnetLabel = new QLabel(tr("Telnet"));
    lblTelnetLabel->setStyleSheet("color: white;");
    layoutTelnet->addWidget(lblTelnetLabel, 0, 0);
    QButtonGroup *grpConnect = new QButtonGroup(this);
    grpConnect->setExclusive(true);

    buttTelnetConnect = new QPushButton();
    layoutTelnet->addWidget(buttTelnetConnect, 0, 1);
    grpConnect->addButton(buttTelnetConnect);
    buttTelnetConnect->setText(tr("Connect"));
    buttTelnetConnect->setIcon(QIcon(":/icons/connect"));
    connect(buttTelnetConnect, SIGNAL(clicked()), this, SLOT(do_telnet_connect()));

    buttTelnetDisconnect= new QPushButton();
    layoutTelnet->addWidget(buttTelnetDisconnect, 0, 2);
    grpConnect->addButton(buttTelnetDisconnect);
    buttTelnetDisconnect->setText(tr("Disconnect"));
    buttTelnetDisconnect->setDisabled(true);
    buttTelnetDisconnect->setIcon(QIcon(":/icons/disconnect"));
    connect(buttTelnetDisconnect, SIGNAL(clicked()), this, SLOT(do_telnet_disconnect()));

    QLabel *lblTelnetStatus= new QLabel(tr("#"));
    layoutTelnet->addWidget(lblTelnetStatus, 1, 0, 1, 1);
    lblTelnetStatus->setStyleSheet("color: yellow; border-top: 1px solid #444444;");
 /*
    QLabel *lblTelnetStatus = new QLabel(tr("Not Connected"));
    layoutTelnet->addWidget(lblTelnetStatus, 1, 1, 1, 2);
    lblTelnetStatus->setStyleSheet("color: yellow; border-top: 1px solid #444444;");
    //lblTelnetStatus->setAlignment(Qt::AlignRight);
    */
    statusBarTelnet = new QStatusBar();
    layoutTelnet->addWidget(statusBarTelnet, 1, 1, 1, 2);
    statusBarTelnet->showMessage("Idle");
    statusBarTelnet->setStyleSheet("color: yellow; border-top: 1px solid #444444;");


    mainLayout->addStretch(20);





    //**********************************************************
    //** Control Buttons
    buttStart = new QPushButton();
    mainLayout->addWidget(buttStart);
    buttStart->setText(tr("Start"));
    buttStart->setIcon(QIcon(":/icons/start_ena"));
	connect(buttStart, SIGNAL(clicked()), this, SLOT(on_start()) );

    buttPause = new QPushButton();
    mainLayout->addWidget(buttPause);
    buttPause->setText(tr("Pause"));
    buttPause->setIcon(QIcon(":/icons/pause_dis"));
    buttPause->setDisabled(true);

    buttStop = new QPushButton();
    mainLayout->addWidget(buttStop);
    buttStop->setText(tr("Stop"));
    buttStop->setIcon(QIcon(":/icons/stop_dis"));
    buttStop->setDisabled(true);
	connect(buttStop, SIGNAL(clicked()), this, SLOT( on_stop()) );

}
void ControlBarWidget::on_telnet_error(QAbstractSocket::SocketError sockError, QString errorStr){
    qDebug("on_telnet_error######");
//    /qDebug() << errorStr;
    statusBarTelnet->showMessage(errorStr, 4000);
}

//** Connect Clicked
void ControlBarWidget::do_telnet_connect(){
    mainObject->telnet->fg_connect();
}

//** DisConnect Clicked
void ControlBarWidget::do_telnet_disconnect(){
    qDebug("do_telnet_disconnect");
    mainObject->telnet->fg_disconnect();
    //emit telnet_cmd(QString("disconnect"));
}

void ControlBarWidget::on_telnet_connected(bool state){
    //telnet->fg_connect();
    qDebug("on_telnet_connected##");
        qDebug() << state;
    statusBarTelnet->showMessage(state ? tr("Connected") : tr("Disconnected"), 4000);
    buttTelnetConnect->setDisabled(state);
    buttTelnetDisconnect->setDisabled(!state);
}




void ControlBarWidget::on_start(){

	QString command("");
	command.append(mainObject->settings->fgfs_path());
	command.append(" --fg-root=").append(mainObject->settings->fg_root());


	qDebug() << "on_start" << command;
	processFgfs.start(command);
	if(processFgfs.waitForStarted()){

		processFgfs.waitForFinished();
		QString ok_result = processFgfs.readAllStandardOutput();
		QString error_result = processFgfs.readAllStandardError();
		if(error_result.length() > 0){
			QMessageBox::critical(this, "Error", error_result);
			return;
		}
		buttStart->setDisabled(true);
		buttStop->setDisabled(false);
		qDebug() << "OK=" << ok_result;
		qDebug() << "ERROR=" << error_result;
	}
}



void ControlBarWidget::on_stop(){
	qDebug() << "on_stop";
	buttStart->setDisabled(false);
	buttStop->setDisabled(true);
}

