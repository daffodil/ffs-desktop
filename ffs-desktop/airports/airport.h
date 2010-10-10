#ifndef AIRPORT_H
#define AIRPORT_H

#include <QObject>

#include "airports/tower.h"
#include "airports/runway.h"

#include <QtCore/QString>
#include <QtCore/QList>

class Airport : public QObject
{
Q_OBJECT
public:
    explicit Airport(QObject *parent = 0);

    bool load(QString airport_code);
    QString code();
    QString name();
    Tower tower();

    QList<Runway> runways;

    static void add_fav(QString airport);
    static void remove_fav(QString airport);



signals:

public slots:

};

#endif // AIRPORT_H
