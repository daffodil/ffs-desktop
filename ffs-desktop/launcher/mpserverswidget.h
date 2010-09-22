#ifndef MPSERVERS_H
#define MPSERVERS_H

#include <QWidget>
#include <QtNetwork/QHostInfo>

#include <QtGui/QTreeWidget>


class MpServersWidget : public QWidget
{
Q_OBJECT
public:
    static const int C_SERVER_NO =0;
    static const int C_DOMAIN_NAME = 1;
    static const int C_ADDRESS = 2;
    static const int C_FLAG = 3;

    explicit MpServersWidget(QWidget *parent = 0);

    QTreeWidget *treeWidget;


    void dns_lookup(int server_no);


signals:

public slots:
     void dns_lookup_all();
     void on_dns_lookup_host(const QHostInfo &hostInfo);
};

#endif // MPSERVERS_H
