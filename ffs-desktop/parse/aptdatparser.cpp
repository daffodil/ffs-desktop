

#include "aptdatparser.h"

#include <QtCore/QDebug>
#include <QtCore/QByteArray>
#include <QtCore/QFile>
#include <QtCore/QIODevice>

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

}
void AptDatParser::process_file(){
    qDebug("AptDatParser::process_file()");
    QFile file("/home/ffs/ffs-desktop/peel/apt.dat");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug("OOPS: file problem");
        return;
     }

    int c = 0;
    while( !file.atEnd() ){
        QByteArray lineBytes = file.readLine();
        QString line = QString(lineBytes).trimmed();
        //qDebug() << line;
        QString row_code = line.section(' ',0, 0);
        //qDebug() << row_code;

        if(row_code == "1"){
            qDebug() << "Airport" << line;
        }

        c++;
        if(c == 1000){
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

