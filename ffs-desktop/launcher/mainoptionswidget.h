#ifndef MAINOPTIONSWIDGET_H
#define MAINOPTIONSWIDGET_H

#include <QtGui/QWidget>
#include <QtGui/QRadioButton>


class MainOptionsWidget : public QWidget
{
Q_OBJECT
public:
    explicit MainOptionsWidget(QWidget *parent = 0);

    QRadioButton make_radio(QString label);

signals:

public slots:

};

#endif // MAINOPTIONSWIDGET_H
