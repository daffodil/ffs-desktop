#ifndef PROPSTREEWIDGET_H
#define PROPSTREEWIDGET_H

#include "mainobject.h"

#include <QtCore/QTimer>

#include <QtGui/QWidget>
#include <QtGui/QTreeWidget>
#include <QtGui/QTreeWidgetItem>
#include <QtGui/QStatusBar>

#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>

class PropsTreeWidget : public QWidget
{
Q_OBJECT
public:
    explicit PropsTreeWidget(MainObject *mOb, QWidget *parent = 0);

    MainObject *mainObject;

    QTimer *timer;
    QTreeWidget *treeWidget;

    QCheckBox *chkAutoRefresh;
    QComboBox *comboAutoRefreshRate;

    QStatusBar *statusBarTree;
signals:

public slots:
    void load_nodes();
    void on_props_path(QString, QString);
    void on_props_node(QString, QString, QString, QString);
    void on_item_expanded(QTreeWidgetItem *);
    void on_item_clicked(QTreeWidgetItem *, int );

    void on_auto_refresh_enabled();
};

#endif // PROPSTREEWIDGET_H
