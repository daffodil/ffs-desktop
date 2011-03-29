

#include <QtCore/QString>
#include <QtCore/QChar>
#include <QtCore/QMap>
#include <QtCore/QMapIterator>


#include <QVBoxLayout>

#include <QtNetwork/QHostInfo>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QNetworkInterface>

#include <QtGui/QBrush>
#include <QtGui/QColor>

#include <QtGui/QVBoxLayout>
#include <QtGui/QAction>
#include <QtGui/QProgressBar>
#include <QtGui/QLabel>
#include <QtGui/QTreeWidgetItem>
#include <QtGui/QHeaderView>
#include <QToolButton>

#include "mp/mpserverswidget.h"
#include "mp/mptelnet.h"

/* list the Mp Servers which are gotten from a DNS lookup

*/


MpServersWidget::MpServersWidget(MainObject *mOb, QWidget *parent) :
    QWidget(parent)
{
	mainObject = mOb;

    //* Main Layout
    QVBoxLayout *mainLayout = new QVBoxLayout();
    setLayout(mainLayout);
    mainLayout->setSpacing(0);
	int m = 10;
	mainLayout->setContentsMargins(m,m,m,m);


	//** MiddleLayout
	QHBoxLayout *middleLayout = new QHBoxLayout();
	mainLayout->addLayout(middleLayout);
	middleLayout->setSpacing(10);
	int mm = 10;
	middleLayout->setContentsMargins(mm,mm,mm,mm);

	//========================================================================
	// Mp Servers Box
	grpMpServer  = new QGroupBox("Enable Multiplayer");
	middleLayout->addWidget(grpMpServer);
	grpMpServer->setCheckable(true);

	QVBoxLayout *layoutMpServer = new QVBoxLayout();
	grpMpServer->setLayout(layoutMpServer);

	//** Top Hoizontal
	QHBoxLayout *layoutTreeBar = new QHBoxLayout();
	layoutMpServer->addLayout(layoutTreeBar);

	//** Callsign
	layoutTreeBar->addWidget(new QLabel("Callsign:"));
	txtCallSign = new QLineEdit();
	txtCallSign->setText("");
	txtCallSign->setMaximumWidth(100);
	txtCallSign->setMaxLength(7);
	layoutTreeBar->addWidget(txtCallSign);
	connect(txtCallSign, SIGNAL(textChanged(QString)), this, SLOT(on_callsign_changed(QString)) );

	//layoutTreeBar->addStretch(20);

    treeWidget = new QTreeWidget();
	layoutMpServer->addWidget(treeWidget, 100);
    treeWidget->setAlternatingRowColors(true);
    treeWidget->setRootIsDecorated(false);


    QTreeWidgetItem * headerItem = treeWidget->headerItem();
    headerItem->setText(C_SERVER_NO, tr("No"));
    headerItem->setText(C_SERVER_NAME, tr("Name"));
    headerItem->setText(C_DOMAIN, tr("Domain"));
    headerItem->setText(C_IP_ADDRESS, tr("IP Address"));
    headerItem->setText(C_PILOTS_COUNT, tr("Pilots"));
	headerItem->setText(C_FLAG, "-");
    treeWidget->header()->setStretchLastSection(true);
    treeWidget->setColumnWidth(C_SERVER_NO, 40);
    treeWidget->setColumnWidth(C_SERVER_NAME, 110);
    treeWidget->setColumnWidth(C_DOMAIN, 100);
	treeWidget->setColumnWidth(C_PILOTS_COUNT, 50);
	treeWidget->setColumnWidth(C_FLAG, 10);

	treeWidget->setColumnHidden(C_DOMAIN, true);

	connect(treeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(on_tree_selection_changed()));

	//************* Bottom Layout
	QHBoxLayout *layoutBottomTreeBar = new QHBoxLayout();
	layoutMpServer->addLayout(layoutBottomTreeBar);
	layoutBottomTreeBar->addStretch(30);

	//* refresh MP servers
	QToolButton *refreshButton = new QToolButton(this);
	layoutBottomTreeBar->addWidget(refreshButton);
	refreshButton->setIcon(QIcon(":/icons/refresh"));
	refreshButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
	connect(refreshButton, SIGNAL(triggered()), this, SLOT(dns_lookup_all()) );


	//========================================================================
	// FgCom Box
	grpFgCom = new QGroupBox(tr("fgCom - Voice Communications"));
	middleLayout->addWidget(grpFgCom);
	grpFgCom->setCheckable(true);
	connect(grpFgCom, SIGNAL(clicked(bool)), this, SLOT(set_fgcom()));

	QVBoxLayout *layoutFgCom = new QVBoxLayout();
	grpFgCom->setLayout(layoutFgCom);

	QString style("font-size: 8pt; color: #666666;");

	// fgCom NO
	txtFgComNo = new QLineEdit("fgcom -Sfgcom.flightgear.org.uk");
	layoutFgCom->addWidget(txtFgComNo);
	connect(txtFgComNo, SIGNAL(textChanged(QString)), this, SLOT(set_fgcom()));

	QLabel *lblHelp1 = new QLabel("Call default FlightGear fgCom server");
	lblHelp1->setStyleSheet(style);
	layoutFgCom->addWidget(lblHelp1);


	layoutFgCom->addSpacing(10);


	// fgCom Port
	txtFgComPort = new QLineEdit("16661");
	txtFgComPort->setMaximumWidth(100);
	layoutFgCom->addWidget(txtFgComPort);
	connect(txtFgComPort, SIGNAL(textChanged(QString)), this, SLOT(set_fgcom()));

	QLabel *lblHelp2 = new QLabel("Default fgCom UDP port");
	lblHelp2->setStyleSheet(style);
	layoutFgCom->addWidget(lblHelp2);

	layoutFgCom->addStretch(30);

	// Load
	dns_lookup_all();


	QList<QHostAddress> addresses = QNetworkInterface::allAddresses();
	qDebug() << addresses;
}
/* end constructor */







//=============================================================
//** Dns Lookup All
void MpServersWidget::dns_lookup_all(){
    //TODO make the max a setting
	for(int i=1; i < 25; i++){ //*TODO - make this a setting for MAX top servers maybe remote ?
        dns_lookup(i);
    }
}

//** Dns Lookup (server_no)
void MpServersWidget::dns_lookup(int server_int){

    //* make server info
    QString domain_name = QString("mpserver%1.flightgear.org").arg(server_int, 2, 10, QChar('0'));
    QString server_name = QString("mpserver%1").arg(server_int, 2, 10, QChar('0'));
    QString server_no = QString("%1").arg(server_int, 2, 10, QChar('0'));


    //* find domain_name in tree and add if not there
    QList<QTreeWidgetItem*> items = treeWidget->findItems(domain_name, Qt::MatchExactly, C_DOMAIN);
    if(items.count() == 0){
        QTreeWidgetItem *newItem = new QTreeWidgetItem();
        newItem->setText(C_SERVER_NO, server_no);
        newItem->setText(C_SERVER_NAME, server_name);
        newItem->setText(C_DOMAIN, domain_name);

        newItem->setText(C_IP_ADDRESS, tr("Looking up"));
        QBrush b = newItem->foreground(MpServersWidget::C_IP_ADDRESS);
        b.setColor(QColor(100, 100, 100));
        newItem->setForeground(C_IP_ADDRESS, b);

        int newIdx = treeWidget->invisibleRootItem()->childCount();
		//m_Domain2Row.insert(domain_name, newIdx);
        treeWidget->insertTopLevelItem(newIdx, newItem);
    }
    //* execute lookup
    QHostInfo::lookupHost(domain_name, this, SLOT(on_dns_lookup_host(QHostInfo)));

}

// DNS Callback
void MpServersWidget::on_dns_lookup_host(const QHostInfo &hostInfo){

    //* Find row matching by domain
    QList<QTreeWidgetItem*> items = treeWidget->findItems(hostInfo.hostName(), Qt::MatchExactly, C_DOMAIN);

    //** Make the colors change if address found
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
     QBrush brush = items[0]->foreground(C_IP_ADDRESS);
     brush.setColor(color);
     items[0]->setForeground(C_IP_ADDRESS, brush);
     items[0]->setText(C_IP_ADDRESS, lbl);

     if(has_address){
		items[0]->setText(C_FLAG, "1");
        items[0]->setText(C_PILOTS_COUNT, tr("Wait"));
        MpTelnet *telnet = new MpTelnet(this );
        telnet->get_info(hostInfo.addresses().first().toString());
        connect(telnet, SIGNAL(telnet_data(QString, QString)),
                this, SLOT(on_telnet_data(QString, QString))
        );
        //TODO catch no return ? error ?
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
    qDebug() <<  "\n------------------------------\nReplyFrom=" << ip_address;

    //** Split the reply into lines and parse each line
    QStringList lines = telnet_reply.split("\n");
    QString line;
    int pilots_count = 0;
    QMap<QString, int> mServerCount;

    for(int i = 0; i < lines.size(); ++i){

        line = lines.at(i).trimmed();
        if(i == 0){
            // skip first line

        }else if(line.startsWith("#")){
            // skip lines starting with #

        }else if(line.length() == 0){
            // skip blank lines

        }else{

            //*** Process the line
            QStringList parts = line.split(" ");
            QString callsign = parts.at(0).split("@").at(0);
            QString mp_server = parts.at(0).split("@").at(1);
            QString mp_server_ip = QString("");
            mp_server = mp_server.replace(QString(":"), QString("")); //* get rid of trailing ":" at end eg a.b.c.192:

            //** Map to an IP address
            if(mp_server == "LOCAL"){
                //* Its ip_address from callback
                mp_server_ip = QString(ip_address);

            }else if(mp_server.startsWith("mpserver")){
                //* its mpserver__ so find in tree if avaiable
                // TODO insert unfound ip
                QList<QTreeWidgetItem*> items = treeWidget->findItems(mp_server, Qt::MatchExactly, C_SERVER_NAME);
                /*
                if(items.count() == 0){
                    mp_server_ip = "NOT_FOUND";
                    QTreeWidgetItem *newItem = new QTreeWidgetItem();
                    newItem->setText(C_IP_ADDRESS,ip_address);
                    newItem->setText(C_DOMAIN, "?");
                    treeWidget->addTopLevelItem(newItem);
                }else{
                    mp_server_ip = items[0]->text(C_IP_ADDRESS);
                }*/
                //qDebug() << "Found: " << mp_server << " = " << items.count();
            }else{
                //* Otherwise we got returned an ip address
                mp_server_ip = mp_server;
            }
            //** Increment pilot count
            if(mServerCount.contains(mp_server_ip)){
                mServerCount[mp_server_ip] = mServerCount[mp_server_ip] + 1;
            }else{
                mServerCount[mp_server_ip] = 1;
            }

            //qDebug() << "Found: " << mp_server << " == " << mp_server_ip;
            //qDebug() << "P=" << i << line.section(':', 0, 0) << parts.at(0) << callsign << mp_server;
            /*
            QTreeWidgetItem *headerItem = treeWidget->headerItem();
            qDebug("colsssssss--------------");
            int found_idx = -1;
            for(int colidx = 0; colidx < headerItem->columnCount(); ++colidx){

                if(headerItem->text(colidx) == server_no){
                    found_idx = colidx;
                    //break;
                }
                qDebug() << "HEADER" << colidx << headerItem->text(colidx) << colidx << found_idx;
            }
            if(found_idx == -1){
                headerItem->setText(headerItem->columnCount(), server_no);
                qDebug() << " >> added";
            }else{
               qDebug() << " >> skipped";
            }
            */
            pilots_count++;

        }
    } /* for lines() */
    QMapIterator<QString, int> i(mServerCount);
    while (i.hasNext()) {
        i.next();
        QList<QTreeWidgetItem*> items = treeWidget->findItems(i.key(), Qt::MatchExactly, C_IP_ADDRESS);
        if(items.count() == 1){
            qDebug() << "FoundRow" << i.key() ;
        }else{
            qDebug() << "Row no found" << i.key();
        }
        //qDebug() << i.key() << ": " << i.value() << endl;
    }
    //** Update the Pilots Count
    QList<QTreeWidgetItem*> items = treeWidget->findItems(ip_address, Qt::MatchExactly, C_IP_ADDRESS);
    //treeWidget->removeItemWidget(items[0], C_PILOTS_COUNT);
    items[0]->setText(C_PILOTS_COUNT, QString::number(pilots_count));
    //qDebug() >> "update=" << items.count();
}

//=====================================
// Callsign Changed
void MpServersWidget::on_callsign_changed(QString txt){
	QString callsign = txt.trimmed();
	if(callsign.length() == 0){
		emit set_arg("remove", "--callsign=","");


	}else{
		mainObject->lblCallsign->setText(callsign);
		emit set_arg("set", "--callsign=",callsign);
	}
}

//=====================================
// Mp Server Selected
void MpServersWidget::on_tree_selection_changed(){
	QTreeWidgetItem *item = treeWidget->currentItem();
	if(!item){
		//#emit set_arg("set", arg_name, item->text());
	}else{
		emit set_arg("set", "--mpserver", item->text(C_DOMAIN));
	}
}


//=====================================
// Setup fgCom
void MpServersWidget::set_fgcom(){
	if(grpFgCom->isChecked()){
		emit set_arg("set", "--fgcom=", txtFgComNo->text().append(":").append( txtFgComPort->text() ) );
	}else{
		emit set_arg("remove", "--fgcom=","");
	}
}

