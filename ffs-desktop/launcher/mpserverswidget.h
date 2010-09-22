#ifndef MPSERVERS_H
#define MPSERVERS_H

#include <QWidget>
#include <QtNetwork/QHostInfo>




class MpServersWidget : public QWidget
{
Q_OBJECT
public:
    explicit MpServersWidget(QWidget *parent = 0);

    void dns_lookup_all();
    void dns_lookup(int server_no);
    void on_dns_lookup_host(QHostInfo hostInfo);

signals:

public slots:

};

#endif // MPSERVERS_H
