#ifndef APTDATPARSER_H
#define APTDATPARSER_H

#include <QObject>

#include <QtSql/QSqlDatabase>
class AptDatParser : public QObject
{
Q_OBJECT
public:
    enum ROW_CODES{
        C_AIRPORT = 1
    };
    explicit AptDatParser(QObject *parent = 0);

    QSqlDatabase db;
    void process_file();
signals:

public slots:

};

#endif // APTDATPARSER_H
