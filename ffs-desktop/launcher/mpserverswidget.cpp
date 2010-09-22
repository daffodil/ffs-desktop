#include "launcher/mpserverswidget.h"

#include <QtCore/QString>
#include <QtCore/QChar>
#include <QtCore/QList>



#include <QtNetwork/QHostInfo>
#include <QtNetwork/QHostAddress>

#include <QtGui/QBrush>
#include <QtGui/QColor>

#include <QtGui/QVBoxLayout>
#include <QtGui/QToolBar>
#include <QtGui/QAction>

#include <QtGui/QTreeWidgetItem>
#include <QtGui/QHeaderView>
//#include <QtGui/>
//#include <QtGui/>
//#include <QtGui/>
//#include <QtGui/>


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
    connect(refreshButton, SIGNAL(triggered()), this, SLOT(dns_lookup_all()) );

    treeWidget = new QTreeWidget();
    mainLayout->addWidget(treeWidget, 100);

    treeWidget->header()->setStretchLastSection(true);
    treeWidget->setAlternatingRowColors(true);
    treeWidget->setRootIsDecorated(false);

    QTreeWidgetItem * headerItem = treeWidget->headerItem();
    headerItem->setText(MpServersWidget::C_SERVER_NO, tr("No"));
    headerItem->setText(MpServersWidget::C_DOMAIN_NAME, tr("Server"));
    headerItem->setText(MpServersWidget::C_ADDRESS, tr("IP"));
    treeWidget->setColumnWidth(0, 200);
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
    for(int i=1; i < 50; i++){
    //for server_no in range(1, mp_config.MAX_NAME_SERVER + 1):
    //        self.lookup(server_no)
        dns_lookup(i);
    }
}
//** Dns Lookup ^n
void MpServersWidget::dns_lookup(int server_no){

    //* make domain name
    QString domain_name = QString("mpserver%1.flightgear.org").arg(server_no, 2, 10, QChar('0'));
    //qDebug() << "Send >> " << domain_name;

    //* find domain_name in tree and add if not there
    QList<QTreeWidgetItem*> items = treeWidget->findItems(domain_name, Qt::MatchExactly, 0);
    if(items.count() == 0){
        QTreeWidgetItem *newItem = new QTreeWidgetItem();
        newItem->setText(MpServersWidget::C_DOMAIN_NAME, domain_name);
        newItem->setData(MpServersWidget::C_DOMAIN_NAME, Qt::UserRole, QVariant(server_no));
        QBrush b = newItem->foreground(MpServersWidget::C_ADDRESS);
        b.setColor(QColor(100, 100, 100));
        newItem->setForeground(MpServersWidget::C_ADDRESS, b);
        newItem->setText(MpServersWidget::C_ADDRESS, tr("Looking up.."));
        treeWidget->addTopLevelItem(newItem);
    }
    //* execute lookup
    QHostInfo::lookupHost(domain_name, this, SLOT(on_dns_lookup_host(QHostInfo)));

}

void MpServersWidget::on_dns_lookup_host(const QHostInfo &hostInfo){

    QList<QTreeWidgetItem*> items = treeWidget->findItems(hostInfo.hostName(), Qt::MatchExactly, MpServersWidget::C_DOMAIN_NAME);

    //** Make the colors change if address found
    QBrush brush = items[0]->foreground(MpServersWidget::C_ADDRESS);
    QString lbl;
    QColor color;
    if( hostInfo.addresses().count() > 0 ){
         lbl = hostInfo.addresses().first().toString();
         color = QColor(0, 150, 0);
     }else{
        lbl = tr("Not Found");
        color = QColor(150, 0, 0);
     }
     brush.setColor(color);
     items[0]->setForeground(MpServersWidget::C_ADDRESS, brush);
     items[0]->setText(MpServersWidget::C_ADDRESS, lbl);
}


