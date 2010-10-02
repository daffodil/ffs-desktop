
#include "airportsdb.h"

#include <QtCore/QDebug>

#include <QtCore/QVariant>
#include <QtCore/QString>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>


AirportsDb::AirportsDb( QObject *parent) :
    QObject(parent)
{
    //mainObject = mOb;

    //QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //db = QSqlDatabase::addDatabase("QMYSQL");
    //db.setHostName("192.168.5.10");
   // db.setUserName("root");
   // db.setPassword("mash");
   // db.setDatabaseName("ffs-desktop");
    //db.setDatabaseName("/home/ffs/ffs-desktop/data.db");
}


//** Check Tables
bool AirportsDb::check_tables(){
    QSqlQuery query;
    bool okT;
    okT = query.exec("show tables like 'airports';");
    //okT = query.exec("SELECT name FROM sqlite_master WHERE name='table_name'");
    //qDebug() << "okT= " << okT << " = " << queryT.size();
    return query.size() == 0;
}

bool AirportsDb::create_tables(){
//    QSqlQuery query;
//    query.exec("DROP TABLE IF EXISTS airports");
//    query.exec("DROP TABLE IF EXISTS runways");
//    query.exec("CREATE TABLE airports(airport varchar(10) NOT NULL PRIMARY KEY, name varchar(50) NULL, elevation int, tower tinyint NULL) ");
//    query.exec("CREATE TABLE runways(airport varchar(10) NULL, runway varchar(3))");
//    qDebug() << "dropped" << query.lastError();
    return true;
}

void AirportsDb::airports(){
    QSqlQuery query;
    bool success;
    success = query.exec("SELECT airport, name, tower, elevation from airports order by airport");
    if(!success){
        qDebug() << "SELECT" << query.lastError();
        return;
    }
    while (query.next()) {
        //QString name = query.value(0).toString();
        // int salary = query.value(1).toInt();
        //qDebug() << name ;
        emit airport(query.value(0).toString(),
                     query.value(1).toString(),
                     query.value(2).toString(),
                     query.value(3).toString()
                    );
    }
    //emit airports_count(query.size());
}

//*****************************************************************
//** Runways
void AirportsDb::runways(QString airport){
    QSqlQuery query;
    // success;
    query.prepare("SELECT runway from runways where airport=? order by runway");
    bool success = query.exec();
    if(!success){
        qDebug() << "SELECT" << query.lastError();
        return;
    }
    while (query.next()) {
        //QString name = query.value(0).toString();
        // int salary = query.value(1).toInt();
        //qDebug() << name ;
    }
    return;
}

