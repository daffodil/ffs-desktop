#ifndef AIRPORTSWIDGET_H
#define AIRPORTSWIDGET_H

#include "airports/airportsdb.h"
#include "mainobject.h"

#include <QtGui/QWidget>
#include <QtGui/QStandardItemModel>
#include <QtGui/QSortFilterProxyModel>
#include <QtGui/QTreeView>
#include <QtGui/QStatusBar>

class AirportsWidget : public QWidget
{
Q_OBJECT
public:

    explicit AirportsWidget(MainObject *mOb, QWidget *parent = 0);

    MainObject *mainObject;
    AirportsDb *airportsDb;

    QStandardItemModel *model;
    QSortFilterProxyModel *proxyModel;
    QTreeView *treeView;

    QStatusBar *statusBarTree;
signals:

public slots:
    void load_airports();
    void load_airports_db();

    void on_airport(QString,QString,QString,QString);
};

#endif // AIRPORTSWIDGET_H