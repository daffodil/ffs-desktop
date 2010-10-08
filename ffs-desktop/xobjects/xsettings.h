#ifndef XSETTINGS_H
#define XSETTINGS_H

#include <QSettings>

class XSettings : public QSettings
{
Q_OBJECT
public:
    explicit XSettings(QObject *parent = 0);

    QString _temp;
    QString temp();
    QString temp(QString append_path);

    QString fg_root();
    QString fg_root(QString append_path);

signals:

public slots:

};

#endif // XSETTINGS_H
