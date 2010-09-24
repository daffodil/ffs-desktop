#ifndef AIRPORTSWIDGET_H
#define AIRPORTSWIDGET_H

#include <QtGui/QWidget>
#include <QtGui/QStandardItemModel>
#include <QtGui/QSortFilterProxyModel>
#include <QtGui/QTreeView>
#include <QtGui/QStatusBar>

class AirportsWidget : public QWidget
{
Q_OBJECT
public:

    explicit AirportsWidget(QWidget *parent = 0);

    QStandardItemModel *model;
    QSortFilterProxyModel *proxyModel;
    QTreeView *treeView;

    QStatusBar *statusBarTree;
signals:

public slots:
    void load_airports();
};

#endif // AIRPORTSWIDGET_H
