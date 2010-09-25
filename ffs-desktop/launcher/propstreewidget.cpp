#include "propstreewidget.h"

#include <QtGui/QVBoxLayout>
#include <QtGui/QSplitter>
#include <QtGui/QToolBar>
#include <QtGui/QAction>
#include <QtGui/QAbstractItemView>
#include <QtGui/QTreeWidgetItem>
//#include <QtGui/
//#include <QtGui/
//#include <QtGui/


PropsTreeWidget::PropsTreeWidget(QWidget *parent) :
    QWidget(parent)
{

    //* Main Layout
    QVBoxLayout *mainLayout = new QVBoxLayout();
    setLayout(mainLayout);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0,0,0,0);

    QSplitter *splitter = new QSplitter(this);
    mainLayout->addWidget(splitter);

    //***************************************************
    //** Left
    QWidget *leftWidget = new QWidget();
    splitter->addWidget(leftWidget);
    QVBoxLayout *treeLayout = new QVBoxLayout();
    leftWidget->setLayout(treeLayout);
    treeLayout->setContentsMargins(0,0,0,0);
    treeLayout->setSpacing(0);


    //** Toolbar
    QToolBar *treeToolbar = new QToolBar();
    treeLayout->addWidget(treeToolbar);
    treeToolbar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    QAction *actionRefreshTree = new QAction(this);
    treeToolbar->addAction(actionRefreshTree);
    actionRefreshTree->setText("Refresh");
    actionRefreshTree->setIcon(QIcon(":/icons/refresh"));
    connect(actionRefreshTree, SIGNAL(triggered()), this, SLOT(load_airports()) );

    treeToolbar->addSeparator();


    //******************************************************
    treeWidget = new QTreeWidget(this);
    treeLayout->addWidget(treeWidget);
    //treeWidget->setModel(proxyModel);
    treeWidget->setAlternatingRowColors(true);
    treeWidget->setRootIsDecorated(true);
    treeWidget->setSortingEnabled(true);
    treeWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    treeWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    QTreeWidgetItem *headerItem = treeWidget->headerItem();
    headerItem->setText(0,tr("Property"));
    headerItem->setText(1,tr("Value"));

    QTreeWidgetItem *it = new QTreeWidgetItem();
    it->setText(0, "/");
    treeWidget->addTopLevelItem(it);
    treeWidget->setItemExpanded(it, true);
    QTreeWidgetItem *it2 = new QTreeWidgetItem(it);
    it2->setText(0, "foo");
    it2->setText(0, "bar");
    //treeWidget->addTopLevelItem(it);

    statusBarTree = new QStatusBar();
    treeLayout->addWidget(statusBarTree);
    statusBarTree->showMessage("Idle");
}
