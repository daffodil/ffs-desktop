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
    void load_aircraft();
    void show_aircraft_details(const QModelIndex &current, const QModelIndex &previous);
    void on_tree_clicked(QModelIndex);
};

#endif // AIRCRAFTWIDGET_H
