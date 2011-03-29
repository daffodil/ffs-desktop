


#include <QtCore/QString>

#include <QtGui/QAbstractButton>
#include <QtGui/QButtonGroup>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLineEdit>
#include <QtGui/QToolButton>
#include <QtGui/QPushButton>
#include <QtGui/QLabel>
#include <QtGui/QMenu>

#include <QIntValidator>

#include "mainoptionswidget.h"


MainOptionsWidget::MainOptionsWidget(MainObject *mOb, QWidget *parent) :
    QWidget(parent)
{
    mainObject = mOb;

    //* Main Layout
    QVBoxLayout *mainLayout = new QVBoxLayout();
    setLayout(mainLayout);
    mainLayout->setSpacing(0);

    mainLayout->setContentsMargins(0,0,0,0);

	QString styleX(""); //QGroupBox{  border:2px solid gray;border-radius:5px;  margin-top: 1ex;} QGroupBox::title{subcontrol-origin: margin;subcontrol-position:top center;padding:0 3px;}");

	//===============================================================
    //** Season
	grpSeason = new QGroupBox();
    mainLayout->addWidget(grpSeason);
	connect(grpSeason, SIGNAL(clicked()), this, SLOT(set_season()));

    grpSeason->setTitle(tr("Season"));
    grpSeason->setCheckable(true);
	grpSeason->setChecked(false);
    grpSeason->setStyleSheet(styleX);

    QVBoxLayout *layoutSeason = new QVBoxLayout();
    grpSeason->setLayout(layoutSeason);
    layoutSeason->setSpacing(0);
    layoutSeason->setContentsMargins(0,0,0,0);

	buttonSeasonSummer = new QRadioButton(tr("Summer"));
    layoutSeason->addWidget(buttonSeasonSummer);
    buttonSeasonSummer->setChecked(true);
	connect(buttonSeasonSummer, SIGNAL(clicked(bool)), this, SLOT(set_season()));

	buttonSeasonWinter = new QRadioButton(tr("Winter"));
    layoutSeason->addWidget(buttonSeasonWinter);
	connect(buttonSeasonWinter, SIGNAL(clicked(bool)), this, SLOT(set_season()));

   //===============================================================
    //** Time Of Day
	grpTimeOfDay = new QGroupBox();
    mainLayout->addWidget(grpTimeOfDay);
	grpTimeOfDay->setTitle(tr("Time Of Day"));
	grpTimeOfDay->setCheckable(true);
	grpTimeOfDay->setChecked(false);
	grpTimeOfDay->setStyleSheet(styleX);
	connect(grpTimeOfDay, SIGNAL(clicked()), this, SLOT(set_time_of_day()));


    QVBoxLayout *layoutTod = new QVBoxLayout();
    grpTimeOfDay->setLayout(layoutTod);
    layoutTod->setSpacing(0);
    layoutTod->setContentsMargins(0,0,0,0);

	buttonGroupTimeOfDay = new QButtonGroup(this);
	buttonGroupTimeOfDay->setExclusive(true);
	connect(buttonGroupTimeOfDay, SIGNAL(buttonClicked(QAbstractButton *)), this, SLOT(set_time_of_day()));

	QRadioButton *buttonTodRealTime = new QRadioButton(tr("Real Time"));
	buttonTodRealTime->setProperty("value", QVariant("realtime"));
	layoutTod->addWidget(buttonTodRealTime);
	buttonGroupTimeOfDay->addButton(buttonTodRealTime);


	QRadioButton *buttonTodDawn = new QRadioButton(tr("Dawn"));
	buttonTodDawn->setProperty("value", QVariant("dawn"));
    layoutTod->addWidget(buttonTodDawn);
	buttonGroupTimeOfDay->addButton(buttonTodDawn);

	QRadioButton *buttonTodMorning = new QRadioButton(tr("Morning"));
	buttonTodMorning->setProperty("value", QVariant("morning"));
	layoutTod->addWidget(buttonTodMorning);
	buttonGroupTimeOfDay->addButton(buttonTodMorning);


	QRadioButton *buttonTodNoon = new QRadioButton(tr("Noon"));
	buttonTodNoon->setProperty("value", QVariant("noon"));
    layoutTod->addWidget(buttonTodNoon);
	buttonGroupTimeOfDay->addButton(buttonTodNoon);
    buttonTodNoon->setChecked(true);

	QRadioButton *buttonTodAfternoon = new QRadioButton(tr("Afternoon"));
	buttonTodAfternoon->setProperty("value", QVariant("afternoon"));
	layoutTod->addWidget(buttonTodAfternoon);
	buttonGroupTimeOfDay->addButton(buttonTodAfternoon);

	QRadioButton *buttonTodDusk = new QRadioButton(tr("Dusk"));
	buttonTodDusk->setProperty("value", QVariant("dusk"));
    layoutTod->addWidget(buttonTodDusk);
	buttonGroupTimeOfDay->addButton(buttonTodDusk);

	QRadioButton *buttonTodEvening = new QRadioButton(tr("Evening"));
	buttonTodEvening->setProperty("value", QVariant("evening"));
	layoutTod->addWidget(buttonTodEvening);
	buttonGroupTimeOfDay->addButton(buttonTodEvening);

	QRadioButton *buttonTodMidnight = new QRadioButton(tr("Midnight"));
	buttonTodMidnight->setProperty("value", QVariant("midnight"));
	layoutTod->addWidget(buttonTodMidnight);
	buttonGroupTimeOfDay->addButton(buttonTodMidnight);

	/*
    QPushButton *buttSendTodTelnet = new QPushButton();
    layoutTod->addWidget(buttSendTodTelnet);
    buttSendTodTelnet->setText(tr("Send"));
    buttSendTodTelnet->setIcon(QIcon(":/icons/send"));
    connect(buttSendTodTelnet, SIGNAL(clicked()),
            this, SLOT(on_send_tod_telnet()));
	*/

    //QWidget *aeroPanelWidget = new QWidget();
    //aeroLayout->addWidget(aeroPanelWidget);
    //aeroPanelWidget->setStyleSheet("border: 1px solid red; background-color: black;");

    //QVBoxLayout *aeroPanelLayout = new QVBoxLayout();
   // grpAeroPanel->setLayout(aeroPanelLayout);

    //***********************************************************************
    //** Network
    QGroupBox *grpNetworkContainer = new QGroupBox();
    mainLayout->addWidget(grpNetworkContainer);

    grpNetworkContainer->setTitle(tr("Network"));
    //grpNetworkContainer->setCheckable(true);
    grpNetworkContainer->setStyleSheet(styleX);

    QVBoxLayout *layoutNetContainer = new QVBoxLayout();
    grpNetworkContainer->setLayout(layoutNetContainer);
    layoutNetContainer->setSpacing(20);
    int mc =20;
    layoutNetContainer->setContentsMargins(mc,mc,mc,mc);

	//==========================================================
    //** HTTP
	grpHttp = new QGroupBox();
	grpHttp->setTitle(tr("HTTP Web Server"));
	grpHttp->setCheckable(true);
	grpHttp->setChecked(false);
	grpHttp->setStyleSheet(styleX);
	layoutNetContainer->addWidget(grpHttp);
	connect(grpHttp, SIGNAL(clicked(bool)), this, SLOT(set_http()));

    QHBoxLayout *layoutNetHttp = new QHBoxLayout();
	grpHttp->setLayout(layoutNetHttp);
    layoutNetHttp->setSpacing(10);
    int m = 5;
    layoutNetHttp->setContentsMargins(m,m,m,m);

    QLabel *lblHttp = new QLabel();
    lblHttp->setText(tr("Set Port No:"));
    layoutNetHttp->addWidget( lblHttp);

	txtHttp = new QLineEdit("5500");
	txtHttp->setValidator(new QIntValidator(80, 32000, this));
    layoutNetHttp->addWidget(txtHttp);
	connect(txtHttp, SIGNAL(textChanged(QString)), this, SLOT(set_http()));

    QToolButton *butHttp = new QToolButton();
    layoutNetHttp->addWidget(butHttp);
    butHttp->setIcon(QIcon(":/icons/dns_lookup"));
	butHttp->setToolButtonStyle(Qt::ToolButtonIconOnly);
    butHttp->setPopupMode(QToolButton::InstantPopup);

    QMenu *menuNetHttp = new QMenu();
    butHttp->setMenu(menuNetHttp);

    QAction *actHttpBrowse = new QAction(menuNetHttp);
    menuNetHttp->addAction(actHttpBrowse);
    actHttpBrowse->setText(tr("Open in external browser"));
    //connect(actExePath, SIGNAL(triggered()), this, SLOT(on_exe_path()));


	//===========================================================
    //** Telnet
	grpTelnet = new QGroupBox();
	grpTelnet->setTitle(tr("Telnet Properties Server"));
	grpTelnet->setCheckable(true);
	grpTelnet->setChecked(false);
	grpTelnet->setStyleSheet(styleX);
	layoutNetContainer->addWidget(grpTelnet);
	connect(grpTelnet, SIGNAL(clicked()), this, SLOT(set_telnet()));

    QHBoxLayout *layoutNetTelnet = new QHBoxLayout();
	grpTelnet->setLayout(layoutNetTelnet);
    layoutNetTelnet->setSpacing(10);
    //int m = 5;
    layoutNetTelnet->setContentsMargins(m,m,m,m);

    QLabel *lblTelnet = new QLabel();
    lblTelnet->setText(tr("Set Port No:"));
    layoutNetTelnet->addWidget( lblTelnet);

	txtTelnet = new QLineEdit("5500");
	txtTelnet->setValidator(new QIntValidator(80, 32000, this));
    layoutNetTelnet->addWidget(txtTelnet);
	connect(txtTelnet, SIGNAL(textChanged(QString)), this, SLOT(set_telnet()));



	//===========================================================
	//** Weather
	QGroupBox *grpWeatherFetch = new QGroupBox();
	grpWeatherFetch->setTitle(tr("Telnet Properties Server"));
	grpWeatherFetch->setCheckable(true);
	grpWeatherFetch->setChecked(false);
	grpWeatherFetch->setStyleSheet(styleX);
	layoutNetContainer->addWidget(grpWeatherFetch);
	//#connect(grpTelnet, SIGNAL(clicked()), this, SLOT(set_telnet()));

	QHBoxLayout *layoutEnviroment = new QHBoxLayout();
	grpTelnet->setLayout(layoutEnviroment);
	layoutEnviroment->setSpacing(10);
	//int m = 5;
	layoutEnviroment->setContentsMargins(m,m,m,m);

	/*
	QLabel *lblTelnet = new QLabel();
	lblTelnet->setText(tr("Set Port No:"));
	layoutEnviroment->addWidget( lblTelnet);
	*/

}


//=================================================
//** Set Season
void MainOptionsWidget::set_season(){
	if( grpSeason->isChecked() ){
		emit set_arg("set", "--season=", buttonSeasonSummer->isChecked() ? "summer" : "winter");
	}else{
		emit set_arg("remove", "--season=", "");
	}
}

//=================================================
//** Set Time Of Day
void MainOptionsWidget::set_time_of_day(){
	if( grpTimeOfDay->isChecked() ){
		emit set_arg("set", "--timeofday=", buttonGroupTimeOfDay->checkedButton()->property("value").toString());
	}else{
		emit set_arg("remove", "--timeofday=", "");
	}
}


//=================================================
//** Set Http
void MainOptionsWidget::set_http(){
	qDebug() << "set_http";
	if( grpHttp->isChecked() ){
		emit set_arg("set", "--http=", txtHttp->text());
	}else{
		emit set_arg("remove", "--http=", "");
	}
}


//=================================================
//** Set Telnet
void MainOptionsWidget::set_telnet(){
	qDebug() << "telnet";
	if( grpTelnet->isChecked() ){
		emit set_arg("set", "--telnet=", txtTelnet->text());
	}else{
		emit set_arg("remove", "--telnet=", "");
	}
}
