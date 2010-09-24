#ifndef AIRPORTSDB_H
#define AIRPORTSDB_H

#include <QObject>

#include <QtSql/QSqlDatabase>


class AirportsDb : public QObject
{
Q_OBJECT
public:
    explicit AirportsDb(QObject *parent = 0);
    QSqlDatabase db;

    bool tables_ok();
    bool create_tables();
signals:

public slots:

};

#endif // AIRPORTSDB_H
