#ifndef APTDATPARSER_H
#define APTDATPARSER_H

#include <QtCore/QObject>
#include <QtCore/QString>


class AptDatParser : public QObject
{
Q_OBJECT
public:

    explicit AptDatParser(QObject *parent = 0);

    int estimated_lines;
    int line_counter;
    bool cancel_import_flag;
    void import_aptdat();

signals:
    void airport_data(QString, QString, QString, QString);
    void runway_data(QString, QString);
    void line_count(int);

public slots:
    void cancel_import();
};

#endif // APTDATPARSER_H
