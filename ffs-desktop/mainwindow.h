#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>


#include <QtGui/QVBoxLayout>
#include <QtGui/QLabel>
#include "mapwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QVBoxLayout *mainVBox;
    QLabel *headerLabel;

    MapWidget mapWidget;

};

#endif // MAINWINDOW_H
