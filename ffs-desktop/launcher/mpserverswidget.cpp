#include "mpservers.h"

#include <QString>
#include <QtNetwork/QHostInfo>

#include <QtGui/QVBoxLayout>
#include <QtGui/QToolBar>
#include <QtGui/QAction>

MpServersWidget::MpServersWidget(QWidget *parent) :
    QWidget(parent)
{

    //* Main Layout
    QVBoxLayout *mainLayout = new QVBoxLayout();
    setLayout(mainLayout);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0,0,0,0);

    //** Toolbar
    QToolBar *toolbar = new QToolBar();
    mainLayout->addWidget(toolbar);
    toolbar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    QAction *refreshButton = new QAction(this);
    toolbar->addAction(refreshButton);
    refreshButton->setText("Refresh");
    refreshButton->setIcon(QIcon(":/icons/refresh"));
    connect(refreshButton, SIGNAL(triggered()), this, SLOT(load_aircraft()) );

    /*
    def lookup_all(self):
            """Looks up all servers in range 1 to MAX_NAME_SERVER"""
            print "\tLookup All"

            results = {}
            for server_no in range(1, mp_config.MAX_NAME_SERVER + 1):
                    self.lookup(server_no)


    def lookup(self, server_no):
            """Looks up a server"""
            domain_name = "mpserver%02d.flightgear.org" % server_no
            QtNetwork.QHostInfo.lookupHost(domain_name, self.on_lookup_host)


    def on_lookup_host(self, hostInfo):
            if hostInfo.error():
                    #print hostInfo.errorString()
                    self.emit(QtCore.SIGNAL("domain_not_found"), hostInfo.hostName())
            else:
                    #print hostInfo.hostName(), hostInfo.addresses()[0].toString()
                    self.emit(QtCore.SIGNAL("domain_found"), hostInfo.hostName(), hostInfo.addresses()[0].toString())
    */
}

//** Dns Lookup All
void MpServersWidget::dns_lookup_all(){
    qDebug("Lookup All");

    //results = {}
    for(int i=1; i < 4; i++){
    //for server_no in range(1, mp_config.MAX_NAME_SERVER + 1):
    //        self.lookup(server_no)
        dns_lookup(i);
    }
}
//** Dns Lookup ^n
void MpServersWidget::dns_lookup(int server_no){
    QString domain_name;
    domain_name = QString("mpserver01.flightgear.org");
    //qDebug(domain_name);
    QHostInfo::lookupHost(domain_name, this, SLOT(on_lookup_host(QHostInfo)));

}

void MpServersWidget::on_dns_lookup_host(QHostInfo hostInfo){
    qDebug("hostInfo()");
}
