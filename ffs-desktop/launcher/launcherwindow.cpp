#include <QtGui/QVBoxLayout>

#include "launcher/launcherwindow.h"

LauncherWindow::LauncherWindow(MainObject *mainOb, QWidget *parent)
    : QMainWindow(parent)
{

    mainObject = mainOb;
	setProperty("settings_namespace", QVariant("launcher_window"));
	mainObject->settings->restoreWindow(this);

	setWindowTitle("fgX Launcher");
    setWindowIcon(QIcon(":/icons/favicon"));
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
    mainVBox->addWidget(headerLabel, 1);

	//** Main Tab =========================
    tabWidget = new QTabWidget(this);
    mainVBox->addWidget(tabWidget,100);

	//* Map
	mpMapWidget = new MpMapWidget(this);
	tabWidget->addTab(mpMapWidget,QString("MP Map"));

	//* Settings - dead for now TODO
	//settingsWidget = new SettingsWidget(mainObject);
	//tabWidget->addTab(settingsWidget, tr("Settings"));

	//* MpServers
	mpServersWidget = new MpServersWidget();
	tabWidget->addTab(mpServersWidget, tr("Multi Player Server"));

	//* Options
	mainOptionsWidget = new MainOptionsWidget(mainObject);
	tabWidget->addTab(mainOptionsWidget, tr("Main Options"));


	//* Aircraft Widget
	aircraftWidget = new AircraftWidget();
	tabWidget->addTab(aircraftWidget, tr("Aircraft"));

	//* Airports Widget
    airportsWidget = new AirportsWidget(mainObject);
    tabWidget->addTab(airportsWidget, tr("Airports"));

	//* Props Tree - experimental
	propsTreeWidget = new PropsTreeWidget(mainObject);
	tabWidget->addTab(propsTreeWidget, tr("Property Tree"));



    //*********************************************************
    //** Control Bar
    //*********************************************************
    controlBarWidget = new ControlBarWidget(mainObject);
    mainVBox->addWidget(controlBarWidget, 1);
    //controlBarWidget->hide();

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
