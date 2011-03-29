#ifndef MPSERVERS_H
#define MPSERVERS_H

#include <QWidget>
#include <QtNetwork/QHostInfo>

#include <QtGui/QTreeWidget>


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

    explicit MpServersWidget(QWidget *parent = 0);

    QTreeWidget *treeWidget;

	//QMap<QString, int> m_Ip2col;
    QMap<QString, int>m_Domain2Row;

    void dns_lookup(int server_no);



signals:
	void set_arg(QString action, QString arg, QString value);

public slots:
     void dns_lookup_all();
     void on_dns_lookup_host(const QHostInfo &hostInfo);
     void on_telnet_data(QString, QString);
	 void on_tree_selection_changed();
};

#endif // MPSERVERS_H
