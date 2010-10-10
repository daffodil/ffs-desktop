#include "navdatparser.h"

NavDatParser::NavDatParser(QObject *parent) :
    QObject(parent)
{
}

bool NavDatParse::parse_ndb_line(){
    // 2  49.01544444 -122.48777778      0   344  50    0.0 XX   ABBOTSFORD NDB
    // 2  00.50000000  173.85000000    108   396  25    0.0 AA   ABEMAMA NDB
    // lat             lng             elev freq range void ID Name

}

bool NavDatParse::parse_vor_line(){
    //3  24.44319400  054.64647200     68 11300 100    0.0 AUH  ABU DHABI VOR-DME
    //3  22.35488900  031.62200000    640 11350 200    2.0 SML  ABU SIMBEL VOR-DME
    //3  09.03779700  007.28509700   1240 11630  40   -2.0 ABC  ABUJA VOR-DME
    //  lat             lng          elev freq  rng ?slave ID  >>name

}
