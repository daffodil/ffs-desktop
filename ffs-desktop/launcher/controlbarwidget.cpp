#include "controlbarwidget.h"

#include <QtGui/QHBoxLayout>
#include <QtGui/QButtonGroup>

ControlBarWidget::ControlBarWidget(QWidget *parent) :
    QWidget(parent)
{

    telnet = new TelnetSlave(this);

    QHBoxLayout *mainLayout = new QHBoxLayout();
    setLayout(mainLayout);

    //**********************************************************
    //** Telnet Buttons
    QButtonGroup *grpConnect = new QButtonGroup(this);
    grpConnect->setExclusive(true);

    buttTelnetConnect = new QPushButton();
    mainLayout->addWidget(buttTelnetConnect);
    grpConnect->addButton(buttTelnetConnect);
    buttTelnetConnect->setText(tr("Connect"));
    buttTelnetConnect->setIcon(QIcon(":/icons/connect"));
    connect(buttTelnetConnect, SIGNAL(clicked()), this, SLOT(on_telnet_connect()));

    buttTelnetDisconnect= new QPushButton();
    mainLayout->addWidget(buttTelnetDisconnect);
    grpConnect->addButton(buttTelnetDisconnect);
    buttTelnetDisconnect->setText(tr("Disconnect"));
    buttTelnetDisconnect->setIcon(QIcon(":/icons/disconnect"));
    connect(buttTelnetDisconnect, SIGNAL(clicked()), this, SLOT(on_telnet_disconnect()));

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

void ControlBarWidget::on_telnet_connect(){
    telnet->fg_connect();
    qDebug("on_telnet_connect");
}
void ControlBarWidget::on_telnet_disconnect(){
    qDebug("on_telnet_disconnect");
}
