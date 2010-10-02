#ifndef AIRPORTSWIDGET_H
#define AIRPORTSWIDGET_H

#include "airports/airportsdb.h"
#include "mainobject.h"

#include <QtGui/QWidget>
#include <QtGui/QStandardItemModel>
#include <QtGui/QSortFilterProxyModel>
#include <QtGui/QTreeView>
#include <QtGui/QTreeWidget>
#include <QtGui/QStatusBar>
#include <QtGui/QButtonGroup>
#include <QtGui/QRadioButton>

class AirportsWidget : public QWidget
{
Q_OBJECT
public:
    enum COLS{
        C_CODE = 0,
        C_NAME = 3,
        C_TOWER = 1,
        C_ELEVATION = 2
    };

    explicit AirportsWidget(MainObject *mOb, QWidget *parent = 0);

    MainObject *mainObject;
    AirportsDb *airportsDb;

    QStandardItemModel *model;
    QSortFilterProxyModel *proxyModel;
    QTreeView *treeView;

    QStatusBar *statusBarTree;

    QLineEdit *txtFindCode;
    QButtonGroup *buttViewGroup;

    QTreeWidget *treeWidgetRunways;

signals:

public slots:
    void load_airports();
    void import_airports_dialog();

    void on_airport(QString, QString, QString, QString);
    //void update_airports_count();
    void on_update_filter();
};

#endif // AIRPORTSWIDGET_H
