#ifndef MPMAPWIDGET_H
#define MPMAPWIDGET_H

#include <QWidget>
#include <QWebView>

class MpMapWidget : public QWidget
{
Q_OBJECT
public:
    explicit MpMapWidget(QWidget *parent = 0);

private:
    QWebView *browser;
signals:

public slots:

};

#endif // MPMAPWIDGET_H
