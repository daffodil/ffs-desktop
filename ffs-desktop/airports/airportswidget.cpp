

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

#include <QtGui/QToolBar>
#include <QtGui/QToolButton>
//#include <QtGui/QAbstractButton>
#include <QtGui/QButtonGroup>

#include <QtGui/QAction>
#include <QtGui/QLabel>
#include <QtGui/QProgressDialog>
//#include <QtGui/QTabWidget>

#include <QtGui/QStandardItemModel>
#include <QtGui/QItemSelection>
#include <QtGui/QItemSelectionModel>
#include <QtGui/QAbstractItemView>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>

AirportsWidget::AirportsWidget(MainObject *mOb, QWidget *parent) :
    QWidget(parent)
{

    mainObject = mOb;

    airportsDb = new AirportsDb(this);
    connect(airportsDb, SIGNAL(airport(QString,QString,QString,QString)),
            this, SLOT(on_airport(QString,QString,QString,QString))
    );

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

    //** Filter Code
    treeToolbar->addWidget(new QLabel(tr("In").append(":")));



    //******************************************************
    //** Filter Buttons
    QButtonGroup *buttViewGroup = new QButtonGroup(this);
    buttViewGroup->setExclusive(true);
//    connect(buttViewGroup, SIGNAL(buttonClicked(QAbstractButton*)),
//            this, SLOT(on_view_button_clicked(QAbstractButton*))
//    );

    QToolButton *buttAll = new QToolButton();
    treeToolbar->addWidget(buttAll);
    buttViewGroup->addButton(buttAll);
    buttAll->setText("All");
    buttAll->setCheckable(true);
    buttAll->setIcon(QIcon(":/icons/pink"));
    buttAll->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    QToolButton *buttCode = new QToolButton();
    treeToolbar->addWidget(buttCode);
    buttViewGroup->addButton(buttCode);
    buttCode->setText("Code");
    buttCode->setCheckable(true);
    buttCode->setIcon(QIcon(":/icons/purple"));
    buttCode->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    QToolButton *buttName = new QToolButton();
    treeToolbar->addWidget(buttName);
    buttViewGroup->addButton(buttName);
    buttName->setText("Name");
    buttName->setCheckable(true);
    buttName->setIcon(QIcon(":/icons/purple"));
    buttName->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    buttAll->setChecked(true);

    treeToolbar->addWidget(new QLabel(tr("find").append(":")));

    //** Find Text
    QLineEdit *txtFindCode = new QLineEdit();
    treeToolbar->addWidget(txtFindCode);
    txtFindCode->setFixedWidth(100);
    connect(txtFindCode,    SIGNAL(textChanged(QString)),
            this,           SLOT(on_find_text_changed(QString))
    );

    treeToolbar->addSeparator();

    //** Add spacer widget to force right
    QWidget *spacerWidget = new QWidget();

    QSizePolicy *sizePolicy = new QSizePolicy();
    //sizePolicy->setHorizontalPolicy( QSizePolicy::Expanding );
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
    headerLabelsList << "Code" << "Tower" << "Elevation" << "Airport";
    model->setHorizontalHeaderLabels(headerLabelsList);

    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    proxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);

    proxyModel->setFilterKeyColumn(0);
    //proxyModel->setFilterFixedString();

    //******************************************************
    //**  Tree
    treeView = new QTreeView(this);
    treeLayout->addWidget(treeView);
    treeView->setModel(proxyModel);

    treeView->setUniformRowHeights(true);
    treeView->setAlternatingRowColors(true);
    treeView->setRootIsDecorated(false);
    treeView->setSortingEnabled(true);
    treeView->setSelectionMode(QAbstractItemView::SingleSelection);
    treeView->setSelectionBehavior(QAbstractItemView::SelectRows);

    //** Deaders and columns
    treeView->header()->setStretchLastSection(true);
    treeView->setColumnHidden(C_ELEVATION, true);
    treeView->setColumnHidden(C_TOWER, true);
    /*
    connect( treeView->selectionModel(),
             SIGNAL( selectionChanged (const QItemSelection&, const QItemSelection&) ),
             SLOT( set_aircraft(const QItemSelection&, const QItemSelection&) )
    );
    */
//    connect(treeView,
//            SIGNAL(clicked(QModelIndex)),
//            this, SLOT(on_tree_clicked(QModelIndex))
//    );

    statusBarTree = new QStatusBar();
    treeLayout->addWidget(statusBarTree);
    statusBarTree->showMessage("Idle");


}

//** Load_Airports() from database
void AirportsWidget::load_airports(){

    qDebug("load_airports()");
    //aptDatParser->process_file();
    airportsDb->airports();


}

//*** Load Airports
void AirportsWidget::on_airport(QString airport,QString name,QString tower,QString elevation){
    //qDebug() <<  airport << name << tower <<  elevation;

    //* insert new row into the model
    int new_row_index = model->rowCount();
    model->insertRow(new_row_index);

    //* create and set items
    QStandardItem *itemAirportCode = new QStandardItem();
    itemAirportCode->setText(airport);
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

void AirportsWidget::on_find_text_changed(QString txt){
    proxyModel->setFilterFixedString(txt);
    proxyModel->setFilterKeyColumn(C_NAME);
}

//*** Import Airports Dialog
void AirportsWidget::import_airports_dialog(){
    //* TODO message you are about to do this and take a few moment etc (or background)
     qDebug("AirportsWidget::load_airports_DB()");
    //QProgressDialog progress("Importing airports", "Abort Copy", 0, 2000, this);
    //progress.show();
     ImportAirportsWidget *imp = new ImportAirportsWidget(mainObject);
     imp->exec();
}

