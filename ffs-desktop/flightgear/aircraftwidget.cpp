#include "aircraftwidget.h"

#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>


AircraftWidget::AircraftWidget(QWidget *parent) :
    QWidget(parent)
{

    QVBoxLayout *mainLayout = new QVBoxLayout();
    setLayout(mainLayout);



    QLabel *headerLabel = new QLabel("Aircraft");
    mainLayout->addWidget(headerLabel);
    
    QHBoxLayout *hBox = new QHBoxLayout();
    mainLayout->addLayout(hBox);
    
    treeWidget = new QTreeWidget();
    hBox->addWidget(treeWidget);

}