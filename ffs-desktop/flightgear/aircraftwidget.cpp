
/**
  This widget displays a list of aircraft,
    does a background call to a process that executes FG
  */

#include "aircraftwidget.h"

// layouts
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>

#include <QtGui/QLabel>

#include <QtGui/QToolBar>

//* tree
#include <QtGui/QHeaderView>
#include <QtGui/QTreeWidgetItem>
#include <QtGui/QAction>
/*


*/

AircraftWidget::AircraftWidget(QWidget *parent) :
    QWidget(parent)
{

    QVBoxLayout *mainLayout = new QVBoxLayout();
    setLayout(mainLayout);

    //** Top Toolbar
    QToolBar *topToolBar = new QToolBar();
    mainLayout->addWidget(topToolBar);


    QLabel *headerLabel = new QLabel(tr("Aircraft"));
    mainLayout->addWidget(headerLabel);
    
    QHBoxLayout *hBox = new QHBoxLayout();
    mainLayout->addLayout(hBox);
    
    //**********************************************************************
    //* Aircraft Tree View
    // TOSO make nested on xml files, for now its a straight list
    treeWidget = new QTreeWidget();
    hBox->addWidget(treeWidget);

    //** get handle on TreeHeader item and set the labels
    QTreeWidgetItem *headerItem = treeWidget->headerItem();
    headerItem->setText(0, tr("Shell"));
    headerItem->setText(1, tr("Description"));

    //* Get a handle on the header and stretch the last section
    QHeaderView *treeHeader = treeWidget->header();
    treeHeader->setStretchLastSection(true);






}
