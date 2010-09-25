#ifndef PROPSTREEWIDGET_H
#define PROPSTREEWIDGET_H

#include <QWidget>
#include <QtGui/QTreeWidget>

#include <QtGui/QStatusBar>


class PropsTreeWidget : public QWidget
{
Q_OBJECT
public:
    explicit PropsTreeWidget(QWidget *parent = 0);

    QTreeWidget *treeWidget;

    QStatusBar *statusBarTree;
signals:

public slots:

};

#endif // PROPSTREEWIDGET_H
