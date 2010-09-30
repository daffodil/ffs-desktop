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
    void import_aptdat();

signals:

public slots:
};

#endif // APTDATPARSER_H
