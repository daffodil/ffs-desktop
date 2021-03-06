#include "launcher/launcherwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    setWindowTitle("FlightGear Launcher");
    setWindowIcon(QIcon(":/icons/favicon"));


    trayIcon = new QSystemTrayIcon(QIcon(":/icons/favicon"), this);
    trayIcon->setToolTip("FlightGear Launcher");
    trayIcon->setVisible(true);

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

    aircraftWidget = new AircraftWidget();
    tabWidget->addTab(aircraftWidget, "Aircraft");

    resize(700, 600);
}

MainWindow::~MainWindow()
{

}
