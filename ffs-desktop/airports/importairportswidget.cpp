#include "importairportswidget.h"

#include <QtGui/QWidget>
#include <QtGui/QIcon>
#include <QtGui/QVBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QCheckBox>
#include <QtGui/QGroupBox>
//#include <QtGui/>

ImportAirportsWidget::ImportAirportsWidget(MainObject *mainOb, QWidget *parent) :
    QWidget(parent)
{

    mainObject = mainOb;

    setWindowTitle("FlightGear Launcher");
    setWindowIcon(QIcon(":/icons/favicon"));
    //setWindowFlags(  Qt::WindowStaysOnTopHint);

    //* MainWidget and MainLayout
    //QWidget *mainWidget = new QWidget(this);
    //setCentralWidget(mainWidget);


    QVBoxLayout *mainVBox = new QVBoxLayout();
    mainVBox->setContentsMargins(0,0,0,0);
    mainVBox->setSpacing(0);
    this->setLayout(mainVBox);


    QLabel *headerLabel = new QLabel(this);
    headerLabel->setText("Import Airports and Navigation Data");
    headerLabel->setStyleSheet("font-size: 20pt; font-weight: bold; background-color: white;");
    mainVBox->addWidget(headerLabel, 1);

    //QGroupBox *grpOpts = new QGroupBox();
    //mainVBox->addWidget(grpOpts);
    //grpOpts->setTitle(tr("Aiport Import Options"));
   // mainVBox->addWidget(headerLabel, 1);
    QLabel *lblHelp = new QLabel("You are about to import from the flight gear data base into a cache, the less information the better as you require.");
    mainVBox->addWidget(lblHelp, 1);

    QCheckBox *icaoOnly = new QCheckBox();
    icaoOnly->setText("Import ONLY the city major aiports");
 mainVBox->addWidget(icaoOnly, 1);



}
