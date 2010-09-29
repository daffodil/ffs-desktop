#ifndef MAINOPTIONSWIDGET_H
#define MAINOPTIONSWIDGET_H

#include <QtGui/QWidget>
#include <QtGui/QRadioButton>
#include <QtGui/QButtonGroup>

#include "mainobject.h"


class MainOptionsWidget : public QWidget
{
Q_OBJECT
public:
    explicit MainOptionsWidget(MainObject *mOb, QWidget *parent = 0);
    MainObject *mainObject;
    QRadioButton make_radio(QString label);
    QButtonGroup *buttGroupTod;
signals:

public slots:
    void on_send_tod_telnet();
};

#endif // MAINOPTIONSWIDGET_H
