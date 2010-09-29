#include "propstreewidget.h"

#include <QtCore/QList>

#include <QtGui/QVBoxLayout>
#include <QtGui/QSplitter>
#include <QtGui/QToolBar>
#include <QtGui/QAction>
#include <QtGui/QAbstractItemView>
#include <QtGui/QTreeWidgetItem>
#include <QtGui/QIcon>
//#include <QtGui/QHeaderView>
//#include <QtGui/

/*



  --TODO--
  Move tree columns numbers to constants

  */

PropsTreeWidget::PropsTreeWidget(MainObject *mOb, QWidget *parent) :
    QWidget(parent)
{

     mainObject = mOb;
     connect(mainObject->telnet, SIGNAL(props_path(QString)),
             this, SLOT(on_props_path(QString))
             );

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
    connect(actionRefreshTree, SIGNAL(triggered()), this, SLOT(load_nodes()) );

    treeToolbar->addSeparator();


    //******************************************************
    treeWidget = new QTreeWidget(this);
    treeLayout->addWidget(treeWidget);
    treeWidget->setItemsExpandable(true);
    treeWidget->setAlternatingRowColors(true);
    treeWidget->setRootIsDecorated(true);
    treeWidget->setSortingEnabled(true);
    treeWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    treeWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    QTreeWidgetItem *headerItem = treeWidget->headerItem();
    headerItem->setText(0, tr("Property"));
    headerItem->setText(1, tr("Value"));
    headerItem->setText(2, tr("Type"));
    treeWidget->setColumnWidth(0, 200);

    connect(treeWidget, SIGNAL(itemExpanded(QTreeWidgetItem*)),
             this, SLOT(on_item_expanded(QTreeWidgetItem*)) );

    //propsRootItem = new QTreeWidgetItem();
    ///propsRootItem->setText(0, "/");
    //treeWidget->addTopLevelItem(it);
    //treeWidget->setItemExpanded(propsRootItem, true);
    //QTreeWidgetItem *it2 = new QTreeWidgetItem(it);
   //it2->setText(0, "foo");
   // it2->setText(0, "bar");
    //treeWidget->addTopLevelItem(it);

    statusBarTree = new QStatusBar();
    treeLayout->addWidget(statusBarTree);
    statusBarTree->showMessage("Idle");
}

void PropsTreeWidget::load_nodes(){
    //mainObject->telnet->fg_connect();
    mainObject->telnet->get_node("/");
    //qDebug() << reply;
}

void PropsTreeWidget::on_props_path(QString path){

    //** Check if node is already there
    QList<QTreeWidgetItem *> items = treeWidget->findItems(path,Qt::MatchExactly, 0);
    if( items.size() > 0){
       return; //* node exists so no need to add
    }
    QTreeWidgetItem *newItem = new QTreeWidgetItem();
    newItem->setText(0, path);
    newItem->setFirstColumnSpanned(true);
    newItem->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
    newItem->setIcon(0, QIcon(":/icons/folder_closed"));
    treeWidget->addTopLevelItem(newItem);
}

void PropsTreeWidget::on_item_expanded(QTreeWidgetItem *item){
    qDebug("ON Expand");
    qDebug() << item->text(0);
    item->setIcon(0, QIcon(":/icons/folder_expanded"));
    mainObject->telnet->get_node(item->text(0));
}
