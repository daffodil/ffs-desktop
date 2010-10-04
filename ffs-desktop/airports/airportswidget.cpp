

#include "airportswidget.h"

#include "airports/importairportswidget.h"
#include "airports/aptdatparser.h"
#include "airports/airportsdb.h"

#include <QtCore/QDebug>
#include <QtCore/QString>
//#include <QtCore/QStringList>


// layouts
#include <QtGui/QVBoxLayout>
#include <QtGui/QSplitter>

#include <QtGui/QSizePolicy>
#include <QtGui/QFont>

#include <QtGui/QToolBar>
#include <QtGui/QToolButton>

#include <QtGui/QAction>
#include <QtGui/QLabel>
#include <QtGui/QProgressDialog>
#include <QtGui/QLineEdit>

#include <QtGui/QStandardItemModel>
#include <QtGui/QItemSelection>
#include <QtGui/QItemSelectionModel>
#include <QtGui/QAbstractItemView>
#include <QtGui/QHeaderView>
#include <QtGui/QTreeWidgetItem>

#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

AirportsWidget::AirportsWidget(MainObject *mOb, QWidget *parent) :
    QWidget(parent)
{

    mainObject = mOb;

    airportsDb = new AirportsDb(this);
    connect(airportsDb, SIGNAL(airport(QString,QString,QString,QString)),
            this, SLOT(on_airport(QString,QString,QString,QString))
    );
//    connect(airportsDb, SIGNAL(airports_count(int)),
//            this, SLOT(update_airports_count())
//    );

    //* Main Layout
    QVBoxLayout *mainLayout = new QVBoxLayout();
    setLayout(mainLayout);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0,0,0,0);

    QSplitter *splitter = new QSplitter(this);
    mainLayout->addWidget(splitter);

    //************************************************************************************************
    //** Left
    QWidget *leftWidget = new QWidget();
    splitter->addWidget(leftWidget);
    QVBoxLayout *treeLayout = new QVBoxLayout();
    leftWidget->setLayout(treeLayout);
    treeLayout->setContentsMargins(0,0,0,0);
    treeLayout->setSpacing(0);

    //*************************************************
    //** Toolbar
    QToolBar *treeToolbar = new QToolBar();
    treeLayout->addWidget(treeToolbar);
    treeToolbar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    treeToolbar->layout()->setSpacing(10);

    //** Filter Code
    treeToolbar->addWidget(new QLabel(tr("Filter").append(":")));



    //***********************************s*******************
    //** Filter Buttons
    buttGroupFilter = new QButtonGroup(this);
    buttGroupFilter->setExclusive(true);
    connect(buttGroupFilter, SIGNAL(buttonClicked(QAbstractButton*)),
            this,           SLOT(on_update_filter())
    );
    /*
    QToolButton *buttAll = new QToolButton();
    treeToolbar->addWidget(buttAll);
    buttViewGroup->addButton(buttAll);
    buttAll->setText("All");
    buttAll->setCheckable(true);
    buttAll->setIcon(QIcon(":/icons/pink"));
    buttAll->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    */
    QRadioButton *buttCode = new QRadioButton();
    treeToolbar->addWidget(buttCode);
    buttGroupFilter->addButton(buttCode);
    buttCode->setText("Code");
    buttCode->setProperty("column", QVariant(C_CODE));

    QRadioButton *buttName = new QRadioButton();
    treeToolbar->addWidget(buttName);
    buttGroupFilter->addButton(buttName);
    buttName->setText("Name");
    buttName->setProperty("column", QVariant(C_NAME));
    buttName->setChecked(true);


    //** Find Text
    txtAirportsFilter = new QLineEdit();
    treeToolbar->addWidget(txtAirportsFilter);
    txtAirportsFilter->setFixedWidth(100);
    connect(txtAirportsFilter,    SIGNAL(textChanged(QString)),
            this,           SLOT(on_update_filter())
    );

    treeToolbar->addSeparator();

    //** Add spacer widget to force right
    QWidget *spacerWidget = new QWidget();

    spacerWidget->setSizePolicy( QSizePolicy::Expanding , QSizePolicy::Minimum );
    treeToolbar->addWidget(spacerWidget);

    QAction *actionRefreshTree = new QAction(this);
    treeToolbar->addAction(actionRefreshTree);
    actionRefreshTree->setText("Refresh");
    actionRefreshTree->setIcon(QIcon(":/icons/refresh"));
    connect(actionRefreshTree, SIGNAL(triggered()), this, SLOT(load_airports()) );

    treeToolbar->addSeparator();


    QAction *actionReloadAiportsDb = new QAction(this);
    treeToolbar->addAction(actionReloadAiportsDb);
    actionReloadAiportsDb->setText("Import Aiports");
    actionReloadAiportsDb->setIcon(QIcon(":/icons/import"));
    connect(actionReloadAiportsDb, SIGNAL(triggered()), this, SLOT(import_airports_dialog()) );




    //******************************************************
    //** Models
    model = new QStandardItemModel(this);
    model->setColumnCount(2);
    QStringList headerLabelsList;
    headerLabelsList << "Fav" << "Code"  << "Twr" <<  "Elevation" << "Name";
    model->setHorizontalHeaderLabels(headerLabelsList);

    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    proxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxyModel->setFilterKeyColumn( C_NAME );

    //******************************************************
    //**  Tree
    treeView = new QTreeView(this);
    treeLayout->addWidget(treeView);
    treeView->setModel(proxyModel);

    treeView->setUniformRowHeights(true);
    treeView->setAlternatingRowColors(true);
    treeView->setRootIsDecorated(false);
    treeView->setSortingEnabled(true);
    treeView->sortByColumn(C_NAME, Qt::AscendingOrder);
    treeView->setSelectionMode(QAbstractItemView::SingleSelection);
    treeView->setSelectionBehavior(QAbstractItemView::SelectRows);

    //** Deaders and columns
    treeView->header()->setStretchLastSection(true);
    //treeView->setColumnHidden(C_ELEVATION, true);
    //treeView->setColumnHidden(C_TOWER, true);
    treeView->setColumnWidth(C_FAV, 50);
    treeView->setColumnWidth(C_CODE, 80);
    treeView->setColumnWidth(C_TOWER, 50);
    treeView->setColumnWidth(C_ELEVATION, 80);

    connect( treeView->selectionModel(),
             SIGNAL( selectionChanged (const QItemSelection&, const QItemSelection&) ),
             SLOT( on_aiport_clicked(const QItemSelection&, const QItemSelection&) )
    );

    //connect(treeView,
    //        SIGNAL(clicked(QModelIndex)),
    //        this, SLOT(on_tree_clicked(QModelIndex))
    //);

    statusBarTree = new QStatusBar();
    treeLayout->addWidget(statusBarTree);
    statusBarTree->showMessage("Idle");



    //************************************************************************************************
    //** Right
    QWidget *rightWidget = new QWidget();
    splitter->addWidget(rightWidget);
    QVBoxLayout *airportLayout = new QVBoxLayout();
    rightWidget->setLayout(airportLayout);
    airportLayout->setContentsMargins(0,0,0,0);
    airportLayout->setSpacing(0);


    treeWidgetRunways = new QTreeWidget();
    airportLayout->addWidget(treeWidgetRunways);
    treeWidgetRunways->setAlternatingRowColors(true);
    treeWidgetRunways->setRootIsDecorated(false);
    QTreeWidgetItem *headerItem = treeWidgetRunways->headerItem();
    headerItem->setText(0, tr("Runways"));

    load_airports();

}
//*******************************************************************************
//** Load Airports from database
void AirportsWidget::load_airports(){

    model->removeRows(0, model->rowCount());
    QSqlQuery query;
    bool success;
    success = query.exec("SELECT airport, name, tower, elevation from airports order by airport");
    if(!success){
        qDebug() << "SELECT airports" << query.lastError();
        return;
    }
    //** I want to return a list
    //QList<QString, QString, QString, QString> airports;
    while (query.next()) {
        //emit airport(query.value(0).toString(),
                    // query.value(1).toString(),
                    // query.value(2).toString(),
                    // query.value(3).toString()
                   // );
        int new_row_index = model->rowCount();
        model->insertRow(new_row_index);

        //* create and set items
        QStandardItem *itemFav = new QStandardItem();
        itemFav->setCheckable(true);
        model->setItem(new_row_index, C_FAV, itemFav);

        QStandardItem *itemAirportCode = new QStandardItem();
        itemAirportCode->setText(query.value(0).toString());
        QFont font = itemAirportCode->font();
        font.setFamily("monospace");
        itemAirportCode->setFont(font);
        model->setItem(new_row_index, C_CODE, itemAirportCode);

        QStandardItem *itemAirportName = new QStandardItem();
        itemAirportName->setText(query.value(1).toString());
        model->setItem(new_row_index, C_NAME, itemAirportName);

        QStandardItem *itemAirportTower = new QStandardItem();
        itemAirportTower->setText(query.value(2).toString());
        model->setItem(new_row_index, C_TOWER, itemAirportTower);

        QStandardItem *itemAirportElevation = new QStandardItem();
        itemAirportElevation->setText(query.value(3).toString());
        model->setItem(new_row_index, C_ELEVATION, itemAirportElevation);
    }
    qDebug() << "set row count";
    statusBarTree->showMessage( QString("%1 airports in total").arg(model->rowCount()) );
}

//*****************************************
//*** DEADLoad Airports
void AirportsWidget::on_airport(QString airport,QString name,QString tower,QString elevation){
    //qDebug() <<  airport << name << tower <<  elevation;

    //* insert new row into the model
    int new_row_index = model->rowCount();
    model->insertRow(new_row_index);

    //* create and set items
    QStandardItem *itemFav = new QStandardItem();
    itemFav->setCheckable(true);
    model->setItem(new_row_index, C_FAV, itemFav);

    QStandardItem *itemAirportCode = new QStandardItem();
    itemAirportCode->setText(airport);
    QFont font = itemAirportCode->font();
    font.setFamily("monospace");
    itemAirportCode->setFont(font);
    model->setItem(new_row_index, C_CODE, itemAirportCode);

    QStandardItem *itemAirportName = new QStandardItem();
    itemAirportName->setText(name);
    model->setItem(new_row_index, C_NAME, itemAirportName);

    QStandardItem *itemAirportTower = new QStandardItem();
    itemAirportTower->setText(tower);
    model->setItem(new_row_index, C_TOWER, itemAirportTower);

    QStandardItem *itemAirportElevation = new QStandardItem();
    itemAirportElevation->setText(elevation);
    model->setItem(new_row_index, C_ELEVATION, itemAirportElevation);

}
//void AirportsWidget::update_airports_count(){
   // QString status_lbl = QString("%1 aiports").arg( model->rowCount() );
    //statusBarTree->showMessage(status_lbl);
//}

//**********************************************
//*** Update Filter
void AirportsWidget::on_update_filter(){
   // qDebug() << txtAirportsFilter->text();

    int column = buttGroupFilter->checkedButton()->property("column").toInt();
    proxyModel->setFilterKeyColumn( column );
    proxyModel->setFilterFixedString( txtAirportsFilter->text() );
    //qDebug() << column;
    //return;
    //proxyModel->setFilterKeyColumn( column );
    treeView->sortByColumn(column);
    //if( !txtAirportsFilter->hasFocus() ){ // WTF?
       // txtAirportsFilter->setFocus();
    //}
}

//**********************************************
//*** Import Airports Dialog
void AirportsWidget::import_airports_dialog(){
    //* TODO message you are about to do this and take a few moment etc (or background)
     qDebug("AirportsWidget::load_airports_DB()");
    //QProgressDialog progress("Importing airports", "Abort Copy", 0, 2000, this);
    //progress.show();
     ImportAirportsWidget *imp = new ImportAirportsWidget(mainObject);
     if(imp->exec()){
        load_airports();
     }
}



//**********************************************
//*** Airport Row Clicked = Show Runways
void AirportsWidget::on_aiport_clicked(const QItemSelection&, const QItemSelection&){
    qDebug() << "CLICK";

    //model->removeRows(0, model->rowCount());
    treeWidgetRunways->model()->removeRows(0,
                                            treeWidgetRunways->model()->rowCount()
                                            );

    QModelIndex proxyIndex =  treeView->selectionModel()->selectedRows(C_CODE).first();
    if(!proxyIndex.isValid()){
        return;
    }
   // qDebug() << "proxy=" << proxyIndex;
    QModelIndex srcIndex = proxyModel->mapToSource(proxyIndex);
    QString airport_code = model->item(srcIndex.row(), C_CODE)->text();

    QSqlQuery query;
    query.prepare("SELECT * from runways where airport=? order by runways");
    query.addBindValue( airport_code );
    bool success = query.exec();
    if(!success){
        qDebug() << "SELECT runways" << airport_code << "==" << query.lastError();
        return;
    }

    qDebug() << query.size() << " " << airport_code;
    //sif(query.is)
    while (query.next()) {
        QTreeWidgetItem *itemRun = new QTreeWidgetItem();
        itemRun->setText( 0, query.value(0).toString() );
        treeWidgetRunways->addTopLevelItem(itemRun);
    }
}
