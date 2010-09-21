#ifndef AIRCRAFTWIDGET_H
#define AIRCRAFTWIDGET_H

#include <QtGui/QWidget>
#include <QtGui/QTreeWidget>


class AircraftWidget : public QWidget
{
Q_OBJECT
public:
    explicit AircraftWidget(QWidget *parent = 0);

private:
    QTreeWidget *treeWidget;

signals:

public slots:

};

#endif // AIRCRAFTWIDGET_H
