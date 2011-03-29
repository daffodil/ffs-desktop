#ifndef LAUNCHERWINDOW_H
#define LAUNCHERWINDOW_H

#include <QtGui/QMainWindow>



#include <QtGui/QLabel>
#include <QtGui/QTreeWidget>
#include <QtGui/QTabWidget>
#include <QtGui/QSplitter>

#include "mainobject.h"

#include "aircraft/aircraftwidget.h"
#include "airports/airportswidget.h"

#include "mp/mpserverswidget.h"
#include "launcher/mainoptionswidget.h"
#include "launcher/controlbarwidget.h"

class LauncherWindow : public QMainWindow
{
    Q_OBJECT

public:

	enum COLS{
		C_ARG = 0,
		C_VAL = 1
	};

    LauncherWindow(MainObject *mainOb, QWidget *parent = 0);
    ~LauncherWindow();

    MainObject *mainObject;

    QLabel *headerLabel;
	QSplitter *splitter;
    QTabWidget *tabWidget;
	QTreeWidget *tree;

    AircraftWidget *aircraftWidget;
    AirportsWidget *airportsWidget;
    MpServersWidget *mpServersWidget;
    MainOptionsWidget *mainOptionsWidget;

    ControlBarWidget *controlBarWidget;

    void closeEvent(QCloseEvent *event);
	void setup_tree();

public slots:
	void on_tab_changed(int);
	void set_arg(QString action, QString arg, QString val);
};

#endif // LAUNCHERWINDOW_H
