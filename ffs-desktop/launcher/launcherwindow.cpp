#include "launcher/launcherwindow.h"

#include <QtGui/QVBoxLayout>

LauncherWindow::LauncherWindow(MainObject *mainOb, QWidget *parent)
    : QMainWindow(parent)
{

    mainObject = mainOb;

    setWindowTitle("FlightGear Launcher");
    setWindowIcon(QIcon(":/icons/favicon"));
    //setWindowFlags(  Qt::WindowStaysOnTopHint);

    //* MainWidget and MainLayout
    QWidget *mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);


    QVBoxLayout *mainVBox = new QVBoxLayout();
    mainVBox->setContentsMargins(0,0,0,0);
    mainVBox->setSpacing(0);
    mainWidget->setLayout(mainVBox);


    headerLabel = new QLabel(this);
    headerLabel->setText("FG Launcher");
    headerLabel->setStyleSheet("font-size: 20pt; font-weight: bold; background-color: white;");
    mainVBox->addWidget(headerLabel, 1);

    tabWidget = new QTabWidget(this);
    mainVBox->addWidget(tabWidget,100);

   // mpMapWidget = new MpMapWidget(this);
    //tabWidget->addTab(mpMapWidget,QString("MP Map"));

    //settingsWidget = new SettingsWidget();
   // tabWidget->addTab(settingsWidget, tr("Settings"));

   // mpServersWidget = new MpServersWidget();
   // tabWidget->addTab(mpServersWidget, tr("Multi Player Server"));


//    mainOptionsWidget = new MainOptionsWidget(mainObject);
//    tabWidget->addTab(mainOptionsWidget, tr("Main Options"));
//
//
//    propsTreeWidget = new PropsTreeWidget(mainObject);
//    tabWidget->addTab(propsTreeWidget, tr("Property Tree"));

    airportsWidget = new AirportsWidget(mainObject);
    tabWidget->addTab(airportsWidget, tr("Airports"));

   // aircraftWidget = new AircraftWidget();
   // tabWidget->addTab(aircraftWidget, tr("Aircraft"));

    //*********************************************************
    //** Control Bar
    //*********************************************************
    controlBarWidget = new ControlBarWidget(mainObject);
    mainVBox->addWidget(controlBarWidget, 1);
    //controlBarWidget->hide();

    resize(800, 600);
    move(10,10);
    tabWidget->setCurrentIndex(2);
}

LauncherWindow::~LauncherWindow()
{

}
