
/*
  Peel of the robin and gets out the airports and runways and minimal hopefully

  TODO incomplete list

  step 1

  only load the ICAO aiports, ignore heliports and seway etc.. lite wiegt and wise..

  assumed is ils etc..
  Other aiports whousl be available on demand as a parse etc..
  eg integration with FG

  */


#include "aptdatparser.h"

#include <QtCore/QDebug>

#include <QtCore/QFile>
#include <QtCore/QIODevice>

#include <QtCore/QRegExp>
#include <QtCore/QStringList>
#include <QtCore/QString>
#include <QtCore/QVariant>
#include <QtCore/QByteArray>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

#include <QtGui/QProgressDialog>


/* From the guide >>

Each row of data has a numeric ‘row code’ as its first field, to define its content.
The top level of this hierarchy defines an individual airport, defined by an airport header row (a row code of ‘1’, ‘16’ or ‘17’).

1  = Land airport header
16 = Seaplane base header
17 = Heliport header
---
100 runway

--
 14 airport viewpoint
18 lightbeacon
19 windsock
---
50 - 56
Comms Freq

*/


AptDatParser::AptDatParser(QObject *parent) :
    QObject(parent)
{
    estimated_lines = 1510000;
    line_counter = -1;
    cancel_import_flag = false;
}

void AptDatParser::cancel_import(){
    cancel_import_flag = true;
}

void AptDatParser::import_aptdat(){





    qDebug("AptDatParser::process_file()");
    //Q//File file("/home/mash/ffs-desktop/apt.dat/apt.dat");
    QFile file("/home/ffs/ffs-desktop/apt.dat");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug("OOPS: file problem");
        return;
     }

    QSqlQuery queryC;
    queryC.exec("DROP TABLE IF EXISTS airports");
    queryC.exec("DROP TABLE IF EXISTS runways");
    queryC.exec("CREATE TABLE airports(airport varchar(10) NOT NULL PRIMARY KEY, name varchar(50) NULL, elevation int, tower tinyint NULL) ");
    queryC.exec("CREATE TABLE runways(airport varchar(10) NULL, runway varchar(3))");

    line_counter = 0;
    cancel_import_flag = false;
    QRegExp rxICAOAirport("[A-Z]{4}");

    QSqlQuery queryAirportInsert;
    queryAirportInsert.prepare("insert into airports( airport, name, elevation, tower)values(?, ?, ?, ?)");

    //QSqlQuery queryRwySel;
    //queryRwySel.prepare("select * from runways where airport=? and runway=?");
    //QSqlQuery queryRwyIns;
    //queryRwyIns.prepare("insert into runways(  airport, runway)values(?, ?)");


    bool success;
    QString airport;
    bool is_icao;

    QProgressDialog progress("Importing Airports", "Cancel", 0, estimated_lines);
    //QProgressDialog()
    progress.setWindowModality(Qt::WindowModal);

    while( !file.atEnd() ){
//        if(cancel_import_flag == true){
//            qDebug("Cancelled");
//            return;
//        }

        QByteArray lineBytes = file.readLine();
        QString line = QString(lineBytes).trimmed();
        //qDebug() << line;
        QString row_code = line.section(' ',0, 0);
        //qDebug() << row_code;
        QStringList parts = line.split(" ", QString::SkipEmptyParts);

        //*** Airport
        if(row_code == "1"){
            airport = parts[4];
            is_icao = rxICAOAirport.exactMatch(airport);
            int elevation = parts[1].toInt();
            QString airport_name;
            for(int p = 5; p < parts.size(); p++){ //** TODO WTF ?
                airport_name.append(parts[p]).append(" ");
            }
            QString tower =  parts[2] == "1" ? "1" : "";
            if(is_icao){
                //qDebug() << airport;
                queryAirportInsert.addBindValue( airport);
                queryAirportInsert.addBindValue( airport_name.trimmed() );
                queryAirportInsert.addBindValue( elevation);
                queryAirportInsert.addBindValue( parts[2] == "1" ? "1" : NULL );
                success = queryAirportInsert.exec();
                if(!success){
                    qDebug() << queryAirportInsert.lastError();
                    qDebug() << "DIE queryApt";
                    return;
                }
                //emit airport_data(airport, airport_name.trimmed(), parts[1], parts[2] == "1" ? "1" : "");
            }
            //qDebug() << "APT Line=" << aiport_code << "=" << is_icao;  //<< " >> " << line << "  "
            //qDebug() << "Parts   =" << parts.join("#");
            //qDebug(""); // << "Airport" << line << " = ";
        }

        //*** Runway
        if(row_code == "100"){
            if(is_icao){
                QString runway = parts[8];
            //QString ki = QString("%1/%2").arg(airport).arg(runway);
//                queryRwySel.addBindValue(airport);
//                queryRwySel.addBindValue(runway);
//                ok = queryRwySel.exec();
//                if(!ok){
//                    qDebug() << queryRwySel.lastError();
//                    qDebug() << "DIE queryRwySel";
//                    return;
//                }
//                if(queryRwySel.size() == 0){
//
//                    qDebug() << airport << " = " << runway;
//                    //queryRwyIns.addBindValue( ki);
//                    queryRwyIns.addBindValue( airport);
//                    queryRwyIns.addBindValue( runway );
//
//
//                    ok = queryRwyIns.exec();
//                    if(!ok){
//                        qDebug() << queryRwyIns.lastError();
//                        qDebug() << "DIE queryRwyIns";
//                        return;
//                    }
//                }
        }
//            bool is_icao = rxICAOAirport.exactMatch(airport_code);
//            int elevation = parts[1].toInt();
//            QString airport;
//            for(int p = 5; p < parts.size(); p++){
//                airport.append(parts[p]).append(" ");
//            }
//            QString tower =  parts[2] == "1" ? "1" : "";
//            if(is_icao){
//                queryApt.addBindValue( airport_code);
//                queryApt.addBindValue( airport.trimmed() );
//                queryApt.addBindValue( elevation);
//                queryApt.addBindValue( parts[2] == "1" ? "1" : NULL );
//                ok = queryApt.exec();
//                if(!ok){
//                    qDebug() << queryApt.lastError();
//                }
//            }
            //qDebug() << "APT Line=" << aiport_code << "=" << is_icao;  //<< " >> " << line << "  "
            //qDebug() << "Parts   =" << parts.join("#");
            //qDebug(""); // << "Airport" << line << " = ";
        }

        if (progress.wasCanceled()){
            return;
        }
        line_counter++;
        progress.setValue(line_counter);
       //if(line_counter % 1000 == 0){
        //    emit line_count(line_counter);
       // }
        //qDebug() << line_counter;
        //if(line_counter == 200){
            //return;
        //}
        //process_line(line);
    }
}
