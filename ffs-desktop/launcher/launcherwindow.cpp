
#include <QtGui/QVBoxLayout>
#include <QtGui/QHeaderView>

#include "launcher/launcherwindow.h"

LauncherWindow::LauncherWindow(MainObject *mainOb, QWidget *parent)
    : QMainWindow(parent)
{

    mainObject = mainOb;
	setProperty("settings_namespace", QVariant("launcher_window"));
	mainObject->settings->restoreWindow(this);

	setWindowTitle("fgX Launcher");
	setWindowIcon(QIcon(":/icons/launcher"));
    //setWindowFlags(  Qt::WindowStaysOnTopHint);


    //* MainWidget and MainLayout
    QWidget *mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);


    QVBoxLayout *mainVBox = new QVBoxLayout();
    mainVBox->setContentsMargins(0,0,0,0);
    mainVBox->setSpacing(0);
    mainWidget->setLayout(mainVBox);

	//** Header Banner across the top =========================
	QString header_style("padding: 10px; font-size: 11pt; font-weight: bold; background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 white, stop: 1 #F0DD17);");
    headerLabel = new QLabel(this);
	headerLabel->setText("fgX Launcher");
	headerLabel->setStyleSheet(header_style);
	mainVBox->addWidget(headerLabel, 0);

	splitter = new QSplitter();
	mainVBox->addWidget(splitter, 20);

	//** Main Tab =========================
    tabWidget = new QTabWidget(this);
	splitter->addWidget(tabWidget);
	connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(on_tab_changed(int)));

	//==================================================
	// Widgets

	//* Options
	mainOptionsWidget = new MainOptionsWidget(mainObject);
	tabWidget->addTab(mainOptionsWidget, tr("Main Options"));
	connect(mainOptionsWidget, SIGNAL(set_arg(QString,QString,QString)), this, SLOT(set_arg(QString,QString,QString)));

	//* MpServers
	mpServersWidget = new MpServersWidget(mainObject);
	tabWidget->addTab(mpServersWidget, tr("Multi Player Server"));
	connect(mpServersWidget, SIGNAL(set_arg(QString,QString,QString)), this, SLOT(set_arg(QString,QString,QString)));



	//* Aircraft Widget
	aircraftWidget = new AircraftWidget(mainObject);
	tabWidget->addTab(aircraftWidget, tr("Aircraft"));
	connect(aircraftWidget, SIGNAL(set_arg(QString,QString,QString)), this, SLOT(set_arg(QString,QString,QString)));






	//* Airports Widget
    airportsWidget = new AirportsWidget(mainObject);
    tabWidget->addTab(airportsWidget, tr("Airports"));
	connect(airportsWidget, SIGNAL(set_arg(QString,QString,QString)), this, SLOT(set_arg(QString,QString,QString)));

	//=============================================================
	// ## Tree
	tree = new QTreeWidget();
	tree->setRootIsDecorated(false);
	tree->setMinimumWidth(400);
	tree->headerItem()->setText(0, "Option");
	tree->headerItem()->setText(1, "Value");
	tree->header()->setStretchLastSection(true);
	tree->setColumnWidth(C_ARG, 200);
	splitter->addWidget(tree);
	setup_tree();

	splitter->setStretchFactor(0,3);
	splitter->setStretchFactor(1,1);


    //*********************************************************
    //** Control Bar
    //*********************************************************
    controlBarWidget = new ControlBarWidget(mainObject);
    mainVBox->addWidget(controlBarWidget, 1);
    //controlBarWidget->hide();

	set_paths();

}

LauncherWindow::~LauncherWindow()
{
}



//void LauncherWindow::closeEvent( event ){
//   //     self.main.settings.save_window( "account_dialog", self )
//    qDebug() << "close";
//}

void LauncherWindow::closeEvent(QCloseEvent *event){
	Q_UNUSED(event);
    mainObject->settings->saveWindow(this);
}



void LauncherWindow::on_tab_changed(int tab_index){
	Q_UNUSED(tab_index);
	//TODO maybe we dont need this..
	// pusedo code
	// if isistance(widget, FooClass) : load()
}


void LauncherWindow::setup_tree(){
	return;
	QStringList args;
	args << "fgfs" << "--fg-root" << "--aircraft" << "--airport" << "--runway" << "--callsign";

	for (int i = 0; i < args.size(); ++i){
		QTreeWidgetItem *item = new QTreeWidgetItem();
		item->setText(0, args.at(i));
		tree->addTopLevelItem(item);
	}
}


void LauncherWindow::set_arg(QString action, QString arg, QString val){
	qDebug() << "set_arg" << action << " " << arg << " " << val;
	QList<QTreeWidgetItem *> items = tree->findItems(arg, Qt::MatchExactly, 0);

	if(action == "remove"){
		if(items.count() == 0){ //* item not there
			return;
		}
		QTreeWidgetItem *removeItem = items.first();
		tree->invisibleRootItem()->removeChild(removeItem);
		return;
	}

	if(action == "set"){
		if(items.count() == 0){
			QTreeWidgetItem *newItem = new QTreeWidgetItem(); //* add Item if not exist
			newItem->setText(C_ARG, arg);
			newItem->setTextAlignment(C_ARG, Qt::AlignRight);
			newItem->setText(C_VAL, val);
			tree->addTopLevelItem(newItem);
			return;
		}else{
			QTreeWidgetItem *item =  items.first();  //* update existing
			item->setText(C_VAL, val);
			return;
		}

	}
	qDebug() << "UNHANDLED";

}

void LauncherWindow::set_paths(){
	set_arg("set", "fgfs", mainObject->settings->fgfs_path());
	set_arg("set", "--fg-root=", mainObject->settings->fg_root());
}
