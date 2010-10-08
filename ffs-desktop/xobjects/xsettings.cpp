#include "xsettings.h"

XSettings::XSettings(QObject *parent) :
    QSettings(parent)
{
}

QString XSettings::fg_root(){
    return this->value("FG_ROOT", "/usr/share/games/FlightGear/").toString();
}

QString XSettings::fg_root(QString append_path){
    return this->fg_root().append(append_path);

                    //.toString().append(append_path);
    //return xpath;
}
