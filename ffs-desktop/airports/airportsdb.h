#ifndef AIRPORTSDB_H
#define AIRPORTSDB_H

#include <QObject>

#include <QtSql/QSqlDatabase>

//#include "mainobject.h"

class AirportsDb : public QObject
{
Q_OBJECT
public:
    explicit AirportsDb(QObject *parent = 0);

    //MainObject *mainObject;
    QSqlDatabase db;

    bool check_tables();
    bool create_tables();
    void airports();
    void runways(QString airport);


signals:
    void airport(QString, QString, QString, QString);

public slots:
    void insert_airport(QString, QString, QString, QString);
};

#endif // AIRPORTSDB_H
