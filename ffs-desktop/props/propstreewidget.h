#ifndef PROPSTREEWIDGET_H
#define PROPSTREEWIDGET_H

#include <QWidget>
#include <QtGui/QTreeWidget>

#include <QtGui/QStatusBar>

#include "mainobject.h"

class PropsTreeWidget : public QWidget
{
Q_OBJECT
public:
    explicit PropsTreeWidget(MainObject *mOb, QWidget *parent = 0);

    MainObject *mainObject;

    QTreeWidget *treeWidget;

    QStatusBar *statusBarTree;
signals:

public slots:
    void load_nodes();
};

#endif // PROPSTREEWIDGET_H
