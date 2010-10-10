#ifndef NAVDATPARSER_H
#define NAVDATPARSER_H

#include <QObject>
#include <QtCore/QStringList>

class NavDatParser : public QObject
{
Q_OBJECT
public:
    explicit NavDatParser(QObject *parent = 0);

    bool process_ndb(QStringList parts);
    bool process_vor(QStringList parts);
signals:

public slots:

};

#endif // NAVDATPARSER_H
