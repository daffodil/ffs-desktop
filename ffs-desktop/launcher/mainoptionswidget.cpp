#include "mainoptionswidget.h"


#include <QtCore/QString>

#include <QtGui/QGroupBox>
#include <QtGui/QRadioButton>
#include <QtGui/QButtonGroup>
#include <QtGui/QVBoxLayout>

MainOptionsWidget::MainOptionsWidget(QWidget *parent) :
    QWidget(parent)
{

    //* Main Layout
    QVBoxLayout *mainLayout = new QVBoxLayout();
    setLayout(mainLayout);
    mainLayout->setSpacing(0);

    mainLayout->setContentsMargins(0,0,0,0);

    //***********************************************************************
    //** Time Of Day
    QGroupBox *grpTimeOfDay = new QGroupBox();
    mainLayout->addWidget(grpTimeOfDay);

    grpTimeOfDay->setTitle(tr("Time Of Day"));
    grpTimeOfDay->setCheckable(true);
    QString styleX = QString("QGroupBox{  border:2px solid gray;border-radius:5px;  margin-top: 1ex;} QGroupBox::title{subcontrol-origin: margin;subcontrol-position:top center;padding:0 3px;}");
    grpTimeOfDay->setStyleSheet(styleX);

    QVBoxLayout *layoutTod = new QVBoxLayout();
    grpTimeOfDay->setLayout(layoutTod);
    layoutTod->setSpacing(0);
    layoutTod->setContentsMargins(0,0,0,0);

    QRadioButton *buttonTodMidnight = new QRadioButton("Midnight");
    layoutTod->addWidget(buttonTodMidnight);

    QRadioButton *buttonTodDawn = new QRadioButton("Dawn");
    layoutTod->addWidget(buttonTodDawn);

    QRadioButton *buttonTodNoon = new QRadioButton("Noon");
    layoutTod->addWidget(buttonTodNoon);

    QRadioButton *buttonTodDusk = new QRadioButton("Dusk");
    layoutTod->addWidget(buttonTodDusk);

    layoutTod->addStretch(20);
   // layoutTod->addWidget(make_radio("Dawn"));
//    layoutTod->addWidget(make_radio("Noon"));
//    layoutTod->addWidget(make_radio("Dusk"));
    //layoutTod->addWidget(make_radio("Dawn"));

    //QWidget *aeroPanelWidget = new QWidget();
    //aeroLayout->addWidget(aeroPanelWidget);
    //aeroPanelWidget->setStyleSheet("border: 1px solid red; background-color: black;");

    //QVBoxLayout *aeroPanelLayout = new QVBoxLayout();
   // grpAeroPanel->setLayout(aeroPanelLayout);
}

QRadioButton MainOptionsWidget::make_radio(QString label){
    //return new QRadioButton(label);
   // return button;
}
