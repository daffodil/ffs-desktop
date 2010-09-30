
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
    QSqlQuery query;
    query.exec("CREATE TABLE airports(airport varchar(10) NOT NULL PRIMARY KEY, name varchar(50) NULL, elevation int, tower tinyint NULL, INDEX (name)) ");
    query.exec("CREATE TABLE runways(airport varchar(10) NULL, runway varchar(3), INDEX (airport, runway))");
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

//*****************************************************************
//** Insert Airport
void AirportsDb::insert_airport(QString airport, QString airport_name, QString elevation, QString tower){
    qDebug() << "insert_airport() = " << airport;
   // QRegExp rxICAOAirport("[A-Z]{1,4}");

    QSqlQuery queryAptInsert;
    queryAptInsert.prepare("insert into airports( airport, name, elevation, tower)values(?, ?, ?, ?)");

    QSqlQuery queryRwySel;
    queryRwySel.prepare("select * from runways where airport=? and runway=?");
    QSqlQuery queryRwyIns;
    queryRwyIns.prepare("insert into runways(  airport, runway)values(?, ?)");


    bool ok;
    int c = 0;

    //QString airport;
    //bool is_icao;


    queryAptInsert.addBindValue( airport );
    queryAptInsert.addBindValue( airport_name );
    queryAptInsert.addBindValue( elevation );
    queryAptInsert.addBindValue( tower );
            ok = queryAptInsert.exec();

       // }

}
//
//
//                qDebug() << airport << " = " << runway;
//                //queryRwyIns.addBindValue( ki);
//                queryRwyIns.addBindValue( airport);
//                queryRwyIns.addBindValue( runway );
//
//
//                ok = queryRwyIns.exec();
//                if(!ok){
//                    qDebug() << queryRwyIns.lastError();
//                    qDebug() << "DIE queryRwyIns";
//                    return;
//                }
//            }


