#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

   //* MainWidget and MainLayout
   QWidget *mainWidget = new QWidget(this);
   setCentralWidget(mainWidget);


    QVBoxLayout *mainVBox = new QVBoxLayout(this);
    mainVBox->setContentsMargins(0,0,0,0);
    mainVBox->setSpacing(0);
    mainWidget->setLayout(mainVBox);


    headerLabel = new QLabel(this);
    headerLabel->setText("FG Launcher");
    headerLabel->setStyleSheet("font-size: 20pt; font-weight: bold; background-color: white;");
    mainVBox->addWidget(headerLabel, 1);

    tabWidget = new QTabWidget(this);
    mainVBox->addWidget(tabWidget,100);

    mpMapWidget = new MpMapWidget(this);
    tabWidget->addTab(mpMapWidget,QString("FOO"));



    resize(400, 400);
}

MainWindow::~MainWindow()
{

}
