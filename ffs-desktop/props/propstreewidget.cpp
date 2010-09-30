#include "propstreewidget.h"

#include <QtCore/QList>

#include <QtGui/QVBoxLayout>
#include <QtGui/QSplitter>
#include <QtGui/QToolBar>
#include <QtGui/QAction>
#include <QtGui/QAbstractItemView>
#include <QtGui/QTreeWidgetItem>
#include <QtGui/QIcon>
#include <QtGui/QFont>


/*



  --TODO--
  Move tree columns numbers to constants

  */

PropsTreeWidget::PropsTreeWidget(MainObject *mOb, QWidget *parent) :
    QWidget(parent)
{

    mainObject = mOb;
    connect(mainObject->telnet, SIGNAL(props_path(QString, QString)),
             this, SLOT(on_props_path(QString, QString))
    );
    connect(mainObject->telnet, SIGNAL(props_node(QString, QString, QString, QString)),
            this, SLOT(on_props_node(QString, QString, QString, QString))
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

    //*****************************
    //** Toolbar
    QToolBar *treeToolbar = new QToolBar();
    treeLayout->addWidget(treeToolbar);
    treeToolbar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    //** Refresh Button
    QAction *actionRefreshTree = new QAction(this);
    treeToolbar->addAction(actionRefreshTree);
    actionRefreshTree->setText("Refresh");
    actionRefreshTree->setIcon(QIcon(":/icons/refresh"));
    connect(actionRefreshTree, SIGNAL(triggered()), this, SLOT(load_nodes()) );

    treeToolbar->addSeparator();

    //*****************************************
    //** Autorefresh
    //****************************************
    timer = new QTimer(this);
    timer->setInterval(1000); //TODO default more

    //** Check Autorefresh enabled
    chkAutoRefresh = new QCheckBox();
    treeToolbar->addWidget(chkAutoRefresh);
    chkAutoRefresh->setText("Autorefresh Enabled");
    chkAutoRefresh->setCheckState(Qt::Unchecked);
    connect(chkAutoRefresh, SIGNAL(toggled(bool)),
            this, SLOT(on_auto_refresh_enabled())
    );

    //** ComboBox sets refresh rate
    comboAutoRefreshRate = new QComboBox();
    treeToolbar->addWidget(comboAutoRefreshRate);
    comboAutoRefreshRate->addItem("1");
    comboAutoRefreshRate->addItem("2");
    comboAutoRefreshRate->addItem("3");
    comboAutoRefreshRate->addItem("4");
    comboAutoRefreshRate->addItem("5");
    connect(comboAutoRefreshRate, SIGNAL(activated(int)),
            this, SLOT(on_set_timer_rate())
    );


    //******************************************************
    //** Tree Widgets
    treeWidget = new QTreeWidget(this);
    treeLayout->addWidget(treeWidget);
    treeWidget->setItemsExpandable(true);
    treeWidget->setAlternatingRowColors(true);
    treeWidget->setRootIsDecorated(true);
    treeWidget->setSortingEnabled(true);
    treeWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    treeWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    treeWidget->setSortingEnabled(true);
    treeWidget->sortByColumn(0, Qt::AscendingOrder);

    QTreeWidgetItem *headerItem = treeWidget->headerItem();
    headerItem->setText(0, tr("Property"));
    headerItem->setText(1, tr("Value"));
    headerItem->setText(2, tr("Type"));
    headerItem->setText(3, tr("Full Path"));
    treeWidget->setColumnWidth(0, 200);

    connect(treeWidget, SIGNAL(itemExpanded(QTreeWidgetItem*)),
             this, SLOT(on_item_expanded(QTreeWidgetItem*))
    );
    connect(treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)),
            this, SLOT(on_item_clicked(QTreeWidgetItem*,int))
    );
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

//************************************************************************
void PropsTreeWidget::load_nodes(){
    //mainObject->telnet->fg_connect();
    mainObject->telnet->get_node("/");
    //qDebug() << reply;
}
//*************************************************************************
//** On props Node
//*************************************************************************
void PropsTreeWidget::on_props_node(QString parent_path, QString node_name,
                                    QString node_value, QString node_type){
    //qDebug() << "YES " << parent_path << "=" << node_value;

    //** Find if actual path end node is already there
    QString end_path = QString(parent_path).append(node_name);
    QList<QTreeWidgetItem *> existing_items = treeWidget->findItems(end_path,
                                                           Qt::MatchExactly | Qt::MatchRecursive,
                                                            3);
    if( existing_items.size() > 0){
        //qDebug() << "NODE EXISTS";
        existing_items[0]->setText(1, node_value); //* UPdate existing node
       return; //* node exists so no need to add
    }
   //QTreeWidgetItem *parent_item;
    //** Otherwise find the parent and add child
    if(parent_path == "/"){
        QTreeWidgetItem *newTopItem = new QTreeWidgetItem();
        newTopItem->setText(3, end_path );
        newTopItem->setText(0, node_name);
        newTopItem->setText(1, node_value);
        newTopItem->setText(2, node_type);
       // newTopItem->setFirstColumnSpanned(true);
        //newTopItem->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
        newTopItem->setIcon(0, QIcon(":/icons/node_val"));
       treeWidget->addTopLevelItem(newTopItem);
    }else{
        QList<QTreeWidgetItem *> items = treeWidget->findItems(parent_path,
                                                           Qt::MatchExactly | Qt::MatchRecursive,
                                                            3);
        QTreeWidgetItem *newNodeItem = new QTreeWidgetItem(items[0]);
        newNodeItem->setText(3, end_path );
        newNodeItem->setText(0, node_name);
        newNodeItem->setText(1, node_value);
        newNodeItem->setText(2, node_type);
       // newNodeItem->setFirstColumnSpanned(true);
        //newNodeItem->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
        newNodeItem->setIcon(0, QIcon(":/icons/node_val"));
        //treeWidget->addTopLevelItem(newTopItem);
       // qDebug( ) << "parent_path=" << "found" << "=" << items.size();
    }
}
//*************************************************************************
//** On props Path
//*************************************************************************
void PropsTreeWidget::on_props_path(QString parent_path, QString path){
    //sqDebug() << "on_props_path >=" << parent_path << "=" << path;

    //** Find if actual path end node is already there
    QString end_path = QString(parent_path).append(path);
    QList<QTreeWidgetItem *> end_items = treeWidget->findItems(end_path,
                                                           Qt::MatchExactly | Qt::MatchRecursive,
                                                            3);
    if( end_items.size() > 0){
       return; //* node exists so no need to add
    }
   //QTreeWidgetItem *parent_item;
    //** Otherwise find the parent and add child
    if(parent_path == "/"){
        QTreeWidgetItem *newTopItem = new QTreeWidgetItem();
        newTopItem->setText(3, end_path );
        newTopItem->setText(0, path.left(path.length() - 1));
        //newTopItem->setText(1, tr("Refresh"));
       // QFont font = newTopItem->font(1);
        //font.setPointSize(7);
        //newTopItem->setFont(1,font);
        //newTopItem->setFirstColumnSpanned(true);
        newTopItem->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
        newTopItem->setIcon(0, QIcon(":/icons/folder_closed"));
        treeWidget->addTopLevelItem(newTopItem);
    }else{
        QList<QTreeWidgetItem *> items = treeWidget->findItems(parent_path,
                                                           Qt::MatchExactly | Qt::MatchRecursive,
                                                            3);
        QTreeWidgetItem *newNodeItem = new QTreeWidgetItem(items[0]);
        newNodeItem->setText(3, end_path );
        newNodeItem->setText(0, path.left(path.length() - 1));
        //newNodeItem->setFirstColumnSpanned(true);
        newNodeItem->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
        newNodeItem->setIcon(0, QIcon(":/icons/folder_closed"));
        //treeWidget->addTopLevelItem(newTopItem);
       // qDebug( ) << "parent_path=" << "found" << "=" << items.size();
    }
    //qDebug( ) << "parent_path=" << parent_path; // << "=" << items.size();
    // qDebug() << "on_props_path <=" << parent_path << "=" << path;
     //qDebug("---");
}

void PropsTreeWidget::on_item_expanded(QTreeWidgetItem *item){
    qDebug() << "ON Expand=" << item->text(3);
   // qDebug() << item->text(3);
    item->setIcon(0, QIcon(":/icons/folder_expanded"));
    item->setText(1, tr("Refresh"));
    QFont font = item->font(1);
    font.setPointSize(7);
    item->setFont(1, font);
    QColor color(0, 0, 170);
    item->setForeground(1, color);
    item->setCheckState(1, Qt::Unchecked);

    mainObject->telnet->get_node(item->text(3));
}

void PropsTreeWidget::on_item_clicked(QTreeWidgetItem *item, int col){
     qDebug("ON on_item_clicked");
    // qDebug() << item->text(3);
     //item->setIcon(0, QIcon(":/icons/folder_expanded"));
    // item->setText(1, tr("Refresh"));
     //mainObject->telnet->get_node(item->text(3));)
    if(item->text(1) == "Refresh"){
        qDebug("REFRESH");
        mainObject->telnet->get_node(item->text(3));
    }
}

//*************************************************************
//* checkbox to start/stop timer in toolbar check button
void PropsTreeWidget::on_auto_refresh_enabled(){
    if( chkAutoRefresh->checkState() ){
        timer->start();
    }else{
        timer->stop();
    }
}
//** Combobox event to set timer rate
void PropsTreeWidget::on_set_timer_rate(){
    int rate = comboAutoRefreshRate->itemText( comboAutoRefreshRate->currentIndex() ).toInt();
    timer->setInterval(rate * 1000);
}
