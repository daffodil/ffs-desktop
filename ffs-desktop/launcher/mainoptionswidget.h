#ifndef MAINOPTIONSWIDGET_H
#define MAINOPTIONSWIDGET_H

#include <QtGui/QWidget>
#include <QtGui/QRadioButton>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QLineEdit>

#include "mainobject.h"


class MainOptionsWidget : public QWidget
{
Q_OBJECT
public:
    explicit MainOptionsWidget(MainObject *mOb, QWidget *parent = 0);
    MainObject *mainObject;


    QRadioButton make_radio(QString label);



	QGroupBox *grpSeason;
	QRadioButton *buttonSeasonSummer;
	QRadioButton *buttonSeasonWinter;

	QGroupBox *grpTimeOfDay;
	QButtonGroup *buttonGroupTimeOfDay;


signals:
	void set_arg(QString action, QString arg, QString value);


public slots:

	void set_season();
	void set_time_of_day();


};

#endif // MAINOPTIONSWIDGET_H
