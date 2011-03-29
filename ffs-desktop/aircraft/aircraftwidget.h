#ifndef AIRCRAFTWIDGET_H
#define AIRCRAFTWIDGET_H

#include <QtGui/QWidget>
#include <QtGui/QAbstractButton>

#include <QtGui/QStandardItemModel>
#include <QtGui/QSortFilterProxyModel>
#include <QtGui/QTreeView>
#include <QtGui/QLabel>

#include <QtGui/QStatusBar>

#include "mainobject.h"

class AircraftWidget : public QWidget
{
Q_OBJECT
public:
	enum COLS{
		C_MODEL = 0,
		C_DESCRIPTION = 1,
		C_PATH = 2
	};

	explicit AircraftWidget(MainObject *mOb, QWidget *parent = 0);

	MainObject *mainObject;

	QLabel *aeroImageLabel;

private:
    QStandardItemModel *model;
    QSortFilterProxyModel *proxyModel;
    QTreeView *treeView;

    QLabel *lblAircraftModel;
    QLabel *lblAircraftDescription;

    QStatusBar *statusBarTree;
    QStatusBar *statusBarAero;

signals:
	void set_arg(QString action, QString arg, QString value);

public slots:
	void load_aircraft_shell();
	void load_aircraft_xml_set();

	void on_tree_selection_changed(const QItemSelection& selected, const QItemSelection& deselected);
	void on_auto_coordination(bool state);

    void on_view_button_clicked(QAbstractButton *button);
};

#endif // AIRCRAFTWIDGET_H
