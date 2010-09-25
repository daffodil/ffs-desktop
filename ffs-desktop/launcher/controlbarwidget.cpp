#include "controlbarwidget.h"

#include <QtGui/QHBoxLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QLabel>


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

    buttPause = new QPushButton();
    mainLayout->addWidget(buttPause);
    buttPause->setText(tr("Pause"));
    buttPause->setIcon(QIcon(":/icons/pause_dis"));

    buttStop = new QPushButton();
    mainLayout->addWidget(buttStop);
    buttStop->setText(tr("Stop"));
    buttStop->setIcon(QIcon(":/icons/stop_dis"));


}
void ControlBarWidget::on_telnet_error(QAbstractSocket::SocketError sockError, QString errorStr){
    qDebug("on_telnet_error######");
//    /qDebug() << errorStr;
    statusBarTelnet->showMessage(errorStr, 4000);
}

//** Connect Clicked
void ControlBarWidget::do_telnet_connect(){
    mainObject->telnet->fg_connect();
    qDebug("do_telnet_connect");
    //emit telnet_cmd(QString("connect"));
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
