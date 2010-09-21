#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include <QWebView>

class MapWidget : public QWidget
{
Q_OBJECT
public:
    explicit MapWidget(QWidget *parent = 0);

private:
    QWebView *browser;
signals:

public slots:

};

#endif // MAPWIDGET_H
