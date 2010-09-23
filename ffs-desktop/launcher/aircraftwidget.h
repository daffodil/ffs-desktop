#ifndef AIRCRAFTWIDGET_H
#define AIRCRAFTWIDGET_H

#include <QtGui/QWidget>
#include <QtGui/QAbstractButton>

#include <QtGui/QStandardItemModel>
#include <QtGui/QSortFilterProxyModel>
#include <QtGui/QTreeView>
#include <QtGui/QLabel>

#include <QtGui/QStatusBar>

class AircraftWidget : public QWidget
{
Q_OBJECT
public:
    explicit AircraftWidget(QWidget *parent = 0);

private:
    QStandardItemModel *model;
    QSortFilterProxyModel *proxyModel;
    QTreeView *treeView;

    QLabel *lblAircraftModel;
    QLabel *lblAircraftDescription;

    QStatusBar *statusBarTree;
    QStatusBar *statusBarAero;

signals:

public slots:
    void load_aircraft();
    void show_aircraft_details(const QModelIndex &current, const QModelIndex &previous);
    void on_tree_clicked(QModelIndex);
    void on_view_button_clicked(QAbstractButton *button);
};

#endif // AIRCRAFTWIDGET_H
