
#include "mpmapwidget.h"

#include <QtGui/QVBoxLayout>
#include <QtGui/QToolBar>
#include <QtGui/QLabel>
#include <QtGui/QComboBox>

MpMapWidget::MpMapWidget(QWidget *parent) :
        QWidget(parent)
{

    setWindowTitle(tr("Multi Player Map"));
    setWindowIcon(QIcon(":/icons/mpmap"));

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);


    //** Toolbar
    QToolBar *toolbar = new QToolBar();
    mainLayout->addWidget(toolbar, 1);

    //** Select server
    QLabel *lblSelectServer = new QLabel("Select Server:");
    toolbar->addWidget(lblSelectServer);
    QComboBox *comboServer = new QComboBox();
    toolbar->addWidget(comboServer);
    comboServer->addItem("MpMap-01", QVariant("http://mpmap01.flightgear.org"));
    comboServer->addItem("MpMap-02", QVariant("http://mpmap02.flightgear.org"));
    connect(comboServer, SIGNAL(currentIndexChanged(QString)), this, SLOT(on_combo_server(int index)));



    //** Browser
    browser = new QWebView(this);
    mainLayout->addWidget(browser, 100);
    connect(browser, SIGNAL(loadStarted()), this, SLOT(start_progress()));
    connect(browser, SIGNAL(loadProgress(int)), this, SLOT(update_progress(int)));
    connect(browser, SIGNAL(loadFinished(bool)), this, SLOT(end_progress(bool)));
    //#browser->setUrl(QUrl("http://mpmap01.flightgear.org"));

    //*** Status Bar
    statusBar = new QStatusBar(this);
    mainLayout->addWidget(statusBar);
    statusBar->showMessage("Idling");

    //** Progress Bar
    progressBar = new QProgressBar();
    progressBar->setVisible(false);
    statusBar->addPermanentWidget(progressBar);

    //*** Initialise
    comboServer->setCurrentIndex(0);
}

//** Progress Slots
void MpMapWidget::start_progress(){
    progressBar->setVisible(true);
}
void MpMapWidget::update_progress(int v){
    progressBar->setValue(v);
}
void MpMapWidget::end_progress(bool Ok){
    progressBar->setVisible(false);
}


void MpMapWidget::on_combo_server(int index){
    //QString url_str = comboServer->
    //#browser->setUrl(QUrl(url_str));
}
