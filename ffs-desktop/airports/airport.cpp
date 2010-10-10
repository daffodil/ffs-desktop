
#include "airport.h"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

#include <QtDebug>

Airport::Airport(QObject *parent) :
    QObject(parent)
{
}

void Airport::add_fav(QString airport){
    QSqlQuery q;
//    q.prepare("delete from airport_favs where airport=?");
//    q.addBindValue(airport);
//    if(!q.exec()){
//        qDebug() << q.lastError();
//    }
}

void Airport::remove_fav(QString airport){
    QSqlQuery q;
//    q.prepare("delete from airport_favs where airport=?");
//    q.addBindValue(airport);
//    if(!q.exec()){
//        qDebug() << q.lastError();
//    }
}
