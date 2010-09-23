#include "launcher/mpserverswidget.h"
#include "launcher/mptelnet.h"

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
    refreshButton->setText("DNS Lookup");
    refreshButton->setIcon(QIcon(":/icons/dns_lookup"));
    connect(refreshButton, SIGNAL(triggered()), this, SLOT(dns_lookup_all()) );

    treeWidget = new QTreeWidget();
    mainLayout->addWidget(treeWidget, 100);

    //treeWidget->setSortingEnabled(true);
    treeWidget->setAlternatingRowColors(true);
    treeWidget->setRootIsDecorated(false);

    QTreeWidgetItem * headerItem = treeWidget->headerItem();
    headerItem->setText(C_SERVER_NO, tr("No"));
    headerItem->setText(C_DOMAIN_NAME, tr("Server"));
    headerItem->setText(C_ADDRESS, tr("IP Address"));
    headerItem->setText(C_PILOTS_COUNT, tr("Pilots"));
    treeWidget->header()->setStretchLastSection(true);
    treeWidget->setColumnWidth(C_SERVER_NO, 40);
    treeWidget->setColumnWidth(C_DOMAIN_NAME, 200);

    //##
    dns_lookup_all();
}
/* end constructor */


//** Dns Lookup All
void MpServersWidget::dns_lookup_all(){
    for(int i=1; i < 5; i++){
        dns_lookup(i);
    }
    //treeWidget->sortByColumn(1);
}

//** Dns Lookup (server_no)
void MpServersWidget::dns_lookup(int server_no){

    //* make domain name
    QString domain_name = QString("mpserver%1.flightgear.org").arg(server_no, 2, 10, QChar('0'));

    //* find domain_name in tree and add if not there
    QList<QTreeWidgetItem*> items = treeWidget->findItems(domain_name, Qt::MatchExactly, C_DOMAIN_NAME);
    if(items.count() == 0){
        QTreeWidgetItem *newItem = new QTreeWidgetItem();
        newItem->setText(C_SERVER_NO, QString::number(server_no));

        newItem->setText(C_DOMAIN_NAME, domain_name);
        newItem->setData(C_DOMAIN_NAME, Qt::UserRole, QVariant(server_no));

        QBrush b = newItem->foreground(MpServersWidget::C_ADDRESS);
        b.setColor(QColor(100, 100, 100));
        newItem->setForeground(C_ADDRESS, b);
        newItem->setText(C_ADDRESS, tr("Looking up"));

        treeWidget->addTopLevelItem(newItem);
    }
    //* execute lookup
    QHostInfo::lookupHost(domain_name, this, SLOT(on_dns_lookup_host(QHostInfo)));

}

void MpServersWidget::on_dns_lookup_host(const QHostInfo &hostInfo){

    QList<QTreeWidgetItem*> items = treeWidget->findItems(hostInfo.hostName(), Qt::MatchExactly, C_DOMAIN_NAME);

    //** Make the colors change if address found
    QBrush brush = items[0]->foreground(C_ADDRESS);
    QString lbl;
    QColor color;
    bool has_address = hostInfo.addresses().count() > 0;
    if( has_address ){
         lbl = hostInfo.addresses().first().toString();
         color = QColor(0, 150, 0);
     }else{
        lbl = tr("Not Found");
        color = QColor(150, 0, 0);
     }
     brush.setColor(color);
     items[0]->setForeground(C_ADDRESS, brush);
     items[0]->setText(C_ADDRESS, lbl);

     if(has_address){
        MpTelnet *telnet = new MpTelnet(this );
        telnet->get_info(hostInfo.addresses().first().toString());
        connect(telnet, SIGNAL(telnet_data(QString, QString)),
                this, SLOT(on_telnet_data(QString, QString))
               );
     }
}
/* Example Output >>
Trying 85.214.37.14...
Connected to mpserver01.flightgear.org.
Escape character is '^]'.
# This is mpserver01
# FlightGear Multiplayer Server v0.10.3 using protocol version v1.1 (LazyRelay enabled)
# This server is tracked: 62.112.194.20
# 38 pilots online
airdomi@LOCAL: 4107968.717705 3824275.355909 3041539.588760 28.615373 42.951713 34195.591451 -3.696031 1.916703 0.573010 Aircraft/777-200/Models/777-200ER.xml
minaya@mpserver10: 4008833.892465 -10727.752073 4944410.518456 51.153549 -0.153324 562.061917 -2.642317 2.096125 1.046300 Aircraft/777-200/Models/777-200ER.xml
*/
void MpServersWidget::on_telnet_data(QString ip_address, QString telnet_reply){
    //qDebug() <<  "YESSS" << telnet_reply;   

    //** Split the reply into lines and parse each line
    QStringList lines = telnet_reply.split("\n");
    QString line;
    int pilot_count = 0;
    for(int i = 0; i < lines.size(); ++i){

        line = lines.at(i).trimmed();
        if(i == 0){
            // skip first line

        }else if(line.startsWith("#")){
            // skip lines starting with #

        }else if(line.length() == 0){
            // skip blank lines

        }else{
            QStringList parts = line.split(" ");
            QString callsign = parts.at(0).split("@").at(0);
            QString mp_server = parts.at(0).split("@").at(1);

            mp_server = mp_server.replace(QString(":"),QString("")); //* get rid of trailing ":" at end eg a.b.c.192:
            if(mp_server == "LOCAL"){
                mp_server = QString(ip_address).append("@@");

            }else if(mp_server.startsWith("mpserver")){
                mp_server = mp_server.append("##");
            }
            qDebug() << "P=" << i << line.section(':', 0, 0) << parts.at(0) << callsign << mp_server;

            pilot_count++;

        }
    }
    //** Update the tree
    //QList<QTreeWidgetItem*> items = treeWidget->findItems(ip_address, Qt::MatchExactly, C_PILOTS_COUNT);

}
