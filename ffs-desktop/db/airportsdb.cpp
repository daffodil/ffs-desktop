
#include "airportsdb.h"


#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>


AirportsDb::AirportsDb(QObject *parent) :
    QObject(parent)
{

    //QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("192.168.5.10");
    db.setUserName("root");
    db.setPassword("mash");
    db.setDatabaseName("ffs-desktop");
    //db.setDatabaseName("/home/ffs/ffs-desktop/data.db");
}


//** Check Tables
bool AirportsDb::tables_ok(){
    QSqlQuery query;
    bool okT;
    okT = query.exec("show tables like 'airports';");
    //okT = query.exec("SELECT name FROM sqlite_master WHERE name='table_name'");
    //qDebug() << "okT= " << okT << " = " << queryT.size();
    return query.size() == 0;
}

bool AirportsDb::create_tables(){
    QSqlQuery query;
    query.exec("CREATE TABLE airports(airport varchar(10) NOT NULL PRIMARY KEY, name varchar(50) NULL, elevation int, tower tinyint NULL, INDEX (name)) ");
    query.exec("CREATE TABLE runways(airport varchar(10) NULL, runway varchar(3), INDEX (airport, runway))");
    return true;
}

bool AirportsDb::airports(){
    QSqlQuery query;
    bool success;
    success = query.exec("SELECT * from airports");
    if(!success){
        qDebug() << "SELECT" << query.lastError();
        return;
    }

}


