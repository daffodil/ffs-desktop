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
#include <QtGui/QProgressBar>

class AirportsWidget : public QWidget
{
Q_OBJECT
public:
    enum COLS{
        C_FAV = 0,
        C_CODE = 1,
        C_TOWER = 2,
        C_ELEVATION = 3,
        C_NAME = 4
    };

    explicit AirportsWidget(MainObject *mOb, QWidget *parent = 0);

    MainObject *mainObject;
    AirportsDb *airportsDb;

    QStandardItemModel *model;
    QSortFilterProxyModel *proxyModel;
    QTreeView *treeView;

    QStatusBar *statusBarTree;
    QProgressBar *progressAirportsLoad;

    QLineEdit *txtAirportsFilter;
    QButtonGroup *buttGroupFilter;

    QTreeWidget *treeWidgetRunways;

signals:

public slots:
    void load_airports();
    void import_airports_dialog();

    void on_airport(QString, QString, QString, QString);
    //void update_airports_count();
    void on_update_filter();
    void on_aiport_clicked(const QItemSelection&, const QItemSelection&);
};

#endif // AIRPORTSWIDGET_H
