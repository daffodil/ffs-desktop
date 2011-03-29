#ifndef MPSERVERS_H
#define MPSERVERS_H

#include <QWidget>
#include <QtNetwork/QHostInfo>

#include <QtGui/QTreeWidget>
#include <QtGui/QGroupBox>
#include <QtGui/QCheckBox>
#include <QtGui/QLineEdit>
#include <QtGui/QComboBox>

#include "mainobject.h"

class MpServersWidget : public QWidget
{
Q_OBJECT
public:

    enum COLS{
        C_SERVER_NO,
        C_SERVER_NAME,
        C_DOMAIN,
        C_PILOTS_COUNT,
		C_IP_ADDRESS,
		C_FLAG
    };

	explicit MpServersWidget(MainObject *mOb, QWidget *parent = 0);

	MainObject *mainObject;


	QGroupBox *grpMpServer;
	QLineEdit *txtCallSign;
	QComboBox *comboIpAddress;
	QComboBox *comboRemoteAddress;
	QTreeWidget *treeWidget;


	QGroupBox *grpFgCom;
	QLineEdit *txtFgComNo;
	QLineEdit *txtFgComPort;

    void dns_lookup(int server_no);
	void load_addresses();


signals:
	void set_arg(QString action, QString arg, QString value);

public slots:
     void dns_lookup_all();
     void on_dns_lookup_host(const QHostInfo &hostInfo);
     void on_telnet_data(QString, QString);

	 void on_mp_server_checked(bool);
	 void on_callsign_changed(QString);
	 void on_tree_selection_changed();

	 void set_fgcom();

};

#endif // MPSERVERS_H
