#include "mpmapwidget.h"
#include <QtGui/QVBoxLayout>

MpMapWidget::MpMapWidget(QWidget *parent) :
        QWidget(parent)
{

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    browser = new QWebView(this);

    mainLayout->addWidget(browser);
    browser->setUrl(QUrl("http://mpmap01.flightgear.org"));


}

