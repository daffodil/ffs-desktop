#ifndef GOOGLEMAPWIDGET_H
#define GOOGLEMAPWIDGET_H

#include <QtCore/QVariant>

//#include <QtGui/QAction>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

#include <QtWebKit/QWebView>

class GoogleMapWidget : public QWidget
{
Q_OBJECT
public:
    explicit GoogleMapWidget(QWidget *parent = 0);

      QWebView *browser;

      QLabel *actLat;
      QLabel *actLng;
signals:

public slots:
      void map_mouse_move(QVariant lat, QVariant lng);
};

#endif // GOOGLEMAPWIDGET_H
