#ifndef IMPORTAIRPORTSWIDGET_H
#define IMPORTAIRPORTSWIDGET_H

#include <QWidget>
#include "mainobject.h"

class ImportAirportsWidget : public QWidget
{
Q_OBJECT
public:
    explicit ImportAirportsWidget(MainObject *mainOb, QWidget *parent = 0);
    MainObject *mainObject;


signals:

public slots:

};

#endif // IMPORTAIRPORTSWIDGET_H
