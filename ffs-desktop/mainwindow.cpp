#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

   //* MainWidget and MainLayout
   QWidget *mainWidget = new QWidget(this);
   setCentralWidget(mainWidget);


    QVBoxLayout *mainVBox = new QVBoxLayout(this);
    mainWidget->setLayout(mainVBox);


    headerLabel = new QLabel(this);
    headerLabel->setText("FG Launcher");
    headerLabel->setStyleSheet("font-size: 20pt; font-weight: bold; background-color: white;");
    mainVBox->addWidget(headerLabel, 20);

    resize(400, 400);
}

MainWindow::~MainWindow()
{

}
