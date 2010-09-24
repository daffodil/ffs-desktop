

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

    //QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("mash");
    db.setDatabaseName("ffs-desktop");
    //db.setDatabaseName("/home/ffs/ffs-desktop/data.db");

    bool dbOk = db.open();
    if(!dbOk){
        qDebug() << "Open error" << db.lastError();
        return;
    }
    //** Check Tables
    QSqlQuery queryT;
    bool okT;
    okT = queryT.exec("show tables like 'airports';");
    //okT = queryT.exec("SELECT name FROM sqlite_master WHERE name='table_name'");
      qDebug() << "okT= " << okT << " = " << queryT.size();
      if(queryT.size() == 0){
            queryT.exec("CREATE TABLE airports(code varchar(10) NOT NULL PRIMARY KEY, airport varchar(50) NULL, elevation int, tower tinyint NULL) ");
      }
      /*
    while (queryT.next()) {
             QString name = queryT.value(0).toString();
             //int salary = query.value(1).toInt();
             qDebug() << name ;//<< salary;
     }*/
    //return;
   // qDebug() << "db.open= " << dbOk;
    QSqlQuery query;
    bool ok = query.exec("SELECT * FROM airports");
    if(ok){
        while (query.next()) {
                 QString name = query.value(0).toString();
                // int salary = query.value(1).toInt();
                 qDebug() << name ;
         }
    }else{
       qDebug() << query.lastError();
    }
    //while (query.next())
   // {
    //  qDebug("NO");
    //}

}
void AptDatParser::process_file(){



    qDebug("AptDatParser::process_file()");
    QFile file("/home/ffs/ffs-desktop/peel/apt.dat");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug("OOPS: file problem");
        return;
     }

    QRegExp rxICAOAirport("[A-Z]{1,4}");

    QSqlQuery queryApt;
    queryApt.prepare("replace into airports(code, airport, elevation, tower)values(?, ?, ?, ?)");
    bool ok;

    //okT = queryT.exec("show tables like 'airports';");
    int c = 0;
    while( !file.atEnd() ){
        QByteArray lineBytes = file.readLine();
        QString line = QString(lineBytes).trimmed();
        //qDebug() << line;
        QString row_code = line.section(' ',0, 0);
        //qDebug() << row_code;
        QStringList parts = line.split(" ", QString::SkipEmptyParts);

        //*** Airport
        if(row_code == "1"){
            QString airport_code = parts[4];
            bool is_icao = rxICAOAirport.exactMatch(airport_code);
            int elevation = parts[1].toInt();
            QString airport;
            for(int p = 5; p < parts.size(); p++){
                airport.append(parts[p]).append(" ");
            }
            QString tower =  parts[2] == "1" ? "1" : "";
            if(is_icao){
                queryApt.addBindValue( airport_code);
                queryApt.addBindValue( airport.trimmed() );
                queryApt.addBindValue( elevation);
                queryApt.addBindValue( parts[2] == "1" ? "1" : NULL );
                ok = queryApt.exec();
                if(!ok){
                    qDebug() << queryApt.lastError();
                }
            }
            //qDebug() << "APT Line=" << aiport_code << "=" << is_icao;  //<< " >> " << line << "  "
            //qDebug() << "Parts   =" << parts.join("#");
            //qDebug(""); // << "Airport" << line << " = ";
        }

        c++;
        if(c == 20000){
            return;
        }
        //process_line(line);
    }
}

//    self.read_line()
//            self.read_line()
//            self.read_line()
//
//            airports = {}
//            c = 0
//            while 1:
//                    line = self.read_line()
//                    #print c, line
//                    #print line
//                    if line != '':
//                            cols = line.split()
//                            ## aiport, seaplane, heliport
//                            akey = cols[0]
//
//                            heliports = []
//                            seaports = []
//                            if akey != '99':
//                                    if akey in ['1', '16', '17']:
//                                            seaport = True if akey == '16' else False
//                                            heliport = True if akey == '17' else False
//                                            #                            icoa,    name,    seaport, heliport, elev,    atc
//                                            #print cols
//                                            airport = " ".join(cols[5:])
//                                            icao = str(cols[4])
//                                            #self.airports_csv.writerow( [cols[4], airport, seaport, heliport, cols[1], cols[2]] )
//                                            airports[icao] = {
//                                                            'name': str(airport),
//                                                            'seaport': seaport,
//                                                            'heliport': heliport,
//                                                            'elevation': int(cols[1]),
//                                                            'atc': bool(cols[2])
//                                            }
//
//                                            #yaml.dump(yam, self.airports_yaml, width=500, indent=4)
//                                            if c % 100 == 0:
//                                                    print c, cols[4], airport
//                                            if c == 1000:
//                                                    print "break"
//                                                    break
//                                            c += 1
//            sorted_airports = sorted(airports.keys())
//            print sorted_airports
//            for ki in sorted_airports:
//                    data = {ki: airports[ki]}
//                    yaml.dump(data, self.airports_yaml, width=500, indent=4)
//            print "### done ####"
//            self.close()

