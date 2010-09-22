#ifndef AIRCRAFTWIDGET_H
#define AIRCRAFTWIDGET_H

#include <QtGui/QWidget>

#include <QtGui/QStandardItemModel>
#include <QtGui/QTreeView>
#include <QtGui/QSortFilterProxyModel>

class AircraftWidget : public QWidget
{
Q_OBJECT
public:
    explicit AircraftWidget(QWidget *parent = 0);

private:
    QStandardItemModel *model;
    QSortFilterProxyModel *proxyModel;
    QTreeView *treeView;

signals:

public slots:
    void on_load();
    void set_aircraft();
};

#endif // AIRCRAFTWIDGET_H
