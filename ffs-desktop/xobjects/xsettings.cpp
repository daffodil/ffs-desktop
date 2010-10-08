#include "xsettings.h"

#include <QtCore/QDebug>
#include <QtCore/QDir>

#include <QtGui/QDesktopServices>


XSettings::XSettings(QObject *parent) :
    QSettings(parent)
{
}

//*********************************************
//** fg_root()
QString XSettings::fg_root(){
    return this->value("FG_ROOT", "/usr/share/games/FlightGear/").toString();
}

QString XSettings::fg_root(QString append_path){
    return this->fg_root().append(append_path);
}


//*********************************************
//** temp
QString XSettings::temp(){
    //** Check the temp dubdirctory exists or create it
    if( _temp.length() == 0 ){
        QDir tmpDir = QDir(QDesktopServices::storageLocation(QDesktopServices::TempLocation));
        if(!tmpDir.exists("ffs-desktop")){
            tmpDir.mkdir("ffs-desktop");
        }
        _temp = QDesktopServices::storageLocation(QDesktopServices::TempLocation).append("/ffs-desktop/");
    }
    return _temp;
}
QString XSettings::temp(QString append_path){
    return this->temp().append(append_path);

}
