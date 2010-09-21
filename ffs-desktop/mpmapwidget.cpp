
#include "mpmapwidget.h"

#include <QtGui/QVBoxLayout>
#include <QtGui/QToolBar>
#include <QtGui/QLabel>
#include <QtGui/QComboBox>

MpMapWidget::MpMapWidget(QWidget *parent) :
        QWidget(parent)
{

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    //** Toolbar
    QToolBar *toolbar = new QToolBar();
    mainLayout->addWidget(toolbar, 1);

    //** Select server
    QLabel *lblSelectServer = new QLabel("Select Server:");
    toolbar->addWidget(lblSelectServer);
    QComboBox *comboServer = new QComboBox();
    toolbar->addWidget(comboServer);
    comboServer->addItem("http://mpmap01.flightgear.org");
    comboServer->addItem("http://mpmap02.flightgear.org");
    connect(comboServer, SIGNAL(currentIndexChanged(QString)), this, SLOT(on_combo_server(QString)));
           // void	activated ( const QString & text )

    progressBar = new QProgressBar();
    toolbar->addWidget(progressBar);
    progressBar->setVisible(false);

    //** Browser
    browser = new QWebView(this);
    mainLayout->addWidget(browser, 100);
    connect(browser, SIGNAL(loadStarted()), this, SLOT(start_progress()));
    connect(browser, SIGNAL(loadProgress(int)), this, SLOT(update_progress(int)));
    connect(browser, SIGNAL(loadFinished(bool)), this, SLOT(end_progress(bool)));
    //#browser->setUrl(QUrl("http://mpmap01.flightgear.org"));

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


void MpMapWidget::on_combo_server(QString url_str){
    browser->setUrl(QUrl(url_str));
}
