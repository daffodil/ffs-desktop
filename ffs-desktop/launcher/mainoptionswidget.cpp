#include "mainoptionswidget.h"


#include <QtCore/QString>

#include <QtGui/QGroupBox>
#include <QtGui/QRadioButton>
#include <QtGui/QButtonGroup>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLineEdit>
#include <QtGui/QToolButton>
#include <QtGui/QPushButton>
#include <QtGui/QLabel>
#include <QtGui/QMenu>

MainOptionsWidget::MainOptionsWidget(MainObject *mOb, QWidget *parent) :
    QWidget(parent)
{
    mainObject = mOb;

    //* Main Layout
    QVBoxLayout *mainLayout = new QVBoxLayout();
    setLayout(mainLayout);
    mainLayout->setSpacing(0);

    mainLayout->setContentsMargins(0,0,0,0);

    QString styleX = QString("QGroupBox{  border:2px solid gray;border-radius:5px;  margin-top: 1ex;} QGroupBox::title{subcontrol-origin: margin;subcontrol-position:top center;padding:0 3px;}");

    //***********************************************************************
    //** Season
    QGroupBox *grpSeason = new QGroupBox();
    mainLayout->addWidget(grpSeason);

    grpSeason->setTitle(tr("Season"));
    grpSeason->setCheckable(true);
    grpSeason->setStyleSheet(styleX);

    QVBoxLayout *layoutSeason = new QVBoxLayout();
    grpSeason->setLayout(layoutSeason);
    layoutSeason->setSpacing(0);
    layoutSeason->setContentsMargins(0,0,0,0);

    QRadioButton *buttonSeasonSummer = new QRadioButton(tr("Summer"));
    layoutSeason->addWidget(buttonSeasonSummer);
    buttonSeasonSummer->setChecked(true);

    QRadioButton *buttonSeasonWinter = new QRadioButton(tr("Winter"));
    layoutSeason->addWidget(buttonSeasonWinter);

    //***********************************************************************
    //** Time Of Day
    QGroupBox *grpTimeOfDay = new QGroupBox();
    mainLayout->addWidget(grpTimeOfDay);

    grpTimeOfDay->setTitle(tr("Time Of Day"));
    grpTimeOfDay->setCheckable(true);
    grpTimeOfDay->setStyleSheet(styleX);

    QVBoxLayout *layoutTod = new QVBoxLayout();
    grpTimeOfDay->setLayout(layoutTod);
    layoutTod->setSpacing(0);
    layoutTod->setContentsMargins(0,0,0,0);

    buttGroupTod = new QButtonGroup(this);
    buttGroupTod->setExclusive(true);

    QRadioButton *buttonTodMidnight = new QRadioButton("Midnight");
    layoutTod->addWidget(buttonTodMidnight);

    QRadioButton *buttonTodDawn = new QRadioButton("Dawn");
    layoutTod->addWidget(buttonTodDawn);

    QRadioButton *buttonTodNoon = new QRadioButton("Noon");
    layoutTod->addWidget(buttonTodNoon);
    buttonTodNoon->setChecked(true);

    QRadioButton *buttonTodDusk = new QRadioButton("Dusk");
    layoutTod->addWidget(buttonTodDusk);

    QPushButton *buttSendTodTelnet = new QPushButton();
    layoutTod->addWidget(buttSendTodTelnet);
    buttSendTodTelnet->setText(tr("Send"));
    buttSendTodTelnet->setIcon(QIcon(":/icons/send"));
    connect(buttSendTodTelnet, SIGNAL(clicked()),
            this, SLOT(on_send_tod_telnet()));

    //layoutTod->addStretch(20);
   // layoutTod->addWidget(make_radio("Dawn"));
//    layoutTod->addWidget(make_radio("Noon"));
//    layoutTod->addWidget(make_radio("Dusk"));
    //layoutTod->addWidget(make_radio("Dawn"));

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

    //** HTTP
    QGroupBox *grpNetHttp = new QGroupBox();
    layoutNetContainer->addWidget(grpNetHttp);

    grpNetHttp->setTitle(tr("HTTP Web Server"));
    grpNetHttp->setCheckable(true);
    grpNetHttp->setStyleSheet(styleX);

    QHBoxLayout *layoutNetHttp = new QHBoxLayout();
    grpNetHttp->setLayout(layoutNetHttp);
    layoutNetHttp->setSpacing(10);
    int m = 5;
    layoutNetHttp->setContentsMargins(m,m,m,m);

    QLabel *lblHttp = new QLabel();
    lblHttp->setText(tr("Set Port No:"));
    layoutNetHttp->addWidget( lblHttp);
    QLineEdit *txtHttp = new QLineEdit("5500");
    layoutNetHttp->addWidget(txtHttp);

    QToolButton *butHttp = new QToolButton();
    layoutNetHttp->addWidget(butHttp);
    butHttp->setText(tr("Open"));
    butHttp->setIcon(QIcon(":/icons/dns_lookup"));
    butHttp->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    butHttp->setPopupMode(QToolButton::InstantPopup);

    QMenu *menuNetHttp = new QMenu();
    butHttp->setMenu(menuNetHttp);

    QAction *actHttpBrowse = new QAction(menuNetHttp);
    menuNetHttp->addAction(actHttpBrowse);
    actHttpBrowse->setText(tr("Open in external browser"));
    //connect(actExePath, SIGNAL(triggered()), this, SLOT(on_exe_path()));

    QAction *actHttpBrowseTab = new QAction(menuNetHttp);
    menuNetHttp->addAction(actHttpBrowseTab);
    actHttpBrowseTab->setText(tr("Open in new Tab"));
    //connect(actExeAutodetect, SIGNAL(triggered()), this, SLOT(on_exe_autodetect()));

    //** Telnet
    QGroupBox *grpNetTelnet = new QGroupBox();
    layoutNetContainer->addWidget(grpNetTelnet);

    grpNetTelnet->setTitle(tr("Telnet Properties Server"));
    grpNetTelnet->setCheckable(true);
    grpNetTelnet->setStyleSheet(styleX);

    QHBoxLayout *layoutNetTelnet = new QHBoxLayout();
    grpNetTelnet->setLayout(layoutNetTelnet);
    layoutNetTelnet->setSpacing(10);
    //int m = 5;
    layoutNetTelnet->setContentsMargins(m,m,m,m);

    QLabel *lblTelnet = new QLabel();
    lblTelnet->setText(tr("Set Port No:"));
    layoutNetTelnet->addWidget( lblTelnet);
    QLineEdit *txtTelnet = new QLineEdit("5500");
    layoutNetTelnet->addWidget(txtTelnet);

    QToolButton *buttTelnet = new QToolButton();
    layoutNetTelnet->addWidget(buttTelnet);
    buttTelnet->setText(tr("Open"));
    buttTelnet->setIcon(QIcon(":/icons/dns_lookup"));
    buttTelnet->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    buttTelnet->setPopupMode(QToolButton::InstantPopup);

    QMenu *menuNetTelnet = new QMenu();
    buttTelnet->setMenu(menuNetTelnet);

    QAction *actTelnetBrowse = new QAction(menuNetTelnet);
    menuNetTelnet->addAction(actTelnetBrowse);
    actTelnetBrowse->setText(tr("Open in eerminal"));
    //connect(actExePath, SIGNAL(triggered()), this, SLOT(on_exe_path()));

    //QAction *actHttpBrowseTab = new QAction(menuNetHttp);
    //menuNetHttp->addAction(actHttpBrowseTab);
    //actHttpBrowseTab->setText(tr("Open in new Tab"));
    //connect(actExeAutodetect, SIGNAL(triggered()), this, SLOT(on_exe_autodetect()));

}

QRadioButton MainOptionsWidget::make_radio(QString label){
    //return new QRadioButton(label);
   // return button;
}

void MainOptionsWidget::on_send_tod_telnet(){
    QAbstractButton *curr = buttGroupTod->checkedButton();
    //mainObject->telnet->set_node();

}
